#ifdef __INTELLISENSE__
#include "Tokenizer.hpp"
#endif

namespace fridayc {

  static constexpr auto SYMBOLS = "!\"%&'()*+,-./:;<=>[]{|}~"sv;

  constexpr Tokenizer::Tokenizer(std::string_view input) noexcept
    : input { std::move(input) }
  {}

  constexpr auto Tokenizer::begin() const noexcept -> iterator {
    return iterator{ this->input, 1, 1 };
  }

  constexpr auto Tokenizer::end() const noexcept -> iterator {
    return iterator{};
  }
  
  constexpr auto Tokenizer::size() const noexcept -> u64 {
    return std::distance(std::begin(*this), std::end(*this));
  }

  template<template<class T> class Container>
  requires std::same_as<Token, typename Container<Token>::value_type>
  constexpr auto Tokenizer::collect() const noexcept -> Container<Token> {
    return std::ranges::to<Container>(*this);
  }

  constexpr Tokenizer::iterator::iterator(std::string_view raw, u64 row, u64 col) noexcept
    : data { raw }
    , stride { 0 }
    , row { row }
    , col { col }
    , base_row { row }
    , base_col { col }
    , type { Token::Type::END }
  {
    this->advance();
  }

  constexpr auto Tokenizer::iterator::operator*() const noexcept -> Token {
    return Token{ this->data.substr(0, this->stride), this->type, this->base_row, this->base_col };
  }

  constexpr auto Tokenizer::iterator::applyStride() noexcept -> void {
    u64 skips = std::min(this->stride, this->data.length());
    this->data.remove_prefix(skips);
    this->stride = 0;
    this->base_row = this->row;
    this->base_col = this->col;
  }

  constexpr auto Tokenizer::iterator::operator++() noexcept -> Tokenizer::iterator& {
    this->applyStride();
    this->advance();
    return *this;
  }

  constexpr auto Tokenizer::iterator::operator++(int) noexcept -> Tokenizer::iterator {
    Tokenizer::iterator copy = *this;
    ++(*this);
    return std::move(copy);
  }

  constexpr auto Tokenizer::iterator::advance() noexcept -> void {
    if(this->peek().isAlpha()) {
      this->consumeIdentifier();
    } else if(this->peek().isDigit()) {
      this->consumeNumber();
    } else if(this->peek() == '/' and this->peek(1) == '/') {
      while(this->peek() and this->peek() != '\n') this->consume();
      this->applyStride();
      this->advance();
    } else if(std::ranges::binary_search(SYMBOLS, this->peek().unwrap())) {
      this->consumeSymbol();
    } else if(this->peek().isSpace() or this->peek().isBreak()) {
      this->consume();
      this->applyStride();
      this->advance();
    } else if(this->peek() == '\0') {
      *this = iterator{};
    } else {
      this->consumeIllegal();
    }
  }

  constexpr auto Tokenizer::iterator::consumeIllegal() noexcept -> void {
    this->consume();
    this->type = Token::Type::ILLEGAL;
  }

  constexpr auto Tokenizer::iterator::peek(u64 ahead) const noexcept -> Character {
    return this->stride + ahead < this->data.length() ? this->data[this->stride + ahead] : '\0';
  }
  
  constexpr auto Tokenizer::iterator::consume() noexcept -> void {
    if(this->peek().isBreak()) {
      ++this->row;
      this->col = 1;
    } else ++this->col;

    if(this->stride < this->data.length())
      ++this->stride;
  }
  

  constexpr auto Tokenizer::iterator::consumeIdentifier() noexcept -> void {
    while(peek().isAlnum()) consume();
    this->type = Token::identifierTypeOf(this->data.substr(0, this->stride));
  }
  
  constexpr auto Tokenizer::iterator::consumeNumber() noexcept -> void {
    while(peek().isDigit()) consume();

    bool floating = false;
    if(peek() == '.' and peek(1).isDigit()) {
      floating = true;
      consume(); // .
      while(peek().isDigit()) consume();
    }

    this->type = floating ? Token::Type::FLOAT_LITERAL : Token::Type::INT_LITERAL;
  }
  
  constexpr auto Tokenizer::iterator::match(char expected, Token::Type success, Token::Type fallback) -> void {
    if(this->peek() == expected) {
      this->consume();
      this->type = success;
    } else this->type = fallback;
  }

  constexpr auto Tokenizer::iterator::bimatch(char expected1, char expected2, Token::Type success1, Token::Type success2, Token::Type fallback) -> void {
    if(this->peek() == expected1) {
      this->consume();
      this->type = success1;
    } else if(this->peek() == expected2) {
      this->consume();
      this->type = success2;
    } else this->type = fallback;
  }

  constexpr auto Tokenizer::iterator::consumeSymbol() noexcept -> void {
    char current = this->peek();
    if(current == '"') return this->consumeStringLiteral();
    else if(current == '\'') return this->consumeCharacterLiteral();
    
    this->consume();

    switch(current) {
      case '(': this->type = Token::Type::LPAREN; break;
      case ')': this->type = Token::Type::RPAREN; break;
      case '[': this->type = Token::Type::LSQUARE; break;
      case ']': this->type = Token::Type::RSQUARE; break;
      case '{': this->type = Token::Type::LBRACE; break;
      case '}': this->type = Token::Type::RBRACE; break;
      case '.': this->type = Token::Type::DOT; break;
      case ',': this->type = Token::Type::COMMA; break;
      case ':': this->type = Token::Type::COLUMN; break;
      case ';': this->type = Token::Type::SEMICOL; break;
      case '~': this->type = Token::Type::BIT_NOT; break;
      case '+': this->match('=', Token::Type::PLUS_EQ, Token::Type::PLUS); break;
      case '*': this->match('=', Token::Type::STAR_EQ, Token::Type::STAR); break;
      case '/': this->match('=', Token::Type::SLASH_EQ, Token::Type::SLASH); break;
      case '%': this->match('=', Token::Type::MODULO_EQ, Token::Type::MODULO); break;
      case '&': this->match('=', Token::Type::BIT_AND_EQ, Token::Type::BIT_AND); break;
      case '|': this->match('=', Token::Type::BIT_OR_EQ, Token::Type::BIT_OR); break;
      case '!': this->match('=', Token::Type::NOT_EQ, Token::Type::ILLEGAL); break;
      case '=': this->bimatch('>', '=', Token::Type::IMPLIES, Token::Type::EQUALS, Token::Type::ASSIGN); break;
      case '-': this->bimatch('=', '>', Token::Type::MINUS_EQ, Token::Type::ARROW, Token::Type::MINUS); break;
      case '>': {
        if(this->peek() == '>') {
          this->consume();
          this->match('=', Token::Type::RSHIFT_EQ, Token::Type::RSHIFT);
        } else this->match('=', Token::Type::GREATER_EQ, Token::Type::GREATER);
        break;
      } case '<': {
        if(this->peek() == '<') {
          this->consume();
          this->match('=', Token::Type::LSHIFT_EQ, Token::Type::LSHIFT);
        } else this->match('=', Token::Type::LESS_EQ, Token::Type::LESS);
        break;
      } default: this->type = Token::Type::ILLEGAL;
    }
  }
  
  constexpr auto Tokenizer::iterator::consumeStringLiteral() noexcept -> void {
    this->consume();
    while(this->peek() and this->peek() != '"') {
      if(this->peek() == '\\' and this->peek(1) == '"')
        this->consume();
      this->consume();
    }
    this->consume();
    this->type = Token::Type::STR_LITERAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeCharacterLiteral() noexcept -> void {
    this->consume();
    while(this->peek() and this->peek() != '\'') {
      if(this->peek() == '\\' and this->peek(1) == '\'')
        this->consume();
      this->consume();
    }
    this->consume();
    this->type = Token::Type::CHAR_LITERAL;
  }


}

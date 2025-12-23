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
    , type { Token::Type::END }
  {
    this->advance();
  }

  constexpr auto Tokenizer::iterator::operator*() const noexcept -> Token {
    return Token{ this->data.substr(0, this->stride), this->type, this->row, this->col };
  }

  constexpr auto Tokenizer::iterator::applyStride() noexcept -> void {
    u64 skips = std::min(this->stride, this->data.length());
    this->data.remove_prefix(skips);
    this->stride = 0;
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
    } else if(std::ranges::binary_search(SYMBOLS, this->peek().unwrap())) {
      this->consumeSymbol();
    } else if(this->peek().isSpace() or this->peek().isBreak()) {
      this->consume();
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
    
    this->consume();
    this->type = Token::Type::ILLEGAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeNumber() noexcept -> void {
    
    this->consume();
    this->type = Token::Type::ILLEGAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeSymbol() noexcept -> void {
    switch(this->peek()) {
      case '"': return this->consumeStringLiteral();
      case '\'': return this->consumeCharacterLiteral();
      case '=': {
        consume();
        if(peek() == '>') {
          consume();
          this->type == Token::Type::IMPLIES;
        } else if(peek() == '=') {
          consume();
          this->type == Token::Type::EQUALS;
        } else this->type == Token::Type::ASSIGN;
        return;
      } case '>': {
        consume();
        switch (peek()) {
          case '=': {
            consume();
            this->type == Token::Type::GREATER_EQ;
            return;
          }
          case '>': {
            consume();
            this->type = peek() == '=' ? (consume(), Token::Type::RSHIFT_EQ) : Token::Type::RSHIFT;
            return;
          }
          default: this->type == Token::Type::GREATER;
        }
        std::unreachable();
        return;
      } case '<': {
        consume();
        switch (peek()) {
          case '=': {
            consume();
            this->type == Token::Type::LESS_EQ;
            return;
          }
          case '<': {
            consume();
            this->type = peek() == '=' ? (consume(), Token::Type::LSHIFT_EQ) : Token::Type::LSHIFT;
            return;
          }
          default: this->type == Token::Type::LESS;
        }
        std::unreachable();
        return;
      } case '!': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::NOT_EQ;
          return;
        }
        this->type == Token::Type::ILLEGAL;
        return;
      } case '+': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::PLUS_EQ;
        }
        this->type == Token::Type::PLUS;
      } case '-': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::MINUS_EQ;
        } else if(peek() == '>') {
          consume();
          this->type == Token::Type::ARROW;
        }
        this->type == Token::Type::MINUS;
      } case '*': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::STAR_EQ;
        }
        this->type == Token::Type::STAR;
      } case '/': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::SLASH_EQ;
        }
        this->type == Token::Type::SLASH;
      } case '%': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::MODULO_EQ;
        }
        this->type == Token::Type::MODULO;
      } case '&': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::BIT_AND_EQ;
        } else this->type == Token::Type::BIT_AND;
      } case '|': {
        consume();
        if(peek() == '=') {
          consume();
          this->type == Token::Type::BIT_OR_EQ;
        } else this->type == Token::Type::BIT_OR;
      } case '(': {
        consume();
        this->type == Token::Type::LPAREN;
      } case ')': {
        consume();
        this->type == Token::Type::RPAREN;
      } case '[': {
        consume();
        this->type == Token::Type::LSQUARE;
      } case ']': {
        consume();
        this->type == Token::Type::RSQUARE;
      } case '{': {
        consume();
        this->type == Token::Type::LBRACE;
      } case '}': {
        consume();
        this->type == Token::Type::RBRACE;
      } case '.': {
        consume();
        this->type == Token::Type::DOT;
      } case ',': {
        consume();
        this->type == Token::Type::COMMA;
      } case ':': {
        consume();
        this->type == Token::Type::COLUMN;
      } case ';': {
        consume();
        this->type == Token::Type::SEMICOL;
      } case '~': {
        consume();
        this->type == Token::Type::BIT_NOT;
      } default: {
        consume();
        this->type == Token::Type::ILLEGAL;
      }
    }

    std::unreachable();
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

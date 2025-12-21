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
    return Token{ this->data.substr(this->stride), this->type, this->row, this->col };
  }

  constexpr auto Tokenizer::iterator::operator++() noexcept -> Tokenizer::iterator& {
    this->advance();
    return *this;
  }

  constexpr auto Tokenizer::iterator::operator++(int) noexcept -> Tokenizer::iterator {
    Tokenizer::iterator copy = *this;
    this->advance();
    return std::move(copy);
  }

  constexpr auto Tokenizer::iterator::advance() noexcept -> void {
    if(this->type == Token::Type::ILLEGAL) {
      *this = iterator{};
      return;
    }
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
    } else {
      this->type == Token::Type::ILLEGAL;
    }
    this->type = Token::Type::ILLEGAL;
  }


  constexpr auto Tokenizer::iterator::peek(u64 ahead) const noexcept -> Character {
    return ahead < this->data.length() ? this->data[ahead] : '\0';
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
    this->type = Token::Type::ILLEGAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeNumber() noexcept -> void {
    this->type = Token::Type::ILLEGAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeSymbol() noexcept -> void {
    this->type = Token::Type::ILLEGAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeStringLiteral() noexcept -> void {
    this->type = Token::Type::ILLEGAL;
  }
  
  constexpr auto Tokenizer::iterator::consumeCharacterLiteral() noexcept -> void {
    this->type = Token::Type::ILLEGAL;
  }

}

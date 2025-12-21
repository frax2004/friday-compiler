#ifdef __INTELLISENSE__
#include "Token.hpp"
#endif

namespace fridayc {

  static constexpr const std::array VALUES = {
    Token::Type::END,
    Token::Type::ILLEGAL,
    Token::Type::FN,
    Token::Type::THIS,
    Token::Type::IF,
    Token::Type::ELSE,
    Token::Type::ELIF,
    Token::Type::WHILE,
    Token::Type::FOR,
    Token::Type::ENUM,
    Token::Type::STRUCT,
    Token::Type::NAMESPACE,
    Token::Type::RETURN,
    Token::Type::CONST,
    Token::Type::LET,
    Token::Type::USING,
    Token::Type::NUL,
    Token::Type::TRUE,
    Token::Type::FALSE,
    Token::Type::PRINT,
    Token::Type::PLUS,
    Token::Type::MINUS,
    Token::Type::STAR,
    Token::Type::SLASH,
    Token::Type::MODULO,
    Token::Type::AND,
    Token::Type::OR,
    Token::Type::NOT,
    Token::Type::LSHIFT,
    Token::Type::RSHIFT,
    Token::Type::BIT_AND,
    Token::Type::BIT_OR,
    Token::Type::BIT_NOT,
    Token::Type::ASSIGN,
    Token::Type::PLUS_EQ,
    Token::Type::MINUS_EQ,
    Token::Type::STAR_EQ,
    Token::Type::SLASH_EQ,
    Token::Type::MODULO_EQ,
    Token::Type::LSHIFT_EQ,
    Token::Type::RSHIFT_EQ,
    Token::Type::BIT_AND_EQ,
    Token::Type::BIT_OR_EQ,
    Token::Type::LPAREN,
    Token::Type::RPAREN,
    Token::Type::LSQUARE,
    Token::Type::RSQUARE,
    Token::Type::LBRACE,    
    Token::Type::RBRACE,
    Token::Type::DOT,
    Token::Type::COMMA,
    Token::Type::SEMICOL,
    Token::Type::COLUMN,
    Token::Type::ARROW,
    Token::Type::IMPLIES,
    Token::Type::GREATER,
    Token::Type::LESS,
    Token::Type::EQUALS,
    Token::Type::GREATER_EQ,
    Token::Type::LESS_EQ,
    Token::Type::NOT_EQ,
    Token::Type::IDENTIFIER,
    Token::Type::INT_LITERAL,
    Token::Type::STR_LITERAL,
    Token::Type::CHAR_LITERAL,
    Token::Type::FLOAT_LITERAL
  };

  static constexpr const std::array NAMES = {
    "END"sv,
    "ILLEGAL"sv,
    "FN"sv,
    "THIS"sv,
    "IF"sv,
    "ELSE"sv,
    "ELIF"sv,
    "WHILE"sv,
    "FOR"sv,
    "ENUM"sv,
    "STRUCT"sv,
    "NAMESPACE"sv,
    "RETURN"sv,
    "CONST"sv,
    "LET"sv,
    "USING"sv,
    "NUL"sv,
    "TRUE"sv,
    "FALSE"sv,
    "PRINT"sv,
    "PLUS"sv,
    "MINUS"sv,
    "STAR"sv,
    "SLASH"sv,
    "MODULO"sv,
    "AND"sv,
    "OR"sv,
    "NOT"sv,
    "LSHIFT"sv,
    "RSHIFT"sv,
    "BIT_AND"sv,
    "BIT_OR"sv,
    "BIT_NOT"sv,
    "ASSIGN"sv,
    "PLUS_EQ"sv,
    "MINUS_EQ"sv,
    "STAR_EQ"sv,
    "SLASH_EQ"sv,
    "MODULO_EQ"sv,
    "LSHIFT_EQ"sv,
    "RSHIFT_EQ"sv,
    "BIT_AND_EQ"sv,
    "BIT_OR_EQ"sv,
    "LPAREN"sv,
    "RPAREN"sv,
    "LSQUARE"sv,
    "RSQUARE"sv,
    "LBRACE"sv,    
    "RBRACE"sv,
    "DOT"sv,
    "COMMA"sv,
    "SEMICOL"sv,
    "COLUMN"sv,
    "ARROW"sv,
    "IMPLIES"sv,
    "GREATER"sv,
    "LESS"sv,
    "EQUALS"sv,
    "GREATER_EQ"sv,
    "LESS_EQ"sv,
    "NOT_EQ"sv,
    "IDENTIFIER"sv,
    "INT_LITERAL"sv,
    "STR_LITERAL"sv,
    "CHAR_LITERAL"sv,
    "FLOAT_LITERAL"sv
  };

  constexpr auto Token::toString() const noexcept -> std::string_view {
    return NAMES[this->getType()];
  }

  // constexpr auto Token::Type::parse(std::string_view str) noexcept -> Token::Type {
  //   const auto iter = std::ranges::find(NAMES, str);
  //   if(iter != NAMES.end())
  //     return Token::Type{ static_cast<Token::Type::value_type>(std::distance(NAMES.begin(), iter)) };
  //   else return Token::Type{ Token::Type::ILLEGAL };
  // }

  constexpr auto Token::values() noexcept -> std::vector<i32> {
    return std::vector<i32>{ VALUES.begin(), VALUES.end() };
  }

  constexpr auto Token::names() noexcept -> std::vector<std::string_view> {
    return std::vector<std::string_view>{ NAMES.begin(), NAMES.end() };
  }

  constexpr Token::Token(std::string_view literal, Type type, u64 row, u64 col) noexcept 
    : literal { std::move(literal) }
    , row { row }
    , col { col }
    , type { type }
  {}

  constexpr auto Token::operator==(Token const& other) const noexcept -> bool {
    if(this->type != other.type) return false;
    switch(this->type) {
      case Token::Type::IDENTIFIER:
      case Token::Type::INT_LITERAL:
      case Token::Type::FLOAT_LITERAL:
      case Token::Type::STR_LITERAL:
      case Token::Type::CHAR_LITERAL: return other.literal == this->literal;
      default: return true;
    }
    std::unreachable();
  }


  constexpr auto Token::getLiteral() const noexcept -> std::string_view {
    return this->literal;
  }

  constexpr auto Token::getRow() const noexcept -> u64 {
    return this->row;
  }

  constexpr auto Token::getColumn() const noexcept -> u64 {
    return this->col;
  }

  constexpr auto Token::getType() const noexcept -> Type {
    return this->type;
  }


}
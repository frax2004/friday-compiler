#pragma once

namespace fridayc {
  
  struct Token {
    
    public:
    enum Type : i32 { 
      ILLEGAL, END,
      
      // Keywords
      FN, THIS, IF, ELSE, ELIF, WHILE, FOR, ENUM, STRUCT, NAMESPACE, RETURN, CONST, LET, USING, NUL, TRUE, FALSE, PRINT,
  
      // Operators
      PLUS, MINUS, STAR, SLASH, MODULO, AND, OR, NOT, LSHIFT, RSHIFT, BIT_AND, BIT_OR, BIT_NOT,
      ASSIGN, PLUS_EQ, MINUS_EQ, STAR_EQ, SLASH_EQ, MODULO_EQ, LSHIFT_EQ, RSHIFT_EQ, BIT_AND_EQ, BIT_OR_EQ,
      LPAREN, RPAREN, LSQUARE, RSQUARE, LBRACE, 
      RBRACE, DOT, COMMA, SEMICOL, COLUMN, ARROW, IMPLIES, GREATER, 
      LESS, EQUALS, GREATER_EQ, LESS_EQ, NOT_EQ,

      // Identifiers and Literals
      IDENTIFIER, INT_LITERAL, STR_LITERAL, CHAR_LITERAL, FLOAT_LITERAL,
    };
    
    private:
    std::string_view literal { "" };
    u64 row { 0 };
    u64 col { 0 };
    Type type { Type::ILLEGAL };

    public:
    constexpr Token() noexcept = default;
    constexpr Token(std::string_view literal, Type type, u64 row, u64 col) noexcept;
    constexpr auto operator==(Token const& other) const noexcept -> bool;
    
    constexpr auto toString() const noexcept -> std::string_view;
    constexpr auto getLiteral() const noexcept -> std::string_view;
    constexpr auto getRow() const noexcept -> u64;
    constexpr auto getColumn() const noexcept -> u64;
    constexpr auto getType() const noexcept -> Type;
    constexpr static auto identifierTypeOf(std::string_view literal) noexcept -> Token::Type;

    static constexpr auto values() noexcept -> std::vector<i32>;
    static constexpr auto names() noexcept -> std::vector<std::string_view>;
  };
}

#include "Token.inl"


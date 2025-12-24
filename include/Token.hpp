#pragma once

namespace fridayc {
  
  struct Token {
    
    public:
    enum Type : byte { 
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
    constexpr Token(Type type, std::string_view literal) noexcept;
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

  namespace Tokens {
    static const Token PRINT      { Token::Type::PRINT,      "print"     };
    static const Token CONST      { Token::Type::CONST,      "const"     };
    static const Token LET        { Token::Type::LET,        "let"       };
    static const Token NAMESPACE  { Token::Type::NAMESPACE,  "namespace" };
    static const Token USING      { Token::Type::USING,      "using"     };
    static const Token FN         { Token::Type::FN,         "fn"        };
    static const Token THIS       { Token::Type::THIS,       "this"      };
    static const Token NUL        { Token::Type::NUL,        "null"      };
    static const Token TRUE       { Token::Type::TRUE,       "true"      };
    static const Token FALSE      { Token::Type::FALSE,      "false"     };
    static const Token RETURN     { Token::Type::RETURN,     "return"    };
    static const Token IF         { Token::Type::IF,         "if"        };
    static const Token ELSE       { Token::Type::ELSE,       "else"      };
    static const Token ELIF       { Token::Type::ELIF,       "elif"      };
    static const Token WHILE      { Token::Type::WHILE,      "while"     };
    static const Token FOR        { Token::Type::FOR,        "for"       };
    static const Token ENUM       { Token::Type::ENUM,       "enum"      };
    static const Token STRUCT     { Token::Type::STRUCT,     "struct"    };
    static const Token END        { Token::Type::END,        "EOF"       };
    static const Token ILLEGAL    { Token::Type::ILLEGAL,    ""          };
    static const Token PLUS       { Token::Type::PLUS,       "+"         };
    static const Token MINUS      { Token::Type::MINUS,      "-"         };
    static const Token STAR       { Token::Type::STAR,       "*"         };
    static const Token SLASH      { Token::Type::SLASH,      "/"         };
    static const Token MODULO     { Token::Type::MODULO,     "%"         };
    static const Token AND        { Token::Type::AND,        "and"       };
    static const Token OR         { Token::Type::OR,         "or"        };
    static const Token NOT        { Token::Type::NOT,        "not"       };
    static const Token LSHIFT     { Token::Type::LSHIFT,     "<<"        };
    static const Token RSHIFT     { Token::Type::RSHIFT,     ">>"        };
    static const Token BIT_AND    { Token::Type::BIT_AND,    "&"         };
    static const Token BIT_OR     { Token::Type::BIT_OR,     "|"         };
    static const Token BIT_NOT    { Token::Type::BIT_NOT,    "~"         };
    static const Token PLUS_EQ    { Token::Type::PLUS_EQ,    "+="        };
    static const Token MINUS_EQ   { Token::Type::MINUS_EQ,   "-="        };
    static const Token STAR_EQ    { Token::Type::STAR_EQ,    "*="        };
    static const Token SLASH_EQ   { Token::Type::SLASH_EQ,   "/="        };
    static const Token MODULO_EQ  { Token::Type::MODULO_EQ,  "%="        };
    static const Token LSHIFT_EQ  { Token::Type::LSHIFT_EQ,  "<<="       };
    static const Token RSHIFT_EQ  { Token::Type::RSHIFT_EQ,  ">>="       };
    static const Token BIT_AND_EQ { Token::Type::BIT_AND_EQ, "&="        }; 
    static const Token BIT_OR_EQ  { Token::Type::BIT_OR_EQ,  "|="        };
    static const Token LPAREN     { Token::Type::LPAREN,     "("         };
    static const Token RPAREN     { Token::Type::RPAREN,     ")"         };
    static const Token LSQUARE    { Token::Type::LSQUARE,    "["         };
    static const Token RSQUARE    { Token::Type::RSQUARE,    "]"         };
    static const Token LBRACE     { Token::Type::LBRACE,     "{"         };
    static const Token RBRACE     { Token::Type::RBRACE,     "}"         };
    static const Token DOT        { Token::Type::DOT,        "."         };
    static const Token COMMA      { Token::Type::COMMA,      ","         };
    static const Token SEMICOL    { Token::Type::SEMICOL,    ";"         };
    static const Token COLUMN     { Token::Type::COLUMN,     ":"         };
    static const Token ARROW      { Token::Type::ARROW,      "->"        };
    static const Token IMPLIES    { Token::Type::IMPLIES,    "=>"        };
    static const Token GREATER    { Token::Type::GREATER,    ">"         };
    static const Token LESS       { Token::Type::LESS,       "<"         };
    static const Token EQUALS     { Token::Type::EQUALS,     "=="        };
    static const Token GREATER_EQ { Token::Type::GREATER_EQ, ">="        };
    static const Token LESS_EQ    { Token::Type::LESS_EQ,    "<="        };
    static const Token ASSIGN     { Token::Type::ASSIGN,     "="         };
    static const Token NOT_EQ     { Token::Type::NOT_EQ,     "!="        };   
  }

}

#include "Token.inl"


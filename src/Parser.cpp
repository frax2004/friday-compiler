#include "Parser.hpp"


namespace fridayc {
  
  const std::map<Token::Type, Parser::PrefixParser> Parser::prefixParsers {
    { Token::Type::TRUE           ,  Parser::parseBoolLiteral       },
    { Token::Type::FALSE          ,  Parser::parseBoolLiteral       },
    { Token::Type::INT_LITERAL    ,  Parser::parseIntLiteral        },
    { Token::Type::CHAR_LITERAL   ,  Parser::parseCharLiteral       },
    { Token::Type::FLOAT_LITERAL  ,  Parser::parseFloatLiteral      },
    { Token::Type::STR_LITERAL    ,  Parser::parseStringLiteral     },
    { Token::Type::NUL            ,  Parser::parseObjectLiteral     },
    { Token::Type::THIS           ,  Parser::parseObjectLiteral     },
    { Token::Type::IDENTIFIER     ,  Parser::parseIdentifier        },

    { Token::Type::MINUS          ,  Parser::parsePrefix            },
    { Token::Type::PLUS           ,  Parser::parsePrefix            },
    { Token::Type::NOT            ,  Parser::parsePrefix            },
    { Token::Type::BIT_NOT        ,  Parser::parsePrefix            },
    { Token::Type::LPAREN         ,  Parser::parseGroupedExpression },
  };
  
  const std::map<Token::Type, Parser::InfixParser> Parser::infixParsers {
    { Token::Type::OR          , Parser::parseLeftAssocInfix  },
    { Token::Type::AND         , Parser::parseLeftAssocInfix  },
    { Token::Type::PLUS        , Parser::parseLeftAssocInfix  },
    { Token::Type::STAR        , Parser::parseLeftAssocInfix  },
    { Token::Type::MINUS       , Parser::parseLeftAssocInfix  },
    { Token::Type::SLASH       , Parser::parseLeftAssocInfix  },
    { Token::Type::MODULO      , Parser::parseLeftAssocInfix  },
    { Token::Type::LSHIFT      , Parser::parseLeftAssocInfix  },
    { Token::Type::RSHIFT      , Parser::parseLeftAssocInfix  },
    { Token::Type::BIT_OR      , Parser::parseLeftAssocInfix  },
    { Token::Type::BIT_AND     , Parser::parseLeftAssocInfix  },
    
    { Token::Type::ASSIGN      , Parser::parseRightAssocInfix },
    { Token::Type::PLUS_EQ     , Parser::parseRightAssocInfix },
    { Token::Type::STAR_EQ     , Parser::parseRightAssocInfix },
    { Token::Type::MINUS_EQ    , Parser::parseRightAssocInfix },
    { Token::Type::SLASH_EQ    , Parser::parseRightAssocInfix },
    { Token::Type::MODULO_EQ   , Parser::parseRightAssocInfix },
    { Token::Type::LSHIFT_EQ   , Parser::parseRightAssocInfix },
    { Token::Type::RSHIFT_EQ   , Parser::parseRightAssocInfix },
    { Token::Type::BIT_OR_EQ   , Parser::parseRightAssocInfix },
    { Token::Type::BIT_AND_EQ  , Parser::parseRightAssocInfix },
  
    { Token::Type::LESS        , Parser::parseLeftAssocInfix  },
    { Token::Type::EQUALS      , Parser::parseLeftAssocInfix  },
    { Token::Type::NOT_EQ      , Parser::parseLeftAssocInfix  },
    { Token::Type::GREATER     , Parser::parseLeftAssocInfix  },
    { Token::Type::LESS_EQ     , Parser::parseLeftAssocInfix  },
    { Token::Type::GREATER_EQ  , Parser::parseLeftAssocInfix  },
  
    { Token::Type::DOT         , Parser::parseLeftAssocInfix  },
    { Token::Type::LPAREN      , Parser::parseFunctionCall    },
    { Token::Type::LSQUARE     , Parser::parseSubscript       },

  };
  
  const std::map<Token::Type, Parser::Precedence> Parser::precedences {
    { Token::Type::BIT_OR     , Precedence::BIT_OR         },
    { Token::Type::BIT_AND    , Precedence::BIT_AND        },
    { Token::Type::OR         , Precedence::OR             },
    { Token::Type::AND        , Precedence::AND            },
    { Token::Type::DOT        , Precedence::MEMBER_ACCESS  },
    { Token::Type::PLUS       , Precedence::ADDTIVE        },
    { Token::Type::LESS       , Precedence::INEQUALITY     },
    { Token::Type::STAR       , Precedence::MULTIPLICATIVE },
    { Token::Type::MINUS      , Precedence::ADDTIVE        },
    { Token::Type::SLASH      , Precedence::MULTIPLICATIVE },
    { Token::Type::MODULO     , Precedence::MULTIPLICATIVE },
    { Token::Type::LSHIFT     , Precedence::SHIFT          },
    { Token::Type::RSHIFT     , Precedence::SHIFT          },
    { Token::Type::EQUALS     , Precedence::EQUALITY       },
    { Token::Type::ASSIGN     , Precedence::ASSIGNMENT     },
    { Token::Type::NOT_EQ     , Precedence::EQUALITY       },
    { Token::Type::LPAREN     , Precedence::FUNCTION_CALL  },
    { Token::Type::LSQUARE    , Precedence::SUBSCRIPT      },
    { Token::Type::GREATER    , Precedence::INEQUALITY     },
    { Token::Type::PLUS_EQ    , Precedence::ASSIGNMENT     },
    { Token::Type::STAR_EQ    , Precedence::ASSIGNMENT     },
    { Token::Type::LESS_EQ    , Precedence::INEQUALITY     },
    { Token::Type::MINUS_EQ   , Precedence::ASSIGNMENT     },
    { Token::Type::SLASH_EQ   , Precedence::ASSIGNMENT     },
    { Token::Type::MODULO_EQ  , Precedence::ASSIGNMENT     },
    { Token::Type::LSHIFT_EQ  , Precedence::ASSIGNMENT     },
    { Token::Type::RSHIFT_EQ  , Precedence::ASSIGNMENT     },
    { Token::Type::BIT_OR_EQ  , Precedence::ASSIGNMENT     },
    { Token::Type::BIT_AND_EQ , Precedence::ASSIGNMENT     },
    { Token::Type::GREATER_EQ , Precedence::INEQUALITY     },
    
  };
  
  Parser::Parser(std::vector<Token> tokens) noexcept 
    : tokens { std::move(tokens) }
    , pos { 0 }
  {}

  auto Parser::getPrefixParser(Token::Type type) noexcept -> PrefixParser {
    return prefixParsers.contains(type) ? prefixParsers.at(type) : nullptr;
  }
  
  auto Parser::getInfixParser(Token::Type type) noexcept -> InfixParser {
    return infixParsers.contains(type) ? infixParsers.at(type) : nullptr;
  }

  auto Parser::getPrecedence(Token::Type type) noexcept -> Precedence {
    return precedences.contains(type) ? precedences.at(type) : Precedence::LOWEST;
  }

  auto Parser::errorAt(Token const& token, std::string error) noexcept -> void {
    if(panic_mode) return;
    error_queue.emplace_back(error, token.getRow(), token.getColumn(), token.getLiteral().length());
    panic_mode = true;
  }

  auto Parser::expect(Token::Type type, std::string error) -> void {
    if(peek().getType() == type) return;
    errorAt(peek(), error);
  }

  auto Parser::peek(u64 ahead) -> Token const& {
    return pos + ahead < tokens.size() ? tokens[pos + ahead] : Tokens::END;
  }

  auto Parser::consume() noexcept -> Token {
    if(pos < tokens.size()) return tokens[pos++];
    return Tokens::END;
  }

  auto Parser::good() const noexcept -> bool {
    return not panic_mode;
  }

  auto Parser::synchronize() noexcept -> void {
    if(not panic_mode) return;

    Token token;
    while((token = peek()).getType() != Token::Type::END) {

      switch (token.getType()) {

        // * End of statement
        case Token::Type::RBRACE:
        case Token::Type::SEMICOL: {
          panic_mode = false;
          consume();
          return;
        }

        // * Statement begin
        case Token::Type::FN:
        case Token::Type::ENUM:
        case Token::Type::USING:
        case Token::Type::STRUCT:
        case Token::Type::NAMESPACE: {
          panic_mode = false;
          return;
        }
        default: consume();
      }
    }
  }

  auto Parser::parse() -> std::tuple<Program, std::vector<Error>> {
    pos = 0;

    Program program;
    program.block = std::make_unique<BlockStatement>();

    while(peek() != Tokens::END) {
      auto statement = parseTopLevelStatement();
      good() ? program.block->add(std::move(statement)) : synchronize();
    }
    
    return std::make_tuple(std::move(program), std::move(error_queue));
  }

}
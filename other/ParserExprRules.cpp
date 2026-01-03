#include "Parser.hpp"

namespace fridayc {

  auto Parser::parseExpression(Precedence precedence) noexcept -> Box<Expression> {
    Token token = consume();
    
    PrefixParser prefix_parser = Parser::getPrefixParser(token.getType());
    if(not prefix_parser) {
      errorAt(token, "Unexpected token '{}' as an expression prefix operator"f.format(token.getLiteral()));
      return nullptr;
    }

    Box<Expression> left = std::invoke(prefix_parser, this, std::move(token));
    if(not left) return nullptr;

    while(precedence < Parser::getPrecedence(peek().getType())) {
      token = consume();

      InfixParser infix_parser = Parser::getInfixParser(token.getType());
      if(not infix_parser) {
        errorAt(token, "Unexpected token '{}' as an expression infix operator"f.format(token.getLiteral()));
        return nullptr;
      }
  
      left = std::invoke(infix_parser, this, std::move(left), std::move(token));
      if(not left) return nullptr;

    }

    return std::move(left);
  }

  auto Parser::parsePrefix(Token token) noexcept -> Box<Expression> {
    auto right = parseExpression(Precedence::PREFIX);
    if(not good()) return nullptr;

    return std::make_unique<PrefixExpression>(token.getType(), std::move(right));
  }
  
  auto Parser::parseLeftAssocInfix(Box<Expression> left, Token token) noexcept -> Box<Expression> {
    Precedence precedence = getPrecedence(token.getType());
    auto right = parseExpression(precedence);
    if(not good()) return nullptr;

    return std::make_unique<InfixExpression>(std::move(left), token.getType(), std::move(right));
  }

  auto Parser::parseRightAssocInfix(Box<Expression> left, Token token) noexcept -> Box<Expression> {
    Precedence precedence = getPrecedence(token.getType());
    auto right = parseExpression(static_cast<Precedence>(std::to_underlying(precedence)-1));
    if(not good()) return nullptr;

    return std::make_unique<InfixExpression>(std::move(left), token.getType(), std::move(right));
  }
  
  auto Parser::parseIdentifier(Token token) noexcept -> Box<Expression> {
    return std::make_unique<Identifier>(std::string{ token.getLiteral() });
  }

  auto Parser::parseObjectLiteral(Token token) noexcept -> Box<Expression> {
    return std::make_unique<ObjectLiteral>(std::move(token));
  }

  auto Parser::parseBoolLiteral(Token token) noexcept -> Box<Expression> {
    return std::make_unique<BoolLiteral>(Boolean::parse(token.getLiteral()));
  }

  auto Parser::parseStringLiteral(Token token) noexcept -> Box<Expression> {    
    return std::make_unique<StringLiteral>(std::string{ token.getLiteral() }); 
  }

  auto Parser::parseFloatLiteral(Token token) noexcept -> Box<Expression> {
    return std::make_unique<FloatLiteral>(Double::parse(token.getLiteral()));
  }

  auto Parser::parseIntLiteral(Token token) noexcept -> Box<Expression> {    
    return std::make_unique<IntLiteral>(Long::parse(token.getLiteral())); 
  }

  auto Parser::parseCharLiteral(Token token) noexcept -> Box<Expression> {
    return std::make_unique<CharLiteral>(Character::parse(token.getLiteral()));
  }

  auto Parser::parseType(Token token) noexcept -> Box<TypeExpression> {
    std::string name{ token.getLiteral() };
    u32 dims = 0;

    while(peek().getType() == Token::Type::LSQUARE) {
      consume(); // '['
      expect(
        Token::Type::RSQUARE, 
        "Expected ']' matching previous '[', got '{}'"f.format(peek().getLiteral())
      );
      if(not good()) return nullptr;
      consume(); // ']'
      ++dims;
    }

    return std::make_unique<TypeExpression>(std::move(name), dims);
  }

  auto Parser::parseGroupedExpression(Token) noexcept -> Box<Expression> {
    auto expr = parseExpression();

    expect(Token::Type::RPAREN, "Expected ')' matching previous '(', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume(); // ')'

    return std::move(expr);
  }

  auto Parser::parseArrayLiteral(Token token) noexcept -> Box<Expression> {

    auto array = std::make_unique<ArrayLiteral>();

    if(peek().getType() != Token::Type::RSQUARE) {
      do {
        auto expr = parseExpression();
        if(not good()) return nullptr;

        array->add(std::move(expr));
      } while(peek().getType() == Token::Type::COMMA and consume().getType() == Token::Type::COMMA);
    }

    expect(Token::Type::RSQUARE, "Expected ']' matching previous '[' in array literal, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume(); // ']'

    return std::move(array);
  }

  auto Parser::parseFunctionCall(Box<Expression> function, Token) noexcept -> Box<Expression> {
    auto callExpr = std::make_unique<CallExpression>(std::move(function));

    if(peek().getType() != Token::Type::RPAREN) {
      do {
        auto arg = parseExpression();
        if(not good()) return nullptr;
        callExpr->add(std::move(arg));

      } while(peek().getType() == Token::Type::COMMA and consume().getType() == Token::Type::COMMA);
    }
    
    expect(Token::Type::RPAREN, "Expected ')' after function call matching '(', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume(); // ')'
    
    return std::move(callExpr);
  }

  auto Parser::parseSubscript(Box<Expression> array, Token) noexcept -> Box<Expression> {
    auto index = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::RSQUARE, "Expected ']' after index expression matching '[', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume(); // ']'

    return std::make_unique<SubscriptExpression>(std::move(array), std::move(index));
  }

}
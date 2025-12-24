#include "Parser.hpp"


namespace fridayc {

  const std::map<Token::Type, Parser::StatementParser> Parser::stmtParsers {
    { Token::Type::IF        , (StatementParser)Parser::parseIfStatement          },
    { Token::Type::FN        , (StatementParser)Parser::parseFunctionStatement    },
    { Token::Type::LET       , (StatementParser)Parser::parseDeclarationStatement },
    { Token::Type::FOR       , (StatementParser)Parser::parseForStatement         },
    { Token::Type::ENUM      , (StatementParser)Parser::parseEnumStatement        },
    { Token::Type::CONST     , (StatementParser)Parser::parseDeclarationStatement },
    { Token::Type::WHILE     , (StatementParser)Parser::parseWhileStatement       },
    { Token::Type::RETURN    , (StatementParser)Parser::parseReturnStatement      },
    { Token::Type::STRUCT    , (StatementParser)Parser::parseStructStatement      },
    { Token::Type::PRINT     , (StatementParser)Parser::parsePrintStatement       },
  };

  const std::map<Token::Type, Parser::StatementParser> Parser::topLevelStmtParsers {
    { Token::Type::FN        , (StatementParser)Parser::parseFunctionStatement    },
    { Token::Type::STRUCT    , (StatementParser)Parser::parseStructStatement      },
    { Token::Type::ENUM      , (StatementParser)Parser::parseEnumStatement        },
    { Token::Type::NAMESPACE , (StatementParser)Parser::parseNamespaceStatement   },
    { Token::Type::USING     , (StatementParser)Parser::parseUsingStatement       },
  };

  auto Parser::parseTopLevelStatement() noexcept -> Box<Statement> {
    if(auto it = topLevelStmtParsers.find(peek().getType()); it != topLevelStmtParsers.end()) {
      return std::invoke(topLevelStmtParsers.at(peek().getType()), this);
    } else {
      expect(
        Token::Type::FN,
        "Expect a top level statement (function, struct, enum, namespace or using statements), got '{}'"f
        .format(peek().getLiteral())
      );
      return nullptr;
    }
  }

  auto Parser::parseStatement() noexcept -> Box<Statement> {
    return stmtParsers.contains(peek().getType()) ? 
      std::invoke(stmtParsers.at(peek().getType()), this) 
        : parseExpressionStatement();
  }

  auto Parser::parsePrintStatement() noexcept -> Box<Statement> {
    consume(); // print
    auto expr = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::SEMICOL, "Expected ';' after expression, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    return std::make_unique<PrintStatement>(std::move(expr));
  }

  auto Parser::parseDeclarationStatement() noexcept -> Box<Statement> {
    auto declarator = consume().getType();
    bool constant = declarator == Token::Type::CONST; // 'let' or 'const'

    expect(
      Token::Type::IDENTIFIER, 
      "Expected an identifier after keyword '{}', got '{}'"f.format((declarator == Token::Type::CONST ? "const" : "let"), peek().getLiteral())
    );
    if(not good()) return nullptr;

    std::string id { consume().getLiteral() };

    expect(
      Token::Type::COLUMN,
      "Expected ':' after identifier, got '{}'"f.format(peek().getLiteral())
    );
    if(not good()) return nullptr;
    consume(); // ':'

    expect(
      Token::Type::IDENTIFIER,
      "Expected a type after ':', got '{}'"f.format(peek().getLiteral())
    );
    if(not good()) return nullptr;

    auto type = parseType(consume());
    if(not good()) return nullptr;


    expect(
      Token::Type::ASSIGN, 
      "Expected '=' to initialize variable, got '{}'"f.format(peek().getLiteral())
    );
    if(not good()) return nullptr;
    consume();

    auto expr = parseExpression();
    if(not good()) return nullptr;

    expect(
      Token::Type::SEMICOL,
      "Expected ';' after declaration, got '{}'"f.format(peek().getLiteral())
    );

    if(not good()) return nullptr;
    consume();

    return std::make_unique<DeclarationStatement>(
      std::move(id), 
      std::move(expr), 
      std::move(type), 
      constant
    );
  }

  auto Parser::parseFunctionStatement() noexcept -> Box<Statement> {
    consume(); // fn

    expect(
      Token::Type::IDENTIFIER, 
      "Expected an identifier after keyword 'fn', got '{}'"f.format(peek().getLiteral())
    );
    if(not good()) return nullptr;

    std::string name { consume().getLiteral() };

    expect(Token::Type::LPAREN, "Expected '(' after function name, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    auto function = std::make_unique<FunctionStatement>(std::move(name));

    if(peek().getType() == Token::Type::IDENTIFIER) {
      do {
        expect(
          Token::Type::IDENTIFIER, 
          "Expected a function parameter name, got '{}'"f.format(peek().getLiteral())
        );
        if(not good()) return nullptr;

        std::string id { consume().getLiteral() };

        expect(
          Token::Type::COLUMN, 
          "Expected ':' after identifier, got '{}'"f.format(peek().getLiteral())
        );

        if(not good()) return nullptr;
        consume();

        expect(
          Token::Type::IDENTIFIER, 
          "Expected a type after ':', got '{}'"f.format(peek().getLiteral())
        );
        if(not good()) return nullptr;

        auto type = parseType(consume());
        if(not good()) return nullptr;

        function->args[id] = std::move(type);

      } while(peek().getType() == Token::Type::COMMA and consume().getType() == Token::Type::COMMA);
    }

    expect(Token::Type::RPAREN, "Expected ')' at the end of function parameter list, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    expect(Token::Type::ARROW, "Expected '->' after function parameter list, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    expect(Token::Type::IDENTIFIER, "Expected function return type after '->', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;

    auto return_type = parseType(consume());
    if(not good()) return nullptr;

    function->return_type = std::move(return_type);

    if(peek().getType() == Token::Type::LBRACE) {
      auto block = parseBlockStatement();
      if(not good()) return nullptr;
      function->block = std::move(block);

    } else if(peek().getType() == Token::Type::IMPLIES) {
      consume(); // '=>'
      
      auto expr = parseExpression();
      if(not good()) return nullptr;
      
      expect(
        Token::Type::SEMICOL,
        "Expected ';' at the end of an inline function declaration, got '{}'"f
        .format(peek().getLiteral())
      );
      if(not good()) return nullptr;
      consume(); // ';'

      auto block = std::make_unique<BlockStatement>();
      auto return_stmt = std::make_unique<ReturnStatement>(std::move(expr));
      block->add(std::move(return_stmt));
      function->block = std::move(block);
    } else {
      expect(
        Token::Type::LBRACE,
        "Expected either '{{' to open a block or '=>' after return type, got '{}'"f
        .format(peek().getLiteral())
      );
      return nullptr;
    }

    return std::move(function);
  }

  auto Parser::parseEnumStatement() noexcept -> Box<Statement> {
    consume(); // enum

    expect(Token::Type::IDENTIFIER, "Expected an identifier after keyword 'enum', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    
    auto _enum = std::make_unique<EnumStatement>(std::string{ consume().getLiteral()} );
    
    expect(Token::Type::LBRACE, "Expected '{{' after enum name, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    if(peek().getType() == Token::Type::IDENTIFIER) {
      do {
        _enum->add(std::string{ consume().getLiteral() });
      } while(peek().getType() == Token::Type::COMMA and consume().getType() == Token::Type::COMMA);
    }

    expect(Token::Type::RBRACE, "Expected '}}' at the end of an enum, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();
    
    return std::move(_enum);
  }
  
  auto Parser::parseStructStatement() noexcept -> Box<Statement> {
    consume(); // struct

    expect(Token::Type::IDENTIFIER, "Expected an identifier after keyword 'struct', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    
    auto _struct = std::make_unique<StructStatement>(std::string{ consume().getLiteral() });
    
    expect(Token::Type::LBRACE, "Expected '{{' after struct name, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    while(peek().getType() != Token::Type::END and peek().getType() != Token::Type::RBRACE) {
      expect(
        Token::Type::IDENTIFIER, 
        "Expected a struct field name, got '{}'"f.format(peek().getLiteral())
      );
      if(not good()) return nullptr;

      std::string id { consume().getLiteral() };

      expect(
        Token::Type::COLUMN, 
        "Expected ':' after identifier, got '{}'"f.format(peek().getLiteral())
      );

      if(not good()) return nullptr;
      consume();

      expect(
        Token::Type::IDENTIFIER, 
        "Expected a type after ':', got '{}'"f.format(peek().getLiteral())
      );
      if(not good()) return nullptr;

      auto type = parseType(consume());

      expect(
        Token::Type::SEMICOL,
        "Expected ';' after struct field, got '{}'"f.format(peek().getLiteral())
      );
      if(not good()) return nullptr;
      consume();

      _struct->fields[id] = std::move(type);
    }

    expect(Token::Type::RBRACE, "Expected '}}' at the end of a struct, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();
    
    return std::move(_struct);
  }

  auto Parser::parseNamespaceStatement() noexcept -> Box<Statement> {
    consume(); // namespace

    expect(Token::Type::IDENTIFIER, "Expected an identifier after keyword 'namespace', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;

    std::string id { consume().getLiteral() };
    
    expect(Token::Type::SEMICOL, "Expected ';' after a namespace statement, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;

    consume();
    
    return std::make_unique<NamespaceStatement>(std::move(id));
  }

  auto Parser::parseUsingStatement() noexcept -> Box<Statement> {
    consume(); // using

    expect(Token::Type::IDENTIFIER, "Expected an identifier after keyword 'using', got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;

    std::string id { consume().getLiteral() };
    
    expect(Token::Type::SEMICOL, "Expected ';' after a using statement, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;

    consume();
    
    return std::make_unique<UsingStatement>(std::move(id));

  }

  auto Parser::parseBlockStatement() noexcept -> Box<BlockStatement> {
    
    expect(Token::Type::LBRACE, "Expected '{{' to open a scope, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();
    
    auto block = std::make_unique<BlockStatement>();

    while(peek().getType() != Token::Type::END and peek().getType() != Token::Type::RBRACE) {
      auto stmt = parseStatement();
      if(not good()) return nullptr;

      block->add(std::move(stmt));
    }

    expect(Token::Type::RBRACE, "Expected '}}' to close a scope, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    return std::move(block);
  }

  auto Parser::parseIfStatement() noexcept -> Box<Statement> {
    consume(); // if or elif

    auto stmt = std::make_unique<IfStatement>();
    stmt->condition = parseExpression();
    if(not good()) return nullptr;

    stmt->block = parseBlockStatement();

    if(peek().getType() == Token::Type::ELIF) {
      stmt->alternative = parseIfStatement();
      if(not good()) return nullptr;

    } else if(peek().getType() == Token::Type::ELSE) {
      consume(); // else
      stmt->alternative = parseBlockStatement();
      if(not good()) return nullptr;
  }

    return std::move(stmt);
  }

  auto Parser::parseWhileStatement() noexcept -> Box<Statement> {
    consume(); // while

    auto expr = parseExpression();
    if(not good()) return nullptr;

    auto block = parseBlockStatement();
    if(not good()) return nullptr;

    return std::make_unique<WhileStatement>(std::move(expr), std::move(block));
  }
  
  auto Parser::parseReturnStatement() noexcept -> Box<Statement> {
    consume(); // return
    auto expr = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::SEMICOL, "Expected ';' after expression, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    return std::make_unique<ReturnStatement>(std::move(expr));
  }

  auto Parser::parseForStatement() noexcept -> Box<Statement> {
    consume(); // for

    auto stmt = std::make_unique<ForStatement>();
    stmt->initializer = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::SEMICOL, "Expected ';' after initializer, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    stmt->condition = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::SEMICOL, "Expected ';' after condition, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();
    
    stmt->modifier = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::SEMICOL, "Expected ';' after modifier, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    stmt->block = parseBlockStatement();
    if(not good()) return nullptr;

    return std::move(stmt);
  }

  auto Parser::parseExpressionStatement() noexcept -> Box<Statement> {
    auto expr = parseExpression();
    if(not good()) return nullptr;

    expect(Token::Type::SEMICOL, "Expected ';' after expression, got '{}'"f.format(peek().getLiteral()));
    if(not good()) return nullptr;
    consume();

    return std::make_unique<ExpressionStatement>(std::move(expr));
  }

}
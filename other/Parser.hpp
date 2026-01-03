#pragma once

#include "Ast.hpp"
#include "Token.hpp"
#include "Error.hpp"

namespace fridayc {

  class Parser {
    std::vector<Error> error_queue { };
    std::vector<Token> tokens      { };
    u64           pos              { 0 };
    bool          panic_mode       { false };

    public:
    /// @brief Construct a parser from source code
    /// @param tokens token stream
    Parser(std::vector<Token> tokens) noexcept;

    /// @brief Move constructor
    /// @param other rvalue reference to the moved object
    Parser(Parser&& other) noexcept = default;

    /// @brief Parses the token stream
    /// @return abstract syntax tree or errors
    auto parse() -> std::tuple<Program, std::vector<Error>>;
    
    private:
    using PrefixParser    = Box<Expression>(Parser::*)(Token);
    using InfixParser     = Box<Expression>(Parser::*)(Box<Expression>, Token);    
    using StatementParser = Box<Statement>(Parser::*)(); 
    
    enum struct Precedence : u16 {
      LOWEST         = 0,
      ASSIGNMENT     = 20,
      OR             = 30,
      AND            = 40,
      BIT_OR         = 50,
      BIT_AND        = 60,
      EQUALITY       = 70,
      INEQUALITY     = 80,
      SHIFT          = 90,      
      ADDTIVE        = 100,
      MULTIPLICATIVE = 110,
      PREFIX         = 120,
      SUBSCRIPT      = 130,
      FUNCTION_CALL  = 130,
      MEMBER_ACCESS  = 140,
      HIGHEST        = 150
    };

    static const std::map<Token::Type, StatementParser> stmtParsers;
    static const std::map<Token::Type, StatementParser> topLevelStmtParsers;
    static const std::map<Token::Type, PrefixParser>    prefixParsers;
    static const std::map<Token::Type, InfixParser>     infixParsers;
    static const std::map<Token::Type, Precedence>      precedences;

    auto good() const noexcept -> bool;
    auto expect(Token::Type type, std::string error) -> void;

    auto errorAt(Token const& token, std::string error) noexcept -> void;
    auto synchronize() noexcept -> void;

    auto peek(u64 ahead = 0) -> Token const&;
    auto consume() noexcept -> Token;

    auto parseStatement() noexcept -> Box<Statement>;
    auto parseTopLevelStatement() noexcept -> Box<Statement>;
    auto parseExpressionStatement() noexcept -> Box<Statement>;
    auto parseDeclarationStatement() noexcept -> Box<Statement>;
    auto parsePrintStatement() noexcept -> Box<Statement>;
    auto parseIfStatement() noexcept -> Box<Statement>;
    auto parseForStatement() noexcept -> Box<Statement>;
    auto parseWhileStatement() noexcept -> Box<Statement>;
    auto parseFunctionStatement() noexcept -> Box<Statement>;
    auto parseReturnStatement() noexcept -> Box<Statement>;
    auto parseEnumStatement() noexcept -> Box<Statement>;
    auto parseStructStatement() noexcept -> Box<Statement>;
    auto parseNamespaceStatement() noexcept -> Box<Statement>;
    auto parseUsingStatement() noexcept -> Box<Statement>;
    auto parseBlockStatement() noexcept -> Box<BlockStatement>;

    auto parseExpression(Precedence precedence = Precedence::LOWEST) noexcept -> Box<Expression>;
    auto parsePrefix(Token token) noexcept -> Box<Expression>;
    auto parseLeftAssocInfix(Box<Expression> left, Token token) noexcept -> Box<Expression>;
    auto parseRightAssocInfix(Box<Expression> left, Token token) noexcept -> Box<Expression>;
        
    auto parseIdentifier(Token token) noexcept -> Box<Expression>;
    auto parseArrayLiteral(Token token) noexcept -> Box<Expression>;
    auto parseObjectLiteral(Token token) noexcept -> Box<Expression>;
    auto parseBoolLiteral(Token token) noexcept -> Box<Expression>;
    auto parseStringLiteral(Token token) noexcept -> Box<Expression>;
    auto parseFloatLiteral(Token token) noexcept -> Box<Expression>;
    auto parseIntLiteral(Token token) noexcept -> Box<Expression>;
    auto parseCharLiteral(Token token) noexcept -> Box<Expression>;
    auto parseGroupedExpression( Token token) noexcept -> Box<Expression>;
    auto parseFunctionCall(Box<Expression> left, Token token) noexcept -> Box<Expression>;
    auto parseSubscript(Box<Expression> left, Token token) noexcept -> Box<Expression>;
    auto parseType(Token token) noexcept -> Box<TypeExpression>;

    static auto getPrefixParser(Token::Type type) noexcept -> PrefixParser;
    static auto getInfixParser(Token::Type type) noexcept -> InfixParser;
    static auto getPrecedence(Token::Type type) noexcept -> Precedence;

  };
}

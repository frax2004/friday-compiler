#pragma once

#include "Traits.hpp"
#include "Token.hpp"
#include "Visitable.hpp"
#include "Expression.hpp"

namespace fridayc {

  /// @brief Interface for statements
  struct Statement : public Visitable {

    /// @brief Default constructor
    Statement() noexcept = default;

    /// @brief Default destructor
    virtual ~Statement() noexcept = default;

    /// @brief Converts a statement into a std::string
    /// @return std::string representation
    virtual auto toString() const noexcept -> std::string = 0;
  };

  inline namespace statements {

    /// @brief Expression statement
    struct ExpressionStatement : public Statement {
      /// @brief Value of the expression
      Box<Expression> expr;

      /// @brief Constructs an expression statement
      /// @param expr the value of the expression
      ExpressionStatement(Box<Expression> expr) noexcept;

      /// @brief Converts an expression statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };

    /// @brief Print statement
    struct PrintStatement : public Statement {
      /// @brief Value of the expression
      Box<Expression> expr;

      /// @brief Constructs return statement
      /// @param expr the value of the expression
      PrintStatement(Box<Expression> expr) noexcept;

      /// @brief Converts a return statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };

    /// @brief Return statement
    struct ReturnStatement : public Statement {
      /// @brief Value of the expression
      Box<Expression> expr;

      /// @brief Constructs return statement
      /// @param expr the value of the expression
      ReturnStatement(Box<Expression> expr) noexcept;

      /// @brief Converts a return statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };

    /// @brief Group of statements brace-enclosed
    struct BlockStatement : public Statement, public Container<Box<Statement>> {

      BlockStatement() noexcept = default;

      /// @brief Converts block statement to a std::string
      /// @returns std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };
    
    /// @brief If statement
    struct IfStatement : public Statement {

      /// @brief Value of the statements block
      Box<BlockStatement> block;

      /// @brief Value of the condition expression
      Box<Expression> condition;

      /// @brief Optional value of the alternative statement
      Box<Statement> alternative;
      
      /// @brief Converts if statement to a std::string
      /// @returns std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };
      
    /// @brief While statement
    struct WhileStatement : public Statement {

      /// @brief Value of the statements block
      Box<BlockStatement> block;
      
      /// @brief Value of the condition expression
      Box<Expression> condition;

      /// @brief Constructs a while statement
      /// @param condition the value of the condition expression
      WhileStatement(Box<Expression> condition, Box<BlockStatement> block) noexcept;

      /// @brief Converts while statement to a std::string
      /// @returns std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };
      
    /// @brief For statement
    struct ForStatement : public Statement {

      /// @brief Value of the statements block
      Box<BlockStatement> block;
      
      /// @brief Value of the initializer expression
      Box<Expression> initializer;

      /// @brief Value of the condition expression
      Box<Expression> condition;

      /// @brief Value of the modifier expression
      Box<Expression> modifier;

      /// @brief Converts for statement to a std::string
      /// @returns std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };
    
    /// @brief Struct statement
    struct StructStatement : public Statement {

      /// @brief Constructs a struct statement
      /// @param name the name of the struct
      StructStatement(std::string name) noexcept;

      /// @brief Converts a struct statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

      /// @brief Value of the name of the struct
      std::string name;

      std::map<std::string, Box<TypeExpression>> fields;
    };

    /// @brief Enum statement
    struct EnumStatement : public Statement, public Container<std::string> {
      
      /// @brief Constructs an enum statement
      /// @param name the name of the enum
      EnumStatement(std::string name) noexcept;

      /// @brief Converts an enum statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

      /// @brief Value of the name of the enum
      std::string name;
    };
    
    /// @brief Function statement
    struct FunctionStatement : public Statement {
      
      /// @brief Constructs a function statement
      /// @param name the function name
      FunctionStatement(std::string name) noexcept;

      /// @brief Converts a function statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

      /// @brief Value of the statements block
      Box<BlockStatement> block;
      
      /// @brief Value of the return type
      Box<TypeExpression> return_type;

      /// @brief Value of the name of the function
      std::string name;

      /// @brief Function parameter names mapped with types
      std::map<std::string, Box<TypeExpression>> args;
    };

    /// @brief Namespace statement
    struct NamespaceStatement : public Statement {

      /// @brief Value of the name of the namespace
      std::string name;

      /// @brief Constructs a namespace statement
      /// @param name the name of the namespace
      NamespaceStatement(std::string name) noexcept;

      /// @brief Converts a namespace statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Using statement
    struct UsingStatement : public Statement {

      /// @brief Value of the name of the identifier
      std::string name;

      /// @brief Constructs a using statement
      /// @param name the name of the identifier
      UsingStatement(std::string name) noexcept;

      /// @brief Converts a using statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Declaration statement
    struct DeclarationStatement : public Statement {

      /// @brief Value of the name of the declared variable
      std::string id;
      
      /// @brief Value of the type of the variable
      Box<TypeExpression> type;

      /// @brief Value of the expression of the declared variable
      Box<Expression> expr;

      /// @brief Tells whether the declared variable is a constant
      bool constant;
    
      /// @brief Constructs a declaration statement
      /// @param id the name of the declared variable
      /// @param expr the expression assigned to the declared variable
      /// @param constant true to declare variable as a constant
      DeclarationStatement(std::string id, Box<Expression> expr, Box<TypeExpression> type, bool constant = false) noexcept;

      /// @brief Converts a declaration statement into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };

  }
}
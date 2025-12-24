#pragma once

#include "Token.hpp"
#include "Visitable.hpp"
#include "Traits.hpp"

namespace fridayc {

  /// @brief Interface for expressions
  struct Expression : public Visitable {

    /// @brief Default constructor
    Expression() noexcept = default;

    /// @brief Default destructor
    virtual ~Expression() noexcept = default;

    /// @brief Converts an expression into a std::string
    /// @return std::string representation
    virtual auto toString() const noexcept -> std::string = 0;
  };

  inline namespace expressions {

    /// @brief Identifier expression
    struct Identifier : public Expression {

      /// @brief Value of the identifier
      std::string id;

      /// @brief Constructs an identifier
      /// @param id name of the identifier
      Identifier(std::string id) noexcept;

      /// @brief Converts an identifier expression into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Bool literal expression
    struct BoolLiteral : public Expression {
      /// @brief Value of the bool literal
      Boolean value;

      /// @brief Constructs a bool literal
      /// @param value the value of the bool literal
      BoolLiteral(Boolean value) noexcept;
      
      /// @brief Converts a bool literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief std::any literal expression
    struct ObjectLiteral : public Expression {
      /// @brief Value of the object literal
      Token value;

      /// @brief Constructs a object literal
      /// @param value the value of the object literal
      ObjectLiteral(Token value) noexcept;

      /// @brief Converts a object literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief std::string literal expression
    struct StringLiteral : public Expression {
      /// @brief Value of the std::string literal
      std::string value;

      /// @brief Constructs a std::string literal
      /// @param value the value of the std::string literal
      StringLiteral(std::string value) noexcept;

      /// @brief Converts a std::string literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };
    
    /// @brief Float literal expression
    struct FloatLiteral : public Expression {
      /// @brief Value of the float literal
      Double value;

      /// @brief Constructs a float literal
      /// @param value the value of the float literal
      FloatLiteral(Double value) noexcept;

      /// @brief Converts a float literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Int literal expression
    struct IntLiteral : public Expression {
      /// @brief Value of the int literal
      Long value;

      /// @brief Constructs an int literal
      /// @param value the value of the int literal
      IntLiteral(Long value) noexcept;
      
      /// @brief Converts an integer literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Char literal expression
    struct CharLiteral : public Expression {

      ///@brief Value of the char literal
      Character value;

      /// @brief Constructs a char literal
      /// @param value the value char literal
      CharLiteral(Character value) noexcept;

      /// @brief Converts a character literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Function call expression
    struct ArrayLiteral : public Expression, public Container<Box<Expression>> {

      /// @brief Constructs an array literal
      ArrayLiteral() noexcept = default;

      /// @brief Converts an array literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;
    };

    /// @brief Type expression
    struct TypeExpression : public Expression {
      
      /// @brief Constructs a type expression
      TypeExpression(std::string name, u32 dimensions) noexcept;
      
      /// @brief Converts an array literal into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

      /// @brief Name of the type
      std::string name;

      /// @brief Dimensions of the type
      u32 dimensions;
    };

    /// @brief Prefix expression
    struct PrefixExpression : public Expression {
      
      /// @brief Value of the expression
      Box<Expression> expr;

      /// @brief Prefix operator
      Token::Type oper;

      /// @brief Constructs a prefix expression
      /// @param prefix_operator the prefix operator
      /// @param expression the expression
      PrefixExpression(Token::Type prefix_operator, Box<Expression> expression) noexcept;

      /// @brief Converts a prefix expression into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Infix expression
    struct InfixExpression : public Expression {

      /// @brief Value of the left-hand-side expression
      Box<Expression> lhs; 

      /// @brief Value of the right-hand-side expression
      Box<Expression> rhs;

      /// @brief Infix operator
      Token::Type oper;

      /// @brief Constructs an infix expression
      /// @param left the left-hand-side expression
      /// @param infix_operator the infix operator
      /// @param right the right-hand-side expression
      InfixExpression(Box<Expression> left, Token::Type infix_operator, Box<Expression> right) noexcept;

      /// @brief Converts an infix expression into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

    /// @brief Function call expression
    struct CallExpression : public Expression, public Container<Box<Expression>> {

      /// @brief Constructs a function call
      /// @param function the value of the function name
      CallExpression(Box<Expression> function) noexcept;

      /// @brief Converts a call expression into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

      /// @brief Value of the function name
      Box<Expression> function;
    };

    /// @brief Subcript expression
    struct SubscriptExpression : public Expression {

      /// @brief Value of the array name
      Box<Expression> array;

      /// @brief Value of the index
      Box<Expression> index;

      /// @brief Constructs a subscript expression
      /// @param array the value of the array name
      /// @param index the value of the index
      SubscriptExpression(Box<Expression> array, Box<Expression> index) noexcept;

      /// @brief Converts a subscript expression into a std::string
      /// @return std::string representation
      auto toString() const noexcept -> std::string override;

      /// @brief Visit this node
      /// @param visitor the visitor object
      auto operator()(Visitor& visitor) noexcept -> std::any override;

    };

  }
}
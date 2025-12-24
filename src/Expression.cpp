#include "Expression.hpp"
#include "Visitor.hpp"
#include "FormatString.hpp"
#include "Wrappers.hpp"

namespace fridayc {

  inline namespace expressions {

    Identifier::Identifier(std::string id) noexcept 
      : id { std::move(id) }
    {}
    
    auto Identifier::toString() const noexcept -> std::string {
      return "{{\"type\": \"Identifier\", \"id\": \"{}\"}}"f.format(id);
    }

    auto Identifier::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    BoolLiteral::BoolLiteral(Boolean value) noexcept
      : value { value }
    {}
      
    auto BoolLiteral::toString() const noexcept -> std::string {
      return "{{\"type\": \"BoolLiteral\", \"value\": \"{}\"}}"f.format(value.unwrap());
    }

    auto BoolLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    ObjectLiteral::ObjectLiteral(Token value) noexcept
      : value { std::move(value) }
    {}
      
    auto ObjectLiteral::toString() const noexcept -> std::string {
      return "{{\"type\": \"ObjectLiteral\", \"value\": \"{}\"}}"f.format(value.getLiteral());
    }

    auto ObjectLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    StringLiteral::StringLiteral(std::string value) noexcept 
      : value { std::move(value) }
    {}
    
    auto StringLiteral::toString() const noexcept -> std::string {
      return "{{\"type\": \"StringLiteral\", \"value\": {}}}"f.format(value);
    }

    auto StringLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    FloatLiteral::FloatLiteral(Double value) noexcept 
      : value { value }
    {}
    
    auto FloatLiteral::toString() const noexcept -> std::string {
      return "{{\"type\": \"FloatLiteral\", \"value\": {}}}"f.format(value.unwrap());
    }
  
    auto FloatLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    IntLiteral::IntLiteral(Long value) noexcept 
      : value { value }
    {}
    
    auto IntLiteral::toString() const noexcept -> std::string {
      return "{{\"type\": \"IntLiteral\", \"value\": {}}}"f.format(value.unwrap());
    }
    
    auto IntLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
  
    CharLiteral::CharLiteral(Character value) noexcept 
      : value { value }
    {}
    
    auto CharLiteral::toString() const noexcept -> std::string {
      return "{{\"type\": \"CharLiteral\", \"value\": \"{}\"}}"f.format(value.unwrap());
    }

    auto CharLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    auto ArrayLiteral::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"ArrayLiteral\", \"values\": [{}]}}", 
        std::ranges::to<std::string>(
          *this
          | std::views::transform(Box<Expression>::operator*)
          | std::views::transform(Expression::toString)
          | std::views::join_with(", "s)
        )
      );
    }

    auto ArrayLiteral::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    TypeExpression::TypeExpression(std::string name, u32 dimensions) noexcept
      : name { std::move(name) }
      , dimensions { dimensions }
    {}

    auto TypeExpression::toString() const noexcept -> std::string {
      return "{{\"type\": \"TypeExpression\", \"name\": \"{}\", \"dimensions\": {}}}"f.format(name, dimensions);
    }

    auto TypeExpression::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    PrefixExpression::PrefixExpression(Token::Type prefix_operator, Box<Expression> expression) noexcept 
      : oper { prefix_operator }
      , expr { std::move(expression) }
    {}
  
    auto PrefixExpression::toString() const noexcept -> std::string {
      return "{{\"type\": \"PrefixExpression\", \"oper\": \"{}\", \"expr\": {}}}"f.format(Token::names()[oper], expr->toString());
    }
    
    auto PrefixExpression::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    InfixExpression::InfixExpression(Box<Expression> left, Token::Type infix_operator, Box<Expression> right) noexcept 
      : lhs { std::move(left) }
      , rhs { std::move(right) }
      , oper { infix_operator }
    {}

    auto InfixExpression::toString() const noexcept -> std::string {
      return "{{\"type\": \"InfixExpression\", \"lhs\": {}, \"oper\": \"{}\", \"rhs\": {}}}"f.format(lhs->toString(), Token::names()[oper], rhs->toString());
    }

    auto InfixExpression::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    CallExpression::CallExpression(Box<Expression> function) noexcept 
      : function { std::move(function) }
    {}

    auto CallExpression::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"CallExpression\", \"function\": {}, \"args\": [{}]}}", 
        function->toString(), 
        std::ranges::to<std::string>(
          *this
          | std::views::transform(Box<Expression>::operator*)
          | std::views::transform(Expression::toString)
          | std::views::join_with(", "s)
        )
      );
      
    }

    auto CallExpression::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    SubscriptExpression::SubscriptExpression(Box<Expression> array, Box<Expression> index) noexcept 
      : array { std::move(array) }
      , index { std::move(index) }
    {}

    auto SubscriptExpression::toString() const noexcept -> std::string {
      return "{{\"type\": \"SubscriptExpression\", \"array\": {}, \"index\": {}}}"f.format(array->toString(), index->toString());
    }
    
    auto SubscriptExpression::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }    
  }
}
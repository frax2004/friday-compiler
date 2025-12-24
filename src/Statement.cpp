#include "Statement.hpp"
#include "Expression.hpp"
#include "Visitor.hpp"

namespace fridayc {
  inline namespace statements {

    ExpressionStatement::ExpressionStatement(Box<Expression> expr) noexcept
      : expr { std::move(expr) }
    {}

    auto ExpressionStatement::toString() const noexcept -> std::string {
      return "{{\"type\": \"ExpressionStatement\", \"expr\": {}}}"f.format(expr->toString());
    }
    
    auto ExpressionStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    ReturnStatement::ReturnStatement(Box<Expression> expr) noexcept
      : expr { std::move(expr) }
    {}

    auto ReturnStatement::toString() const noexcept -> std::string {
      return "{{\"type\": \"ReturnStatement\", \"expr\": {}}}"f.format(expr->toString());
    }

    auto ReturnStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    PrintStatement::PrintStatement(Box<Expression> expr) noexcept
      : expr { std::move(expr) }
    {}

    auto PrintStatement::toString() const noexcept -> std::string {
      return "{{\"type\": \"PrintStatement\", \"expr\": {}}}"f.format(expr->toString());
    }

    auto PrintStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    auto BlockStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"BlockStatement\", \"statements\": [{}]}}",
        std::ranges::to<std::string>(
          *this
          | std::views::transform(Box<Statement>::operator*)
          | std::views::transform(Statement::toString)
          | std::views::join_with(", "s)
        )
      );
    }
    
    auto BlockStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    auto IfStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"IfStatement\", \"condition\": {}, \"block\": {}{}}}",
        condition->toString(),
        block->toString(),
        alternative ? ", \"alternative\": {}"f.format(alternative->toString()) : ""
      );
    }
    
    auto IfStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    WhileStatement::WhileStatement(Box<Expression> condition, Box<BlockStatement> block) noexcept
      : condition { std::move(condition) }
      , block { std::move(block) }
    {}

    auto WhileStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"WhileStatement\", \"condition\": {}, \"block\": {}}}",
        condition->toString(),
        block->toString()
      );
    }
    
    auto WhileStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    auto ForStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"ForStatement\", \"initializer\": {}, \"condition\": {}, \"modifier\": {}, \"block\": {}}}",
        initializer->toString(),
        condition->toString(),
        modifier->toString(),
        block->toString()
      );
    }

    auto ForStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    StructStatement::StructStatement(std::string name) noexcept 
      : name { std::move(name) }
    {}

    auto StructStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"StructStatement\", \"fields\": [{}]}}", 
        std::ranges::to<std::string>(
          fields
          | std::views::transform([](auto const& pair) { 
            return "{{\"type\": \"Field\", \"identifier\": \"{}\", \"datatype\": {}}}"f
            .format(pair.first, pair.second->toString());
          })
          | std::views::join_with(", "s)
        )
      );      
    }

    auto StructStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    EnumStatement::EnumStatement(std::string name) noexcept 
      : name { std::move(name) }
    {}

    auto EnumStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"EnumStatement\", \"constants\": [{}]}}", 
        std::ranges::to<std::string>(
          *this 
          | std::views::transform([](std::string constant) { return '"' + constant + '"'; })
          | std::views::join_with(", "s)
        )
      );
    }

    auto EnumStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    FunctionStatement::FunctionStatement(std::string name) noexcept
      : name { std::move(name) }
    {}
      
    auto FunctionStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"FunctionStatement\", \"args\": [{}], \"block\": {}}}", 
        std::ranges::to<std::string>(
          args
          | std::views::transform([](auto const& pair) { 
            return "{{\"type\": \"Parameter\", \"identifier\": \"{}\", \"datatype\": {}}}"f
            .format(pair.first, pair.second->toString());
          })
          | std::views::join_with(", "s)
        ),
        block->toString()
      );
    }

    auto FunctionStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    NamespaceStatement::NamespaceStatement(std::string name) noexcept 
      : name { std::move(name) }
    {}

    auto NamespaceStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"NamespaceStatement\", \"name\": {}}}", 
        name
      );
    }

    auto NamespaceStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
    
    UsingStatement::UsingStatement(std::string name) noexcept 
      : name { std::move(name) }
    {}

    auto UsingStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"UsingStatement\", \"identifier\": {}}}", 
        name
      );
    }

    auto UsingStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }

    DeclarationStatement::DeclarationStatement(std::string id, Box<Expression> expr, Box<TypeExpression> type, bool constant) noexcept
      : id { std::move(id) }
      , type { std::move(type) }
      , expr { std::move(expr) }
      , constant { constant }
    {}

    auto DeclarationStatement::toString() const noexcept -> std::string {
      return std::format(
        "{{\"type\": \"DeclarationStatement\", \"constant\": \"{}\", \"identifier\": \"{}\", \"datatype\": {}, \"value\": {}}}", 
        constant,
        id,
        type->toString(),
        expr ? expr->toString() : "\"\""
      );
    }

    auto DeclarationStatement::operator()(Visitor& visitor) noexcept -> std::any {
      return visitor.visit(*this);
    }
   
  }
}
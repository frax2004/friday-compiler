#pragma once

#include "Ast.hpp"
#include "Visitable.hpp"

namespace fridayc {

  struct Visitor {

    constexpr Visitor() noexcept = default;
    constexpr virtual ~Visitor() = default;
    
    constexpr virtual auto operator()(Expression& arg) noexcept -> std::any final;
    constexpr virtual auto operator()(Statement& arg) noexcept -> std::any final;

    virtual auto operator()(Identifier& arg) noexcept -> std::any = 0;
    virtual auto operator()(BoolLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(ObjectLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(StringLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(FloatLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(IntLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(CharLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(PrefixExpression& arg) noexcept -> std::any = 0;
    virtual auto operator()(InfixExpression& arg) noexcept -> std::any = 0;
    virtual auto operator()(CallExpression& arg) noexcept -> std::any = 0;
    virtual auto operator()(SubscriptExpression& arg) noexcept -> std::any = 0;
    virtual auto operator()(TypeExpression& arg) noexcept -> std::any = 0;
    virtual auto operator()(ExpressionStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(ArrayLiteral& arg) noexcept -> std::any = 0;
    virtual auto operator()(ReturnStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(PrintStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(BlockStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(IfStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(WhileStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(ForStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(StructStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(EnumStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(FunctionStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(NamespaceStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(UsingStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(DeclarationStatement& arg) noexcept -> std::any = 0;
    virtual auto operator()(Program& arg) noexcept -> std::any = 0;

    template<std::derived_from<Visitable> T>
    constexpr auto visit(T& visitable) noexcept -> std::any;
  };

}

#include "Visitor.inl"
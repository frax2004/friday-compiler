#pragma once

#include "Expression.hpp"
#include "Statement.hpp"

namespace fridayc {

  /// @brief A program is a list of statements
  struct Program final : public Visitable {

    /// @brief Default constructor
    Program() noexcept = default;

    auto toString() const noexcept -> std::string;

    auto operator()(Visitor& visitor) noexcept -> std::any override;

    /// @brief Block of statements
    Box<BlockStatement> block;
  };

}


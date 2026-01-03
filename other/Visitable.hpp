#pragma once

namespace fridayc {

  struct Visitor;
  
  struct Visitable {
    constexpr Visitable() noexcept = default;
    constexpr virtual ~Visitable() noexcept = default;
    virtual auto operator()(Visitor& visitor) noexcept -> std::any = 0;
  };

}
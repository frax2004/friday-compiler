#ifdef __INTELLISENSE__
#include "Visitor.hpp"
#endif

namespace fridayc {
  template<std::derived_from<Visitable> T>
  constexpr auto Visitor::visit(T& visitable) noexcept -> std::any {
    return std::invoke(*this, visitable);
  }

  constexpr auto Visitor::operator()(Expression& arg) noexcept -> std::any {
    return std::invoke(arg, *this);
  }

  constexpr auto Visitor::operator()(Statement& arg) noexcept -> std::any {
    return std::invoke(arg, *this);
  }
}
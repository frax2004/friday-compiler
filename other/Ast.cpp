#include "Ast.hpp"
#include "Visitor.hpp"

namespace fridayc {

  auto Program::toString() const noexcept -> std::string {
    return "{{\"type\": \"Program\", \"block\": {}}}"f.format(block->toString());
  }
  
  auto Program::operator()(Visitor& visitor) noexcept -> std::any {
    return visitor.visit(*this);
  }
}
#include "Math.hpp"



auto main(int argc, const char** argv) -> int {
  using namespace fridayc;
  static_assert(math::cos(math::pi) == -1.0);
}
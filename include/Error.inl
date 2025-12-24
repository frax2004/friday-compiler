#ifdef __INTELLISENSE__
#include "Error.hpp"
#endif

namespace fridayc {

  constexpr Error::Error(std::string error, u32 row, u32 col, u32 length) noexcept
    : message { std::move(error) }
    , row { row }
    , col { col }
    , length { length }
  {}

}
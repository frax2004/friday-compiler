#ifdef __INTELLISENSE__
#include "FormatString.hpp"
#endif


namespace fridayc {

  template<class ... Args>
  constexpr auto FormatString::format(Args&& ...args) noexcept -> std::string {
    return std::vformat(data, std::make_format_args(args...));
  }
  
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wliteral-suffix\"")  

constexpr auto operator ""f(const i8* data, u64 length) noexcept -> fridayc::FormatString {
  return fridayc::FormatString { data };
}

_Pragma("GCC diagnostic pop")
#ifndef FRIDAYC_FORMAT_STRING_HPP
#define FRIDAYC_FORMAT_STRING_HPP

namespace fridayc {
  struct FormatString {
    const i8* data;

    template<class ... Args>
    constexpr auto format(Args&& ...args) noexcept -> std::string;
  };
}

_Pragma("GCC diagnostic push")
_Pragma("GCC diagnostic ignored \"-Wliteral-suffix\"")

constexpr auto operator ""f(const i8* data, u64 length) noexcept -> fridayc::FormatString;

_Pragma("GCC diagnostic pop")


#include "FormatString.inl"

#endif
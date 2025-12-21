#ifndef FRIDAYC_CTYPES_HPP
#define FRIDAYC_CTYPES_HPP

extern "C" {
  using i8 = char;
  using i16 = short;
  using i32 = int;
  using i64 = long long;

  using u8 = unsigned char;
  using u16 = unsigned short;
  using u32 = unsigned int;
  using u64 = unsigned long long;

  using f32 = float;
  using f64 = double;

  using byte = char;

  using int8 = char;
  using int16 = short;
  using int32 = int;
  using int64 = long long;

  using uint8 = unsigned char;
  using uint16 = unsigned short;
  using uint32 = unsigned int;
  using uint64 = unsigned long long;

  using float32 = float;
  using float64 = double;  
}

using namespace std::string_literals;
using namespace std::string_view_literals;


#endif
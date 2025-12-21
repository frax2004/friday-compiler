#ifdef __INTELLISENSE__
#include "Wrappers.hpp"
#endif


namespace fridayc {
  constexpr Long::Long(value_type other) noexcept
    : value { other } 
  {}
  
  constexpr auto Long::operator=(value_type other) noexcept -> Long& {
    return (value = other), *this;
  }  
  
    
  constexpr Long::operator reference_type() noexcept { 
    return value; 
  }
  
  constexpr Long::operator value_type() const noexcept { 
    return value; 
  }
  
  
  constexpr auto Long::unwrap() const noexcept -> value_type { 
    return value; 
  }
  
  constexpr auto Long::parse(std::string_view str) -> Long {
    return std::stoll(str.data());
  }
  
  constexpr auto Long::wrap(value_type other) noexcept -> Long { 
    return Long{other}; 
  }
  
  constexpr auto Long::toString() const noexcept -> std::string {
    return std::to_string(value);
  }
  
  constexpr auto Long::sum(Long lhs, Long rhs) noexcept -> Long { 
    return Long{lhs + rhs}; 
  }
  
  constexpr auto Long::difference(Long lhs, Long rhs) noexcept -> Long { 
    return Long{lhs - rhs}; 
  }
  
  constexpr auto Long::product(Long lhs, Long rhs) noexcept -> Long { 
    return Long{lhs * rhs}; 
  }
  
  constexpr auto Long::quotient(Long lhs, Long rhs) -> Long { 
    if(rhs == 0LL) throw std::domain_error("Division by 0.");
    return Long{lhs / rhs}; 
  }
  
  constexpr auto Long::remainder(Long lhs, Long rhs) -> Long { 
    if(rhs == 0LL) throw std::domain_error("Division by 0.");
    return Long{lhs % rhs};
  }
  
  constexpr auto Long::isEven() const noexcept -> bool { 
    return unwrap() % 2 == 0; 
  }
  
  constexpr auto Long::isOdd() const noexcept -> bool { 
    return unwrap() % 2 != 0; 
  }
    
  constexpr Integer::Integer(value_type other) noexcept
    : value { other } 
  {}
  
  constexpr auto Integer::operator=(value_type other) noexcept -> Integer& {
    return (value = other), *this;
  }  
    
  constexpr Integer::operator reference_type() noexcept { 
    return value; 
  }
  
  constexpr Integer::operator value_type() const noexcept { 
    return value; 
  }
  
  constexpr auto Integer::unwrap() const noexcept -> value_type { 
    return value; 
  }
  
  constexpr auto Integer::parse(std::string_view value) -> Integer {
    return std::stoi(value.data());
  }
  
  constexpr auto Integer::wrap(value_type other) noexcept -> Integer { 
    return Integer{other}; 
  }
  
  constexpr auto Integer::toString() const noexcept -> std::string {
    return std::to_string(value);
  }
  
  constexpr auto Integer::sum(Integer lhs, Integer rhs) noexcept -> Integer { 
    return Integer{lhs + rhs}; 
  }

  constexpr auto Integer::difference(Integer lhs, Integer rhs) noexcept -> Integer { 
    return Integer{lhs - rhs}; 
  }
  
  constexpr auto Integer::product(Integer lhs, Integer rhs) noexcept -> Integer { 
    return Integer{lhs * rhs}; 
  }
  
  constexpr auto Integer::quotient(Integer lhs, Integer rhs) -> Integer { 
    if(rhs == 0) throw std::domain_error("Division by 0.");
    return Integer{lhs / rhs}; 
  }
  
  constexpr auto Integer::remainder(Integer lhs, Integer rhs) -> Integer { 
    if(rhs == 0) throw std::domain_error("Division by 0.");
    return Integer{lhs % rhs}; 
  }
  
  constexpr auto Integer::isEven() const noexcept -> bool { 
    return unwrap() % 2 == 0; 
  }
  
  constexpr auto Integer::isOdd() const noexcept -> bool { 
    return unwrap() % 2 != 0; 
  } 
  
  constexpr Double::Double(value_type other) noexcept 
    : value { other } 
  {}
  
  constexpr auto Double::operator=(value_type other) noexcept -> Double& {
    return (value = other), *this;
  }  
    
  constexpr Double::operator reference_type() noexcept { 
    return value; 
  }
  
  constexpr Double::operator value_type() const noexcept { 
    return value; 
  }
  
  
  constexpr auto Double::unwrap() const noexcept -> value_type { 
    return value; 
  }
  
  constexpr auto Double::parse(std::string_view value) -> Double {
    return std::stod(value.data());
  }
  
  constexpr auto Double::wrap(value_type other) noexcept -> Double { 
    return Double{other}; 
  }
  
  constexpr auto Double::toString() const noexcept -> std::string {
    return std::to_string(value);
  }
  
  constexpr auto Double::sum(Double lhs, Double rhs) noexcept -> Double { 
    return Double{lhs + rhs}; 
  }
  
  constexpr auto Double::difference(Double lhs, Double rhs) noexcept -> Double { 
    return Double{lhs - rhs}; 
  }
  
  constexpr auto Double::product(Double lhs, Double rhs) noexcept -> Double { 
    return Double{lhs * rhs}; 
  }
  
  constexpr auto Double::quotient(Double lhs, Double rhs) -> Double { 
    if(rhs == 0.) throw std::domain_error("Division by 0.");
    return Double{lhs / rhs}; 
  }
  
  constexpr auto Double::mantissa() const noexcept -> Double {
    return Double{unwrap() - std::floor(unwrap())};
  }  

  constexpr Float::Float(value_type other) noexcept
    : value { other } 
  {}
  
  constexpr auto Float::operator=(value_type other) noexcept -> Float& {
    return (value = other), *this;
  }  
  
  constexpr Float::operator reference_type() noexcept { 
    return value; 
  }
  
  constexpr Float::operator value_type() const noexcept { 
    return value; 
  }
  
  constexpr auto Float::unwrap() const noexcept -> value_type { 
    return value; 
  }
  
  constexpr auto Float::parse(std::string_view value) -> Float {
    return std::stof(value.data());
  }
  
  constexpr auto Float::wrap(value_type other) noexcept -> Float { 
    return Float{other}; 
  }
  
  constexpr auto Float::toString() const noexcept -> std::string {
    return std::to_string(value);
  }
  
  constexpr auto Float::sum(Float lhs, Float rhs) noexcept -> Float { 
    return Float{lhs + rhs}; 
  }
  
  constexpr auto Float::difference(Float lhs, Float rhs) noexcept -> Float { 
    return Float{lhs - rhs}; 
  }
  
  constexpr auto Float::product(Float lhs, Float rhs) noexcept -> Float { 
    return Float{lhs * rhs}; 
  }
  
  constexpr auto Float::quotient(Float lhs, Float rhs) -> Float { 
    if(rhs == 0.f) throw std::domain_error("Division by 0.");
    return Float{lhs / rhs}; 
  }
  
  constexpr auto Float::mantissa() const noexcept -> Float {
    return Float{unwrap() - std::floor(unwrap())};
  }

  constexpr Character::Character(value_type other) noexcept
    : value { other } 
  {}
  
  constexpr auto Character::operator=(value_type other) noexcept -> Character& {
    return (value = other), *this;
  }  
  
  constexpr Character::operator reference_type() noexcept { 
    return value; 
  }
  
  constexpr Character::operator value_type() const noexcept { 
    return value; 
  }
  
  constexpr auto Character::unwrap() const noexcept -> value_type { 
    return value; 
  }
  
  constexpr auto Character::parse(std::string_view value) -> Character {
    return value.at(0);
  }
  
  constexpr auto Character::wrap(value_type other) noexcept -> Character { 
    return Character{other}; 
  }
  
  constexpr auto Character::toString() const noexcept -> std::string {
    return std::string(1, value);
  } 
  
  constexpr auto Character::isAlpha() const noexcept -> bool {
    char c = unwrap();
    return (c >= 'A' and c <= 'Z') 
      or (c >= 'a' and c <= 'z')
      or c == '_';
  }
  
  constexpr auto Character::isDigit() const noexcept -> bool {
    char c = unwrap();
    return c >= '0' and c <= '9';
  }
  
  constexpr auto Character::isAlnum() const noexcept -> bool {
    return isAlpha() or isDigit();
  }
  
  constexpr auto Character::isSpace() const noexcept -> bool {
    char c = unwrap();
    return c == ' ' or c == '\t';
  }
  
  constexpr auto Character::isBreak() const noexcept -> bool {
    return unwrap() == '\n';
  }  

  constexpr Boolean::Boolean(value_type other) noexcept
    : value { other } 
  {}
  
  constexpr auto Boolean::operator=(value_type other) noexcept -> Boolean& {
    return (value = other), *this;
  }  
    
  constexpr Boolean::operator reference_type() noexcept { 
    return value; 
  }
  
  constexpr Boolean::operator value_type() const noexcept { 
    return value; 
  }
  
  constexpr auto Boolean::unwrap() const noexcept -> value_type { 
    return value; 
  }
  
  constexpr auto Boolean::parse(std::string_view value) -> Boolean {
    if(value == "true") return true;
    else if(value == "false") return false;
    else throw std::runtime_error("Failed to parse \"{}\" as Boolean"f.format(value));
    
    return false;
  }
  
  constexpr auto Boolean::wrap(value_type other) noexcept -> Boolean { 
    return Boolean{other}; 
  }
  
  constexpr auto Boolean::toString() const noexcept -> std::string {
    return std::to_string(value);
  }
  
  constexpr auto Boolean::logicAnd(Boolean lhs, Boolean rhs) noexcept -> Boolean {
    return lhs and rhs;
  }
  
  constexpr auto Boolean::logicOr(Boolean lhs, Boolean rhs) noexcept -> Boolean {
    return lhs or rhs;
  }
  
  constexpr auto Boolean::logicNot(Boolean value) noexcept -> Boolean {
    return not value;
  }
  
  constexpr auto Boolean::negate() const noexcept -> Boolean {
    return not value;
  }

}

constexpr auto operator""_I(u64 value) noexcept -> fridayc::Integer {
  return value;
}

constexpr auto operator""_L(u64 value) noexcept -> fridayc::Long {
  return value;
}

constexpr auto operator""_B(u64 value) noexcept -> fridayc::Boolean {
  return value;
}

constexpr auto operator""_F(long double value) noexcept -> fridayc::Float {
  return value;
} 

constexpr auto operator""_D(long double value) noexcept -> fridayc::Double {
  return value;
}

constexpr auto operator""_C(i8 value) noexcept -> fridayc::Character {
  return value;
}
#pragma once

namespace fridayc {


  struct Boolean final {
    
    using value_type = bool;
    using reference_type = bool&;
    using pointer_type = bool*;

    constexpr Boolean() noexcept = default;
    constexpr Boolean(Boolean const& other) noexcept = default;
    constexpr Boolean(Boolean && other) noexcept = default;
    constexpr Boolean(value_type other) noexcept;

    constexpr auto operator=(Boolean const& other) noexcept -> Boolean& = default;
    constexpr auto operator=(Boolean&& other) noexcept -> Boolean& = default;
    constexpr auto operator=(value_type other) noexcept -> Boolean&;  

    constexpr operator reference_type() noexcept;
    constexpr operator value_type() const noexcept;

    constexpr auto unwrap() const noexcept -> value_type;
    constexpr auto toString() const noexcept -> std::string;  
    constexpr auto negate() const noexcept -> Boolean;

    constexpr static auto parse(std::string_view value) -> Boolean;
    constexpr static auto wrap(value_type other) noexcept -> Boolean;  
    constexpr static auto logicAnd(Boolean lhs, Boolean rhs) noexcept -> Boolean;
    constexpr static auto logicOr(Boolean lhs, Boolean rhs) noexcept -> Boolean;  
    constexpr static auto logicNot(Boolean value) noexcept -> Boolean;

    private:
    value_type value;
  };

  struct Character final {
  
    using value_type     = i8;
    using reference_type = i8&;
    using pointer_type   = i8*;

    constexpr Character() noexcept = default;
    constexpr Character(Character const&) noexcept = default;
    constexpr Character(Character &&) noexcept = default;
    constexpr Character(value_type other) noexcept;

    constexpr auto operator=(Character const& other) noexcept -> Character& = default;
    constexpr auto operator=(Character&& other) noexcept -> Character& = default;
    constexpr auto operator=(value_type other) noexcept -> Character&;

    constexpr operator reference_type() noexcept;
    constexpr operator value_type() const noexcept;

    constexpr auto toString() const noexcept -> std::string;
    constexpr auto unwrap() const noexcept -> value_type;
    constexpr auto isAlpha() const noexcept -> bool;
    constexpr auto isDigit() const noexcept -> bool;
    constexpr auto isAlnum() const noexcept -> bool;
    constexpr auto isSpace() const noexcept -> bool;
    constexpr auto isBreak() const noexcept -> bool;
    
    constexpr static auto parse(std::string_view value) -> Character;
    constexpr static auto wrap(value_type other) noexcept -> Character;
  
    private:
    value_type value;
  
  };

  struct Double final {
    using value_type     = f64;
    using reference_type = f64&;
    using pointer_type   = f64*;
  
    constexpr Double() noexcept = default;
    constexpr Double(Double const&) noexcept = default;
    constexpr Double(Double &&) noexcept = default;
    constexpr Double(value_type other) noexcept;
  
    constexpr auto operator=(Double const& other) noexcept -> Double& = default;
    constexpr auto operator=(Double&& other) noexcept -> Double& = default;
    constexpr auto operator=(value_type other) noexcept -> Double&;
  
    constexpr operator reference_type() noexcept;
    constexpr operator value_type() const noexcept;

    constexpr auto unwrap() const noexcept -> value_type;
    constexpr auto toString() const noexcept -> std::string;
    constexpr auto mantissa() const noexcept -> Double;
    
    constexpr static auto parse(std::string_view value) -> Double;
    constexpr static auto wrap(value_type other) noexcept -> Double;
    constexpr static auto sum(Double lhs, Double rhs) noexcept -> Double;
    constexpr static auto difference(Double lhs, Double rhs) noexcept -> Double;
    constexpr static auto product(Double lhs, Double rhs) noexcept -> Double;
    constexpr static auto quotient(Double lhs, Double rhs) -> Double;
  
    private:
    value_type value;
  };

  struct Float final {
    using value_type     = f32;
    using reference_type = f32&;
    using pointer_type   = f32*;
  
    constexpr Float() noexcept = default;
    constexpr Float(Float const&) noexcept = default;
    constexpr Float(Float &&) noexcept = default;
    constexpr Float(value_type other) noexcept;
  
    constexpr auto operator=(Float const& other) noexcept -> Float& = default;
    constexpr auto operator=(Float&& other) noexcept -> Float& = default;
    constexpr auto operator=(value_type other) noexcept -> Float&;
    
    constexpr operator reference_type() noexcept;
    constexpr operator value_type() const noexcept;

    constexpr auto unwrap() const noexcept -> value_type;
    constexpr auto toString() const noexcept -> std::string;
    constexpr auto mantissa() const noexcept -> Float;
    
    constexpr static auto sum(Float lhs, Float rhs) noexcept -> Float;
    constexpr static auto parse(std::string_view value) -> Float;
    constexpr static auto wrap(value_type other) noexcept -> Float;
    constexpr static auto difference(Float lhs, Float rhs) noexcept -> Float;
    constexpr static auto product(Float lhs, Float rhs) noexcept -> Float;  
    constexpr static auto quotient(Float lhs, Float rhs) -> Float;
  
    private:
    value_type value;
  };

  struct Integer final {
    using value_type     = i32;
    using reference_type = i32&;
    using pointer_type   = i32*;
  
    constexpr Integer() noexcept = default;
    constexpr Integer(Integer const&) noexcept = default;
    constexpr Integer(Integer &&) noexcept = default;
    constexpr Integer(value_type other) noexcept;
  
    constexpr auto operator=(Integer const& other) noexcept -> Integer& = default;
    constexpr auto operator=(Integer&& other) noexcept -> Integer& = default;
    constexpr auto operator=(value_type other) noexcept -> Integer&;
  
    constexpr operator reference_type() noexcept;
    constexpr operator value_type() const noexcept;

    constexpr auto unwrap() const noexcept -> value_type;
    constexpr auto toString() const noexcept -> std::string;
    constexpr auto isEven() const noexcept -> bool;
    constexpr auto isOdd() const noexcept -> bool;
    
    constexpr static auto parse(std::string_view value) -> Integer;
    constexpr static auto wrap(value_type other) noexcept -> Integer;
    constexpr static auto sum(Integer lhs, Integer rhs) noexcept -> Integer;
    constexpr static auto difference(Integer lhs, Integer rhs) noexcept -> Integer;
    constexpr static auto product(Integer lhs, Integer rhs) noexcept -> Integer;
    constexpr static auto quotient(Integer lhs, Integer rhs) -> Integer;
    constexpr static auto remainder(Integer lhs, Integer rhs) -> Integer;

    private:
    value_type value;
  };

  struct Long final {
    using value_type     = i64;
    using reference_type = i64&;
    using pointer_type   = i64*;
    
    constexpr Long() noexcept = default;
    constexpr Long(Long const&) noexcept = default;
    constexpr Long(Long &&) noexcept = default;
    constexpr Long(value_type other) noexcept;
  
    constexpr auto operator=(Long const& other) noexcept -> Long& = default;
    constexpr auto operator=(Long&& other) noexcept -> Long& = default;
    constexpr auto operator=(value_type other) noexcept -> Long&;

    constexpr operator reference_type() noexcept;
    constexpr operator value_type() const noexcept;

    constexpr auto unwrap() const noexcept -> value_type;
    constexpr auto toString() const noexcept -> std::string;
    constexpr auto isEven() const noexcept -> bool;
    constexpr auto isOdd() const noexcept -> bool;
    
    constexpr static auto parse(std::string_view str) -> Long;
    constexpr static auto wrap(value_type other) noexcept -> Long;
    constexpr static auto sum(Long lhs, Long rhs) noexcept -> Long;
    constexpr static auto difference(Long lhs, Long rhs) noexcept -> Long;
    constexpr static auto product(Long lhs, Long rhs) noexcept -> Long;
    constexpr static auto quotient(Long lhs, Long rhs) -> Long;  
    constexpr static auto remainder(Long lhs, Long rhs) -> Long;
  
    private:
    value_type value;
  };

}

constexpr auto operator""_I(u64 value) noexcept -> fridayc::Integer;
constexpr auto operator""_L(u64 value) noexcept -> fridayc::Long;
constexpr auto operator""_B(u64 value) noexcept -> fridayc::Boolean;
constexpr auto operator""_F(long double value) noexcept -> fridayc::Float;
constexpr auto operator""_D(long double value) noexcept -> fridayc::Double;
constexpr auto operator""_C(i8 value) noexcept -> fridayc::Character;

#include "Wrappers.inl"



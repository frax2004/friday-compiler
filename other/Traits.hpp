#pragma once

namespace fridayc {
  template<class T>
  concept Stringable = requires (T object) {
    { object.toString() } -> std::convertible_to<std::string>;
  };

  template<class... Overloads>
  constexpr auto overload(Overloads&& ...overloads) {
    struct overload_result_t : public Overloads... {
      using Overloads::operator()...;
    };
    return overload_result_t{};
  }

  template<class T>
  struct Container {

    using value_type = T;
    using iterator = typename std::vector<value_type>::iterator;
    using const_iterator = typename std::vector<value_type>::const_iterator;
  
    constexpr auto add(T arg) noexcept -> void;
    constexpr auto begin() noexcept -> iterator;
    constexpr auto begin() const noexcept -> const_iterator;
    constexpr auto end() noexcept -> iterator;
    constexpr auto end() const noexcept -> const_iterator;
    constexpr auto size() const noexcept -> u64;
    constexpr auto empty() const noexcept -> bool;
    constexpr auto at(u64 index) -> value_type&;
    constexpr auto at(u64 index) const -> value_type const&;
    constexpr auto operator[](u64 index) noexcept -> value_type&;
    constexpr auto operator[](u64 index) const noexcept -> value_type const&;
  
    private:
    std::vector<T> values;
  };

}

#include "Traits.inl"
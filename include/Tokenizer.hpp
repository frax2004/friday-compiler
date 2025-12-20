#ifndef FRIDAYC_TOKENIZER_HPP
#define FRIDAYC_TOKENIZER_HPP

#include "Token.hpp"

namespace fridayc {

  class Tokenizer {

    public:
    struct iterator {
      std::string_view data;
      constexpr auto operator==(iterator const& rhs) const noexcept -> bool = default;
      constexpr auto operator!=(iterator const& rhs) const noexcept -> bool = default;

      using value_type = Token;
      using difference_type = std::ptrdiff_t;
    };

    private:
    std::string_view input;

    public:
    constexpr Tokenizer(std::string_view input) noexcept;
    constexpr Tokenizer(Tokenizer const&) noexcept = default;
    constexpr Tokenizer(Tokenizer &&) noexcept = default;
    constexpr auto operator==(Tokenizer const&) const noexcept -> bool = default;

    constexpr auto begin() const noexcept -> iterator;
    constexpr auto end() const noexcept -> iterator;

    template<template<class T> class Container>
    requires std::same_as<Token, typename Container<Token>::value_type>
    constexpr auto collect() const noexcept -> Container<Token>;
  };

  constexpr auto operator*(Tokenizer::iterator const& lhs) noexcept -> Token;
  constexpr auto operator++(Tokenizer::iterator& lhs) noexcept -> Tokenizer::iterator&;
  constexpr auto operator++(Tokenizer::iterator& lhs, int) noexcept -> Tokenizer::iterator;
}

#include "Tokenizer.inl"

#endif
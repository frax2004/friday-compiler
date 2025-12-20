#ifdef __INTELLISENSE__
#include "Tokenizer.hpp"
#endif

namespace fridayc {
  constexpr Tokenizer::Tokenizer(std::string_view input) noexcept
    : input { std::move(input) }
  {}

  constexpr auto Tokenizer::begin() const noexcept -> iterator {
    return {};
  }

  constexpr auto Tokenizer::end() const noexcept -> iterator {
    return {};
  }

  template<template<class T> class Container>
  requires std::same_as<Token, typename Container<Token>::value_type>
  constexpr auto Tokenizer::collect() const noexcept -> Container<Token> {
    return Container(std::begin(*this), std::end(*this));
  }

  constexpr auto operator*(Tokenizer::iterator const& lhs) noexcept -> Token {
    return {};
  }

  constexpr auto operator++(Tokenizer::iterator& lhs) noexcept -> Tokenizer::iterator& {
    return lhs;
  }

  constexpr auto operator++(Tokenizer::iterator& lhs, int) noexcept -> Tokenizer::iterator {
    return {};
  }


}

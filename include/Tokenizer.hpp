#ifndef FRIDAYC_TOKENIZER_HPP
#define FRIDAYC_TOKENIZER_HPP

#include "Token.hpp"

namespace fridayc {

  class Tokenizer {

    public:
    struct iterator {

      public:
      std::string_view data;
      
      private:
      u64 row = 0;
      u64 col = 0;
      u64 stride = 0;
      Token::Type type = Token::Type::END;

      public:
      using iterator_category = std::forward_iterator_tag;
      using iterator_concept = std::forward_iterator_tag;
      using value_type = Token;
      using difference_type = std::ptrdiff_t;

      constexpr iterator() noexcept = default;
      constexpr iterator(std::string_view raw, u64 row, u64 col) noexcept;
      constexpr auto operator==(iterator const& rhs) const noexcept -> bool = default;
      constexpr auto operator*() const noexcept -> Token;
      constexpr auto operator++() noexcept -> Tokenizer::iterator&;
      constexpr auto operator++(int) noexcept -> Tokenizer::iterator;

      private:
      constexpr auto advance() noexcept -> void;
      constexpr auto peek(u64 ahead = 0) const noexcept -> Character;
      constexpr auto consume() noexcept -> void;
      constexpr auto consumeIdentifier() noexcept -> void;
      constexpr auto consumeNumber() noexcept -> void;
      constexpr auto consumeSymbol() noexcept -> void;
      constexpr auto consumeStringLiteral() noexcept -> void;
      constexpr auto consumeCharacterLiteral() noexcept -> void;
      constexpr auto consumeIllegal() noexcept -> void;
      constexpr auto applyStride() noexcept -> void;
      constexpr auto bimatch(char expected1, char expected2, Token::Type success1, Token::Type success2, Token::Type fallback) -> void;
      constexpr auto match(char expected, Token::Type success, Token::Type fallback) -> void;

    };

    private:
    std::string_view input;

    public:
    constexpr Tokenizer(std::string_view input) noexcept;
    constexpr Tokenizer(Tokenizer const&) noexcept = default;
    constexpr Tokenizer(Tokenizer &&) noexcept = default;
    constexpr auto operator==(Tokenizer const&) const noexcept -> bool = default;

    constexpr auto size() const noexcept -> u64;
    constexpr auto begin() const noexcept -> iterator;
    constexpr auto end() const noexcept -> iterator;

    template<template<class T> class Container>
    requires std::same_as<Token, typename Container<Token>::value_type>
    constexpr auto collect() const noexcept -> Container<Token>;
  };

  static_assert(std::ranges::range<Tokenizer>);
  static_assert(std::ranges::sized_range<Tokenizer>);
  static_assert(std::ranges::forward_range<Tokenizer>);
  static_assert(std::ranges::input_range<Tokenizer>);

}

#include "Tokenizer.inl"

#endif
#include "Math.hpp"
#include "Tokenizer.hpp"

using namespace fridayc;

template<size_t N>
struct FixedString {
  char data[N];
  constexpr FixedString(const char (&str)[N]) {
    std::copy_n(str, N, data);
  }
  constexpr std::string_view view() const { return {data, N - 1}; }
};

template<FixedString input>
constexpr auto tokenize() {
  constexpr auto tokenizer = Tokenizer(input.view());
  constexpr auto N = tokenizer.size();
  std::array<Token, N> tokens;
  std::ranges::copy(tokenizer, tokens.begin());
  return std::move(tokens);
};



auto main(i32 argc, const i8* argv[]) -> i32 {
  
  constexpr auto input = R"(
  
  fn sum(x: int, y: int) -> int => x + y;
  let x = 10;
  let y = 20;
  print x + y;
  
  )"sv;
  const auto tokenizer = Tokenizer(input);
  
  for(const auto& token : tokenizer) {
    std::println("Token: {} [{}] ({}:{})", token.toString(), token.getLiteral(), token.getRow(), token.getColumn());
  }


  return 0;
}

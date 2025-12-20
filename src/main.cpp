#include "Math.hpp"
#include "Tokenizer.hpp"




auto main(i32 argc, const i8* argv[]) -> i32 {
  
  using fridayc::Tokenizer;
  using fridayc::Token;
  
  constexpr auto input = "let x = {} + {} + {};"sv;
  constexpr auto tokenizer = Tokenizer(input);
  
  constexpr auto tokens = tokenizer.collect<std::vector>();

  static_assert(tokens.size() == 0);

  return 0;
}
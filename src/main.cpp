#include "Math.hpp"
#include "Tokenizer.hpp"

using namespace fridayc;



auto main(i32 argc, const i8* argv[]) -> i32 {
  
  
  constexpr auto input = "\"ciao\""sv;
  constexpr auto tokenizer = Tokenizer(input);

  constexpr auto tokens = tokenizer.collect<std::vector>();

  return 0;
}

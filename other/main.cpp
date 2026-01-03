#include "Math.hpp"
#include "Tokenizer.hpp"
#include "Parser.hpp"

using namespace fridayc;

struct ConsoleColor {
  static constexpr const auto BLACK = "\u001B[30m"sv;
  static constexpr const auto RED = "\u001B[31m"sv;
  static constexpr const auto GREEN = "\u001B[32m"sv;
  static constexpr const auto YELLOW = "\u001B[33m"sv;
  static constexpr const auto BLUE = "\u001B[34m"sv;
  static constexpr const auto PURPLE = "\u001B[35m"sv;
  static constexpr const auto CYAN = "\u001B[36m"sv;
  static constexpr const auto WHITE = "\u001B[37m"sv;  
};

auto read(std::string path) noexcept -> std::string {
  const auto file = std::ifstream{ path };
  auto stream = std::ostringstream{};
  stream << file.rdbuf();
  return stream.str();
}

auto main(i32 argc, const i8* argv[]) -> i32 {

  std::string path = argv[1];
  std::string input = read(path);

  const auto tokens = Tokenizer(input).collect<std::vector>();

  const auto [program, errors] = Parser(std::move(tokens)).parse();

  const auto lines = input
  | std::views::split('\n')
  | std::views::transform([](auto view) { return std::string_view{view}; })
  | std::ranges::to<std::vector>();

  const auto max_digits = (u32)std::ceil(std::log10(lines.size())); 

  const auto raise_error = [&path, &lines, max_digits](Error const& error) {
    std::string_view line = lines[error.row-1];
    u64 col = std::min(line.length(), (u64)error.col-1);
    u64 col2 = std::min(line.length(), col + error.length);

    std::cout 
    << ConsoleColor::RED << "[ERROR] " << ConsoleColor::WHITE 
    << "In file " << path << ':' << error.row << ':' << error.col << ": " 
    << ConsoleColor::RED << error.message << ConsoleColor::WHITE << '\n'
    << "  " << std::setw(max_digits) << std::right << error.row << "  |  "
    << line.substr(0, col) << ConsoleColor::RED 
    << line.substr(col, error.length) << ConsoleColor::WHITE 
    << line.substr(col2) << '\n'
    << std::setfill(' ') << std::setw(max_digits + 4) << "" << "|  "
    << std::setfill(' ') << std::setw(col) << "" << ConsoleColor::RED << '^'
    << std::setfill('~') << std::setw(error.length-1) << "" << ConsoleColor::WHITE << std::endl;
  };

  if(errors.empty()) {
    std::println("{}", program.toString());
  } else std::ranges::for_each(errors, raise_error);

  return 0;
}

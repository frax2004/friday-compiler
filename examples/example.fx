

enum Token {
  PLUS,
  MINUS,
  STAR,
  SLASH,
  LET,
  IDENTIFIER,
  INT_LITERAL,
  SEMICOL
}

fn main() -> int {
  // input
  const input: String = "let x = 10;";

  // tokenizer
  const tokenizer: Tokenizer = Tokenizer.new(input);
}



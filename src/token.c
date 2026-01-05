#include "fridayc.h"

const char* TokenTypeToString(TokenType type) {
  switch(type) {
    case TOKEN_END: return "TOKEN_END";
    case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
    case TOKEN_INT_LIT: return "TOKEN_INT_LIT";
    case TOKEN_FLOAT_LIT: return "TOKEN_FLOAT_LIT";
    case TOKEN_STR_LIT: return "TOKEN_STR_LIT";
    case TOKEN_LET: return "TOKEN_LET";
    default: return "TOKEN_ILLEGAL";
  }
}

static HashTable KEYWORDS;

static void InitKeywords() {
  KEYWORDS = HashTableCreate();
  HashTableInsert(&KEYWORDS, "let", (void*)(u64)TOKEN_LET);
}

Token TokenFromIdentifier(const char* lexeme, u64 row, u64 col) {
  if(KEYWORDS.buckets == NULL) {
    InitKeywords();
  }

  Entry* entry = HashTableLookUp(&KEYWORDS, lexeme);
  TokenType type = entry != NULL ? (TokenType)(u64)entry->value : TOKEN_IDENTIFIER;
  return TokenCreateEx(lexeme, type, row, col);
}

Token TokenCreate(const char* lexeme, TokenType type) {
  return TokenCreateEx(lexeme, type, 0, 0);
}

Token TokenCreateEx(const char* lexeme, TokenType type, u64 row, u64 col) {
  return (Token) {
    .lexeme = lexeme,
    .row = row,
    .col = col,
    .type = type
  };
}

i32 TokenCompare(const Token lhs, const Token rhs) {
  if(lhs.type != rhs.type) return false;
  switch(lhs.type) {
    case TOKEN_IDENTIFIER:
    case TOKEN_INT_LIT:
    case TOKEN_FLOAT_LIT:
    case TOKEN_STR_LIT: return strcmp(lhs.lexeme, rhs.lexeme);
    default: return 0;
  }
}

bool TokenEquals(const Token lhs, const Token rhs) {
  return TokenCompare(lhs, rhs) == 0;
}


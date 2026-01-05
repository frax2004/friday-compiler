#include "fridayc.h"
#include "ctest.h"

void TestSuite();
void TestTokenTypeToString();
void TestTokenCreateEx();
void TestTokenCompare();
void TestTokenFromIdentifier();

i32 main() {
  TestSuite();
}


void TestSuite() {
  TestTokenTypeToString();
  TestTokenCompare();
  TestTokenCreateEx();
  TestTokenFromIdentifier();
}

void TestTokenTypeToString() {
  const char* expected = "TOKEN_LET";
  const char* actual = TokenTypeToString(TOKEN_LET);

  assertEquals(0, strcmp(expected, actual));
}

void TestTokenFromIdentifier() {
  const char* id1 = "let";
  const char* id2 = "foobar";

  Token t1 = TokenFromIdentifier(id1, 0, 0);
  Token t2 = TokenFromIdentifier(id2, 0, 0);

  assertEquals(0, TokenCompare(TOKENS[TOKEN_LET], t1));
  assertEquals(TOKEN_IDENTIFIER, t2.type);
}

void TestTokenCreateEx() {
  Token token = TokenCreateEx("let", TOKEN_LET, 0, 0);
  assertEquals(0, TokenCompare(token, TOKENS[TOKEN_LET]));
}

void TestTokenCompare() {
  const char* id1 = "foo";
  const char* id2 = "bar";

  Token t1 = TokenCreateEx(id1, TOKEN_IDENTIFIER, 0, 0);
  Token t2 = TokenCreateEx(id2, TOKEN_IDENTIFIER, 0, 0);

  i32 expected = strcmp(id1, id2);
  i32 actual = TokenCompare(t1, t2);

  assertEquals(expected, actual);
}



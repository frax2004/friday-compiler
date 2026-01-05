#ifndef FRIDAYC_H
#define FRIDAYC_H
/*
|-------------------------------------|
|                                     |
|             TYPE ALIASES            |
|                                     |
|-------------------------------------|
*/

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef unsigned char byte;


typedef enum Result Result;
typedef enum TokenType TokenType;
typedef struct Token Token;
typedef struct Entry Entry;
typedef struct HashTable HashTable;

/*
|-------------------------------------|
|                                     |
|          STRUCTS DEFINITIONS        |
|                                     |
|-------------------------------------|
*/

enum TokenType {
  TOKEN_ILLEGAL,
  TOKEN_END,
  TOKEN_IDENTIFIER,
  TOKEN_INT_LIT,
  TOKEN_FLOAT_LIT,
  TOKEN_STR_LIT,
  TOKEN_LET,
};


struct Token {
  const char* lexeme;
  u64 row;
  u64 col;
  TokenType type;  
};


#define HASH_TABLE_INITIAL_CAPACITY 4

struct Entry {
  const char* key;
  void* value;
  Entry* next;
};

struct HashTable {
  Entry** buckets;
  u64 size;
  u64 capacity;
};

/*
|-------------------------------------|
|                                     |
|              FUNCTIONS              |
|                                     |
|-------------------------------------|
*/

// Token related functions

const char* TokenTypeToString(TokenType type);
Token       TokenCreate(const char* lexeme, TokenType type);
Token       TokenCreateEx(const char* lexeme, TokenType type, u64 row, u64 col);
Token       TokenFromIdentifier(const char* lexeme, u64 row, u64 col);
i32         TokenCompare(const Token lhs, const Token rhs);
bool        TokenEquals(const Token lhs, const Token rhs);

// Compiler related functions

bool  IsAlpha(char c);
bool  IsDigit(char c);
bool  IsBreak(char c);
bool  IsSpace(char c);
bool  IsSymbol(char c);
byte* Compile(const char* code);


// Interpreter related functions

i32 Interpret(byte* bytecode);


// IO related functions

char* ReadFile(const char* path);

// Data structures related functions

u64       GetStringHashCode(const char* key);
HashTable HashTableCreate();
Entry*    HashTableLookUp(HashTable* self, const char* key);
Entry*    HashTableInsert(HashTable* self, const char* key, void* value);
bool      HashTableRemove(HashTable* self, const char* key);
bool      HashTableContains(HashTable* self, const char* key);
void      HashTableRehash(HashTable* self);
void      HashTableDestroy(HashTable* self);

/*
|-------------------------------------|
|                                     |
|             STATIC DATA             |
|                                     |
|-------------------------------------|
*/

static const Token TOKENS[] = {
  [TOKEN_LET]     = (Token) { .lexeme = "let",     .type = TOKEN_LET     },
  [TOKEN_ILLEGAL] = (Token) { .lexeme = "ILLEGAL", .type = TOKEN_ILLEGAL },
  [TOKEN_END]     = (Token) { .lexeme = "EOF",     .type = TOKEN_END     },
};



#endif
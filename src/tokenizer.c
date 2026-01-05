#include "fridayc.h"

bool IsAlpha(char c) {
  return ('a' <= c && c <= 'z') 
  || ('A' <= c && c <= 'Z') 
  || (c == '_');
}

bool IsDigit(char c) {
  return '0' <= c && c <= '9';
}

bool IsBreak(char c) {
  return (c == '\n') || (c == '\v');
}

bool IsSpace(char c) {
  return (c == ' ') || (c == '\t');
}

bool IsSymbol(char c) {
  switch(c) {
    case '.':
    case ',':
    case ';':
    case '"':
    case '\'':
    case '-':
    case '<':
    case '>':
    case '=':
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case '!':
    case '*':
    case '/':
    case '+':
    case '?':
    case '%':
    case '&':
    case ':':
    case '~': return true;
    default: return false;
  }
}


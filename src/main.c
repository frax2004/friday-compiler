#include "fridayc.h"


i32 main(i32 argc, const i8* argv[]) {

  const char* code = "(3 + 4) * 5";
  byte* bytecode = Compile(code);
  i32 result = Interpret(bytecode);

}
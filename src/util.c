#include "fridayc.h"


char* ReadFile(const char* path) {
  FILE* file = fopen(path, "r");
  if(!file) return NULL;

  fseek(file, 0, SEEK_END);
  u64 size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  char* buffer = (char*)malloc(sizeof(char) * size + 1);
  fread(buffer, sizeof(char), size, file);
  buffer[size] = 0;
  fclose(file);
  
  return buffer;
}

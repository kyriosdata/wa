#include <string.h>

void readStrFromMem(char* offset, int length);

void showString(char* str) {
  readStrFromMem(str, strlen(str));  
}

int main() { 
  return 42;
} 
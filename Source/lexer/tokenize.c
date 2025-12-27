#include "NoneScript.h"
#include "lexer.h"
#include "../errors.h"

#include <string.h>

void
tokenize(const char *buffer) {
  unsigned int columns = 0;
  unsigned int lineLength = strlen(buffer);
  if (lineLength > MAX_LINE_LENGTH) {
    panic("tokenize()", "too long line", NULL);
  }
  for (unsigned int i = 0; i < lineLength; ++i) {
    columns++;
    
  }
}

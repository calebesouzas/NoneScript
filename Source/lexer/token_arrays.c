#include "lexer.h"

#include <stdlib.h>

token_array_t initTokenArray() {
  token_array_t ta;
  
  ta.count = 0;
  ta.tokens = (token_t*)malloc(sizeof(token_t) * 32);
  if (ta.tokens == NULL) {
  }

  return ta;
}

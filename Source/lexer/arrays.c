#include "lexer.h"
#include "../errors.h"

#include <stddef.h>
#include <stdlib.h>

const unsigned int tokenAllocPerTurn = 64 * sizeof(token_t);

token_array_t
initTokenArray() {
  token_array_t ta;

  ta.count = 0;
  ta.tokens = (token_t*)malloc(sizeof(token_t) * tokenAllocPerTurn);
  if (ta.tokens == NULL) {
    panic("initTokenArray()", "MemoryAllocation", NULL);
  }
  
  return ta;
}

void
appendTokenArray(token_array_t* ta, token_t* t) {
  if (ta->count >= tokenAllocPerTurn) {
    ta->tokens = (token_t*)realloc((token_t*)ta->tokens,
                                    sizeof(token_t) * ta->count
                                    + tokenAllocPerTurn);
  }
  ta->tokens[ta->count] = *t;
  ta->count++;
}

#include "lexer.h"
#include "errors.h"

#include <stdlib.h>
#include <stdbool.h>

#include <ctype.h>

token_array_t
initTokenArray() {
  token_array_t ta;

  ta.count = 0;
  ta.tokens = (token_t*)malloc(NONE_TOKEN_ALLOCATION);
  
  if (ta.tokens == NULL) {
    panic("initTokenArray()", "failed to allocate memory for tokens");
  }

  return ta;
}

void
appendTokenArray(token_array_t *ta, token_t *t) {
  if (ta->count >= NONE_TOKEN_ALLOCATION) {
    ta->tokens = (token_t*)realloc(ta->tokens,
                                    NONE_TOKEN_ALLOCATION
                                    + sizeof(token_t)
                                    * ta->count);
    if (ta->tokens == NULL) {
      panic("appendTokenArray()", "failed to reallocate memory for tokens");
    }
  }

  ta->tokens[ta->count] = *t;
  ta->count++;
}

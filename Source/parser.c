#include <stdio.h>
#include "lexer.h"
#include "parser.h"

void parse(TokenArray* tokenArray) {
  for (int i = 0; i < tokenArray->count; i++) {
    printf("Found token: %s\n", tokenArray->tokens[i].value);
  }
}

#include <stdio.h>
#include "lexer.h"
#include "parser.h"

void parse(TokenArray* tokenArray) {
  TokenArray tokens = *tokenArray;
  for (int i = 0; i < tokens.count; i++) {
    printf("Found token: %s", tokens.tokens[i].value);
  }
}

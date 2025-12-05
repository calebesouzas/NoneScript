#include <stdio.h>
#include "lexer.h"

void
add_token(token_t token, token_t *tokenArray, unsigned int arrayLength) {
  tokenArray[arrayLength + 1] = token;
}

void
tokenize(char *sourceCode, off_t size) {
  token_t tokens[size];
  
  for (int i = 0; i < size; i++) {
    char currentChar = sourceCode[i];
    token_t tok;
    unsigned int tokenArrayLength = sizeof(tokens) / sizeof(token_t);
    switch (currentChar) {
      case '+'|'-'|'*'|'/':
        tok.type = BinaryOperator;
        tok.value = &currentChar;
        add_token(tok, tokens, tokenArrayLength);
        break;
      case '!':
        tok.type = ExclamationMark;
        tok.value = &currentChar;
        add_token(tok, tokens, tokenArrayLength);
        break;
      case '?':
        tok.type = QuestionMark;
        tok.value = &currentChar;
        add_token(tok, tokens, tokenArrayLength);
    }
  }
}

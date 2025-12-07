#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

void
check_for_reserved_keyword(token_t *token) {
  const char *identifier = token->value;
  if (!strncmp(identifier, "let", 3)) {
    token->type = Let;
  }
  else if (!strncmp(identifier, "const", 5)) {
    token->type = Const;
  }
  return;
}

void
tokenize(char *sourceCode, off_t size) {
  token_t tokens[size];
  unsigned int tokensAdded = 0;
  
  for (int i = 0; i < size; i++) {
    char currentChar = sourceCode[i];
    // First we check if the current character is any
    // whitespace, tab, newline or return character.
    // Then, we skip it
    switch (currentChar) {
      case  ' ':
      case '\n':
      case '\r':
      case '\t':
        continue;
    }
    token_t tok;
    unsigned int passSwitch = 0;
    switch (currentChar) {
      case '+':
      case '-':
      case '*':
      case '/':
        tok.type = BinaryOperator;
        strncat(tok.value, &currentChar, 1);
        tokens[tokensAdded] = tok;
        tokensAdded++;
        passSwitch = 1;
        break;
      case '!':
        tok.type = ExclamationMark;
        strncat(tok.value, &currentChar, 1);
        tokens[tokensAdded] = tok;
        tokensAdded++;
        passSwitch = 1;
        break;
      case '?':
        tok.type = QuestionMark;
        strncat(tok.value, &currentChar, 1);
        tokens[tokensAdded] = tok;
        tokensAdded++;
        passSwitch = 1;
        break;
    }
    // Somethings are better to verify with if - else statements
    // But we only do it if `currentChar` didn't match any case
    // in the previous switch - case statement
    if (!passSwitch) {
      if (isalpha(currentChar)) {
        tok.type = Identifier;
        int tempI = i;
        while (isalpha(sourceCode[tempI])) {
          strncat(tok.value, &sourceCode[tempI], 1);
          tempI++;
        }

        check_for_reserved_keyword(&tok);

        tokens[tokensAdded] = tok;
        tokensAdded++;
      }
      else if (isdigit(currentChar)) {
        tok.type = Number;
        int tempI = i;
        while (isdigit(sourceCode[tempI])) {
          strncat(tok.value, &sourceCode[tempI], 1);
          tempI++;
        }

        tokens[tokensAdded] = tok;
        tokensAdded++;
      }
      else {
        printf("Unrecognized character: %s\n", &currentChar);
        return;
      }
    }
  }
}

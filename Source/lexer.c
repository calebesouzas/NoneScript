#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

void tokenize(TokenArray* tokenArray, const char *sourceCode) {
  for (int i = 0; i < sizeof(sourceCode); i++) {
    char currentChar = sourceCode[i];
    Token token = {.longValue = NULL};
    switch (currentChar) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        continue;
      case '+':
      case '-':
      case '*':
      case '/':
        token.type = BinaryOperator; break;
      case '(':
      case '[':
      case '{':
        token.type = OpenGroup; break;
      case ')':
      case ']':
      case '}':
        token.type = CloseGroup; break;
      default:
        if (isdigit(currentChar)) {
          token.type = Number;
          int startIndex  = i;
          int endIndex    = i;
          while (isdigit(sourceCode[endIndex])) { endIndex++; }
          int numberCount = endIndex - startIndex;
          if (numberCount < sizeof(token.value)) {
            strncpy(token.value, sourceCode + startIndex, numberCount);
          } 
          else {
            strncpy(token.longValue, sourceCode + startIndex, numberCount);
          }
          i = endIndex;
          continue;
        } 
        else if (isalpha(currentChar)) {
          token.type = Identifier;
          int startIndex  = i;
          int endIndex    = i;
          while (isalpha(sourceCode[endIndex])) { endIndex++; }
          int charCount = endIndex - startIndex;
          if (charCount < sizeof(token.value)) {
            strncpy(token.value, sourceCode + startIndex, charCount);
            token.value[charCount] = '\0';
          }
          else {
            strncpy(token.longValue, sourceCode + startIndex, charCount);
            token.longValue[charCount] = '\0';
          }
          i = endIndex;
          continue;
        }
        else {
          printf("Invalid character: %c", currentChar);
          exit(1);
        }
        break;
      strncat(token.value, &currentChar, 1);
    }
    tokenArray->tokens[tokenArray->count] = token;
    tokenArray->count++;
  }
}

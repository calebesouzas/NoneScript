#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "errors.h"

int getSimpleTokenType(Token* token, char character) {
  switch (character) {
    case '\\':
      token->type = EscapeSequence;
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      token->type = BinaryOperator;
      break;
    case '(':
    case '[':
    case '{':
      token->type = OpenGroup;
      break;
    case ')':
    case ']':
    case '}':
      token->type = CloseGroup;
      break;
    default:
      return 0;
  }
  token->value[0] = character;
  return 1;
}

int keywordToken(Token* token, const char *identifier) {
  if (!strncmp(identifier, "let", 3)) {
    token->type = LetKeyword;
    return 1;
  }
  else if (!strncmp(identifier, "range", 5)) {
    token->type = RangeKeyword;
    return 1;
  }
  else if (!strncmp(identifier, "const", 5)) {
    token->type = ConstKeyword;
    return 1;
  }
  return 0;
}

unsigned int getTokenType(Token* token, const char *string, Result* result) {
  unsigned int count = 0;
  if (isdigit(string[count]) || (string[count] == '.' && count > 0)) {
    token->type = Number;
    while (isdigit(string[count])) { count++; }
    if (count > sizeof(token->value)) {
      token->longValue = (char*)malloc(count);
      if (token->longValue == NULL) {
        puts("Failed to allocate memory for long token\n");
        exit(1);
      }
      strncpy(token->longValue, string, count);
    }
    else {
      strncpy(token->value, string, count);
    }
  }
  else if (isalpha(string[count]) || (string[count] == '.' && count > 0)) {
    token->type = Identifier;

    if (keywordToken(token, string)) {return count;}

    while (isalpha(string[count])) { count++; }
    if (count > sizeof(token->value)) {
      token->longValue = (char*)malloc(count);
      if (token->longValue == NULL) {
        puts("Failed to allocate memory for long token\n");
        exit(1);
      }
      strncpy(token->longValue, string, count);
    }
    else {
      strncpy(token->value, string, count);
    }
  }
  else {
    result->status = Error;
    strncpy(result->error, "Invalid Token: ", sizeof(result->error));
    strncat(result->error, string, strlen(string));
  }
  return count;
}

Result genTokenArray(TokenArray* tokenArray,
                     const char *sourceCode,
                     unsigned int fileSize) {
  Result result = {.status = Ok};
  memset(result.error, 0, sizeof(result.error));
  for (int i = 0; i < fileSize; i++) {
    char currentChar = sourceCode[i];
    Token token = {.longValue = NULL};
    memset(token.value, 0, sizeof(token.value));
    switch (currentChar) {
      case  ' ':
      case '\t':
      case '\r':
      case '\n':
        continue;
    }
    if (!getSimpleTokenType(&token, currentChar)) {
      Result tokenTypeResult = {.status = Ok};
      memset(tokenTypeResult.error, 0, sizeof(tokenTypeResult.error));
      i += getTokenType(&token, sourceCode + i, &result);
      if (tokenTypeResult.status == Error) {
        return tokenTypeResult;
      }
    }
    tokenArray->tokens[tokenArray->count] = token;
    tokenArray->count++;
  }
  return result;
}

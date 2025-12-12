#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "errors.h"

int getSimpleTokenType(Token* token, char character) {
  switch (character) {
    case '\\':  token->type = EscapeSequence;   break;

    case '+':
    case '-':
    case '*':
    case '/':   token->type = BinaryOperator;   break;

    case '&':   token->type = BitwiseAnd;       break;
    case '|':   token->type = BitwiseOr;        break;
    case '^':   token->type = BitwiseXOr;       break;

    case '.':   token->type = DotOperator;      break;
    case ':':   token->type = CollonOperator;   break;

    case '(':   token->type = OpenParen;        break;
    case '[':   token->type = OpenBrackets;     break;
    case '{':   token->type = OpenBraces;       break;

    case ')':   token->type = CloseParen;       break;
    case ']':   token->type = CloseBrackets;    break;
    case '}':   token->type = CloseBraces;      break;

    case '!':   token->type = NotOperator;      break;
    case '=':   token->type = Equals;           break;
    case '<':   token->type = LessThan;         break;
    case '>':   token->type = GreaterThan;      break;
    default:
      return 0;
  }
  token->value[0] = character;
  return 1;
}

int keywordToken(Token* token, const char *identifier) {
  if (!strncmp(identifier, "if", 2)) {
    token->type = KeywordIf;
    return 1;
  }
  else if (!strncmp(identifier, "let", 3)) {
    token->type = KeywordLet;
    return 1;
  }
  else if (!strncmp(identifier, "set", 3)) {
    token->type = KeywordSet;
    return 1;
  }
  else if (!strncmp(identifier, "end", 3)) {
    token->type = KeywordEnd;
    return 1;
  }
  else if (!strncmp(identifier, "else", 4)) {
    token->type = KeywordElse;
    return 1;
  }
  else if (!strncmp(identifier, "enum", 4)) {
    token->type = KeywordEnum;
    return 1;
  }
  else if (!strncmp(identifier, "const", 5)) {
    token->type = KeywordConst;
    return 1;
  }
  else if (!strncmp(identifier, "range", 5)) {
    token->type = KeywordRange;
    return 1;
  }
  else if (!strncmp(identifier, "class", 5)) {
    token->type = KeywordClass;
    return 1;
  }
  else if (!strncmp(identifier, "struct", 6)) {
    token->type = KeywordStruct;
    return 1;
  }
  return 0;
}

unsigned int getTokenType(Token* token, const char *string, Result* result) {
  unsigned int count = 0;
  if (isdigit(string[count])) {
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
  tokenArray->tokens[tokenArray->count] = (Token) {.type = EndOfFile};
  return result;
}

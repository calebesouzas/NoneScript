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

int keywordToken(Token* token, const char *identifier, unsigned int *count) {
  if (!strncmp(identifier, "if", 2)) {
    token->type = KeywordIf;
    *count += 2;
    return 1;
  }
  else if (!strncmp(identifier, "let", 3)) {
    token->type = KeywordLet;
    *count += 3;
    return 1;
  }
  else if (!strncmp(identifier, "set", 3)) {
    token->type = KeywordSet;
    *count += 3;
    return 1;
  }
  else if (!strncmp(identifier, "end", 3)) {
    token->type = KeywordEnd;
    *count += 3;
    return 1;
  }
  else if (!strncmp(identifier, "use", 3)) {
    token->type = KeywordUse;
    *count += 3;
    return 1;
  }
  else if (!strncmp(identifier, "else", 4)) {
    token->type = KeywordElse;
    *count += 4;
    return 1;
  }
  else if (!strncmp(identifier, "enum", 4)) {
    token->type = KeywordEnum;
    *count += 4;
    return 1;
  }
  else if (!strncmp(identifier, "const", 5)) {
    token->type = KeywordConst;
    *count += 5;
    return 1;
  }
  else if (!strncmp(identifier, "range", 5)) {
    token->type = KeywordRange;
    *count += 5;
    return 1;
  }
  else if (!strncmp(identifier, "class", 5)) {
    token->type = KeywordClass;
    *count += 5;
    return 1;
  }
  else if (!strncmp(identifier, "struct", 6)) {
    token->type = KeywordStruct;
    *count += 6;
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
  else if (isalpha(string[count])) {
    token->type = Identifier;

    if (keywordToken(token, string, &count)) {return count;}

    while (isalpha(string[count]) || (isdigit(string[count]) && count > 1)) { count++; }
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
  return count > 1 ? count : 0;
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

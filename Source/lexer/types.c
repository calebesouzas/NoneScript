#include "lexer.h"
#include "keywords.h"

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

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
  else if (isalpha(string[count]) || string[count] == '_') {
    token->type = Identifier;

    if (isKeywordToken(token, string, &count)) {return count;}

    while (isalpha(string[count]) || (isdigit(string[count]) && count > 1)
          || string[count] == '_') { count++; }
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
    strncat(result->error, &string[0], 1);
  }
  return count > 1 ? count - 1 : 0;
}

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
    case '@':   token->type = AtOperator;       break;
    case '$':   token->type = DollarOperator;   break;
    case '?':   token->type = NoneOperator;     break;

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

    case '"':   token->type = String;           break;
    default:
      return 0;
  }
  token->value[0] = character;
  return 1;
}

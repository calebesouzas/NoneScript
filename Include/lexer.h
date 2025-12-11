#ifndef NONE_LEXER_H
#define NONE_LEXER_H
#include "errors.h"

typedef enum {
  BinaryOperator,

  OpenGroup,
  CloseGroup,

  LetKeyword,
  RangeKeyword,
  ConstKeyword,

  Identifier,

  Dot,
  Collon,

  Question,
  Exclamation,

  Equals,
  LessThan,
  GreaterThan,

  Number,

  StringLiteral,
  RegexString,

  EscapeSequence,

  EndOfFile
} TokenType;

typedef struct {
  TokenType     type;
  char          value[32];
  char*         longValue;
} Token;

typedef struct {
  Token*        tokens;
  unsigned int  count;
} TokenArray;

Result genTokenArray(TokenArray* tokenArray,
                     const char *sourceCode,
                     unsigned int fileSize);

#endif /* ifndef NONE_LEXER_H */

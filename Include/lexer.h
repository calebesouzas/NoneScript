#ifndef NONE_LEXER_H
#define NONE_LEXER_H

typedef enum {
  BinaryOperator,

  OpenGroup,
  CloseGroup,

  LetKeyword,
  RangeKeyword,

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

void tokenize(TokenArray* tokenArray, const char *sourceCode);

#endif /* ifndef NONE_LEXER_H */

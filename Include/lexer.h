#ifndef NONE_LEXER_H
#define NONE_LEXER_H
#include "errors.h"

typedef enum {
  BinaryOperator,   // check
  
  BitwiseAnd,       // check
  BitwiseOr,        // check
  BitwiseXOr,       // check

  DotOperator,      // check
  CollonOperator,   // check

  OpenParen,        // check
  OpenBraces,       // check
  OpenBrackets,     // check

  CloseParen,       // check
  CloseBraces,      // check
  CloseBrackets,    // check

  KeywordLet,       // check
  KeywordSet,       // check
  KeywordConst,     // check

  KeywordUse,       // check

  KeywordEnd,       // check

  KeywordRange,     // check

  KeywordIf,        // check
  KeywordElse,      // check

  KeywordEnum,      // check
  KeywordStruct,    // check
  KeywordClass,     // check

  Identifier,       // check

  Equals,           // check
  NotOperator,      // check
  LessThan,         // check
  GreaterThan,      // check

  Number,           // check
  DecimalNumber,    // not check

  StringLiteral,    // not check
  RegexString,      // not check

  EscapeSequence,   // check

  EndOfFile         // check
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

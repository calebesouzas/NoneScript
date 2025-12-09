#ifndef NONE_LEXER_H
#define NONE_LEXER_H
#include <stddef.h>
#include <stdio.h>

typedef enum {
  // Start KEYWORDS
  LetKeyword,
  ConstKeyword,
  // End KEYWORDS

  Identifier,
  EqualsSymbol,
  QuestionMark,
  ExclamationMark,
  Number,
  StringLiteral,
  RegexString,

  // Start OPERATORS
  BinaryOperator,
  DotOperator,
  CollonOperator,
  // End OPERATORS
  
  // Start PAIRED_SYMBOLS
  OpenParen,
  CloseParen,
  OpenSquareBracket,
  CloseSquareBracket,
  OpenCurlyBrace,
  CloseCurlyBrace,
  // End PAIRED_SYMBOLS

  EndOfFile
} token_type_t;

typedef struct {
  token_type_t type;
  char value[32];
} token_t;

typedef struct {
  token_t *tokens;
  size_t count;
  enum {
    Ok,
    Error
  } status;
  char errorMsg[32];
} LexerResult;

LexerResult tokenize(const char *sourceCode);

#endif /* ifndef NONE_LEXER_H */

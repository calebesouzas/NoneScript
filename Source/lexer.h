#ifndef NONE_LEXER_H
#define NONE_LEXER_H
#include <stddef.h>
#include <stdio.h>

typedef enum {
  Let,                // Let keyword
  Const,              // Const keyword
  Identifier,         // Identifier
  EqualsSymbol,       // '='
  QuestionMark,       // '?'
  ExclamationMark,    // '!'
  DotOperator,        // '.'
  Number,             // 0 - 9
  StringLiteral,      // "any thing inside double quotes"
  RegexString,        // re"any thing inside double quotes after 're'"
  BinaryOperator,     // '+', '-', '*', '/' will be supported by now
  OpenParen,          // '('
  CloseParen,         // ')'
  OpenSquareBracket,  // '['
  CloseSquareBracket, // ']'
  OpenCurlyBrace,     // '{'
  CloseCurlyBrace,    // '}'
  EndOfFile           // Yep, it marks the last token in the array
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
  enum {
    MemoryAllocationFailed,
    UnrecognizedToken
  } error;
} LexerResult;

LexerResult tokenize(const char *sourceCode);

#endif /* ifndef NONE_LEXER_H */

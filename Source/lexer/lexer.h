#ifndef NONE_LEXER_H
#define NONE_LEXER_H

#define NONE_TOKEN_ALLOCATION 64

typedef enum {
  EndOfFile,

  BinaryOperator,

  AsignmentOperator,

  OpenGroup,
  CloseGroup,

  Identifier,
  Keyword,

  Number,
  FloatingNumber
} token_type_t;

typedef struct {
  char*         value;
  unsigned int  length;
  token_type_t  type;
} token_t;

typedef struct {
  token_t*      tokens;
  unsigned int  count;
} token_array_t;


token_array_t initTokenArray();

void appendTokenArray(token_array_t* ta, token_t* t);

void tokenize(const char *buffer);

#endif /* NONE_LEXER_H */

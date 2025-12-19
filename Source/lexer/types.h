#ifndef NONE_LEXER_TYPES_H
#define NONE_LEXER_TYPES_H

#include "lexer.h"

unsigned int getTokenType(Token* token, const char *string, Result* result);

int getSimpleTokenType(Token* token, char character);

#endif /* NONE_LEXER_TYPES_H */

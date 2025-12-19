#include "lexer.h"
#include "errors.h"

#include "types.h"

#include <string.h>

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
      i += getTokenType(&token, sourceCode + i, &result);
      if (result.status == Error) {
        return result;
      }
    }
    tokenArray->tokens[tokenArray->count] = token;
    tokenArray->count++;
  }
  tokenArray->tokens[tokenArray->count] = (Token) {.type = EndOfFile};
  return result;
}

#include "lexer.h"
#include <string.h>

int isKeywordToken(Token* token, const char *identifier, unsigned int *count) {
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

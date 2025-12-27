#include "NoneScript.h"
#include "lexer/lexer.h"

#include <stdio.h>

#include <string.h>

None_Result
None_RunFile(const char *fileName) {
  FILE * noneFile = fopen(fileName, "r");
  if (noneFile == NULL) {
    return (None_Result)
    {
      .status = Error,
      .error.location = "FileOpening",
      .error.message = "Failed to open file",
    };
  }

  char buffer[MAX_LINE_LENGTH] = {0};

  token_array_t ta = initTokenArray();
  unsigned int lines = 0;
  while (fgets(buffer, MAX_LINE_LENGTH, noneFile) != NULL) {
    ++lines;
  }

  return (None_Result) {.status = Ok};
}


void
None_RunInteractive() {
  char buffer[MAX_LINE_LENGTH] = {0};

  while (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
    if (strncmp(buffer, "quit()", 6) != 0) {
      break;
    }
  }
}

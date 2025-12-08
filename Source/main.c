#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

enum Error {
  FileOperationFailed,
  MemoryAllocationError,
  ScriptRunningFailure
};

int run(const char *sourceCode);

/* Function `main`. The entry point of the program.
 * It takes two arguments (which are given by the Shell).
 * Param `argc` is the argument count (incliding program name).
 * Param `argv` is an array of strings. It contains every argument given
 * to our program, including it's name (in `argv[0]`). */

int // Returns 0 for EXIT_SUCCESS or any other number for EXIT_FAILURE
main(int argc, char *argv[]) {
  FILE *pNSFile = NULL; // iT's a good practice to default pointers
                        // to NULL if there is any chance of failure
  if (argc == 1) {
    printf("NoneScript - Creative Commons 0 - version 0.1.0-dev\n");
  }

  else {
    // If the user gave an argument to the program and that argument 
    // is not an option, we'll treat it as a file, 
    // then we'll get the file size,
    // allocate memory for it's content
    // and run the script (always validating before, of course).
    pNSFile = fopen(argv[1], "r");
    if (pNSFile == NULL) {
      perror("Failed to open file");
      return FileOperationFailed;
    }
    int fileSize = 0;
    // Get the position of the EOF (End Of File) constant
    fseek(pNSFile, 0, SEEK_END);
    fileSize = ftell(pNSFile); // and asign it to `fileSize`

    // Handle possible errors when trying to get file size
    if (fileSize == -1) {
      perror("Failed to get file size");
      fclose(pNSFile);
      return FileOperationFailed;
    }

    fseek(pNSFile, 0, SEEK_SET); // Go back to the begining

    // Allocate memory enought to store the source code.
    // Then we can close the file early
    // +1 for the '\0' (Null terminator).
    char *pNoneScript = (char *)malloc(fileSize + 1);
    if (pNoneScript == NULL) {
      perror("Failed to allocate memory for the script");
      fclose(pNSFile);
      return MemoryAllocationError;
    }

    // Getting index of last character (size of NoneScript buffer + 1)
    // and also storing the NS file's content into `pNoneScript`
    
    size_t lastChar = fread(pNoneScript, sizeof(char), fileSize, pNSFile);

    if (ferror(pNSFile) != 0) {
      fputs("Failed to read file", stderr);
      free(pNoneScript);
      fclose(pNSFile);
      return FileOperationFailed;
    }
    else {
      pNoneScript[lastChar] = '\0'; // Null terminate the buffer
      fclose(pNSFile);
      pNSFile = NULL;
    }

    int ranSuccessfully = run(pNoneScript);
    if (!ranSuccessfully) {
      printf("Failed to run script");
      return ScriptRunningFailure;
    }

    free(pNoneScript);
    pNoneScript = NULL;
  }
    return 0;
}

int
run(const char *sourceCode) {
  LexerResult lexerResult = tokenize(sourceCode);
  if (lexerResult.status == Error) {
    switch (lexerResult.error) {
      case MemoryAllocationFailed:
        perror("Failed to allocate memory for the tokens");
        return 0;
      
      case UnrecognizedToken:
        printf("Unrecognized token: ");
        char *unrecognizedToken = lexerResult.tokens[lexerResult.count].value;
        printf("%s\n", unrecognizedToken);
        free(lexerResult.tokens);
        return 0;
    }
  }
  else {
    for (size_t i = 0; i < lexerResult.count; i++) {
      printf("Found token: { value: %s },\n",
              lexerResult.tokens[i].value);
    }
  }

  return 1;
}

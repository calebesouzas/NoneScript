#include <stdio.h>
#include <stdlib.h>

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
      printf("Failed to open file %s\n", argv[1]);
      return -1;
    }
    int fileSize = 0;
    // Get the position of the EOF (End Of File) constant
    fseek(pNSFile, 0, SEEK_END);
    fileSize = ftell(pNSFile); // and asign it to `fileSize`

    char *pNoneScript = (char *)malloc(fileSize);
    if (pNoneScript == NULL) {
      printf("Failed to allocate memory for the script\n");
      return -2;
    }

    free(pNoneScript);
    pNoneScript = NULL;
    fclose(pNSFile);
  }
  return 0;
}

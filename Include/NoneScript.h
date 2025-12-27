#ifndef NONESCRIPT_H
#define NONESCRIPT_H

#define MAX_LINE_LENGTH 1024

struct None_Error {
  char message[32];
  char location[16];
};

typedef struct {
  enum {
    Ok,
    Error
  } status;
  struct None_Error error;
} None_Result;

/* @function 'None_RunFile' {
 * runs the NoneScript code inside a file
 * }
 * @param 'fileName' {
 * file name (or path) containing the source code
 * }
 * @return {
 * returns a 'None_Result' structure that contains:
 * - an 'status' field,
 * - an 'error' structure field, inside it we have:
 *   - a 'message' field containing a string,
 *   - a 'location' field containing a string telling where the error ocurred
 *   - a 'type' enum field giving an overview of what happened
 * } */
None_Result
None_RunFile(const char* fileName);

/* @function 'None_RunInteractive' {
 * to run simple scripts withing the terminal.
 * It has some limitations, like no access for '@file' special variable.
 * Breaks the loop when the user uses any of these functions:
 * 'quit()' or 'exit(int code ?? 0)'
 * } */
void
None_RunInteractive();

#endif /* NONESCRIPT_H */

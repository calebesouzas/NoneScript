#ifndef ERRORS_H
#define ERRORS_H


typedef struct {
  enum {
    Ok,
    Error
  } status;
  char error[32];
} Result;

void panic(const char *local, const char *reason, const char **details);

#endif /* ERRORS_H */

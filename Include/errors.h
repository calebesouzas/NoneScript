#ifndef ERRORS_H
#define ERRORS_H


typedef struct {
  enum {
    Ok,
    Error
  } status;
  char error[32];
} Result;

#endif /* ERRORS_H */

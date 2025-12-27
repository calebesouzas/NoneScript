#include "errors.h"

#include <stdio.h>

void panic(const char *local, const char *reason, const char **details) {
  (void)printf("Panicked at '%s'\nReason: %s\n", local, reason);

  if (details != NULL) {
    unsigned int i = 0;
    puts("Details:\n");
    do {
      (void)printf("\t%s\n", details[i]);
      ++i;
    } while (details[i] != NULL);
  }
}

#include "errors.h"

#include <stdio.h>
#include <stdlib.h>

void panic(const char *local, const char *reason) {
  (void)printf("Panicked at '%s'\nReason: %s\n", local, reason);
  exit(1);
}

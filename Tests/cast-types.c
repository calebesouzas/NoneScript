#include <stdio.h>
int stringToInt(const char *value) {
  int result = 0;
  for (int i = 0; value[i] != '\0'; i++) {
    result = (result * 10) + (value[i] - '0');
  }
  return result;
}

int main() {
  char number[] = "123";
  printf("%s\n", number);
  printf("%d\n", stringToInt(number));
  return 0;
}

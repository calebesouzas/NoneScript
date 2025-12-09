#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

/* Function `check_for_reserved_keyword`:
 * takes a `token_t` pointer as a parameter. 
 * Compares the `token_t`->value to each keyword,
 * if someone matches, it sets `token_t`->type to the corresponding keyword */

void check_for_reserved_keyword(token_t *token) {
  const char *identifier = token->value;
  if (!strncmp(identifier, "let", 3)) {
    token->type = LetKeyword;
  }
  else if (!strncmp(identifier, "const", 5)) {
    token->type = ConstKeyword;
  }
}

// Function `add_token`: appends a token into a token array
void add_token(token_t *tokens,     // tokens array
               token_t* token,      // token to be added
               const char *value,   // string to be token's value 
                                    // (optional - when set to NULL)
               unsigned int *index);// index of last item (auto-increments)

/* Function `tokenize`:
 * @param string `sourceCode`
 * Generates an array of tokens based on `sourceCode`'s content' */

LexerResult tokenize(const char *sourceCode) {
  size_t sourceCodeSize = strlen(sourceCode);
  token_t *tokens = (token_t *)malloc(sourceCodeSize * sizeof(token_t));
  if (tokens == NULL) {
    return (LexerResult){
      .tokens = NULL,
      .count = 0,
      .status = Error,
      .error = MemoryAllocationFailed
    };
  }
  unsigned int tokensAdded = 0;

  LexerResult result = {
    .tokens = tokens,
    .count = tokensAdded,
    .status = Ok
  };

  for (unsigned int i = 0; i < sourceCodeSize; i++) {
    char currentChar = sourceCode[i];
    // First we check if the current character is any
    // whitespace, tab, newline or return character.
    // Then, we skip it
    switch (currentChar) {
      case  ' ':
      case '\n':
      case '\r':
      case '\t':
        continue;
    }
    token_t tok;
    tok.value[0] = '\0';
    unsigned int passSwitch = 0;
    switch (currentChar) {
      case '+':
      case '-':
      case '*':
      case '/':
        tok.type = BinaryOperator;
        add_token(tokens, &tok, &currentChar, &tokensAdded);
        passSwitch = 1;
        break;
      case '!':
        tok.type = ExclamationMark;
        add_token(tokens, &tok, &currentChar, &tokensAdded);
        passSwitch = 1;
        break;
      case '?':
        tok.type = QuestionMark;
        add_token(tokens, &tok, &currentChar, &tokensAdded);
        passSwitch = 1;
        break;
      case '(':
        tok.type = OpenParen;
        add_token(tokens, &tok, &currentChar, &tokensAdded);
        passSwitch = 1;
        break;
      case ')':
        tok.type = CloseParen;
        add_token(tokens, &tok, &currentChar, &tokensAdded);
        passSwitch = 1;
        break;
      case '\0':
        tok.type = EndOfFile;
        tokens[tokensAdded] = tok;
        passSwitch = 1;
        return result;
    }

    // Somethings are better to verify with if - else statements
    // But we only do it if `currentChar` didn't match any case
    // in the previous switch - case statement
    if (!passSwitch) {
      if (isalpha(currentChar)) {
        tok.type = Identifier;
        int startI = i;
        int tempI = i;
        while (isalpha(sourceCode[tempI])) {
          tempI++;
        }
        
        unsigned int lastChar = tempI - startI;
        strncpy(tok.value, sourceCode + startI, lastChar);
        tok.value[lastChar] = '\0';

        i = tempI - 1;
        check_for_reserved_keyword(&tok);
        add_token(tokens, &tok, NULL, &tokensAdded);
      }
      else if (isdigit(currentChar)) {
        tok.type = Number;
        int startI = i;
        int tempI = i;
        while (isdigit(sourceCode[tempI]) && 
              (tempI - startI) < sizeof(tok.value)) {
          tempI++;
        }
        unsigned int lastNumber = tempI - startI;
        strncpy(tok.value, sourceCode + startI, lastNumber);
        tok.value[lastNumber] = '\0';
        
        i = tempI - 1;
        add_token(tokens, &tok, NULL, &tokensAdded);
      }
      else {
        strncat(tok.value, &currentChar, 1);
        tokens[tokensAdded] = tok;
        return (LexerResult) {
          .tokens = tokens,
          .status = Error,
          .error = UnrecognizedToken,
          .count = tokensAdded
        };
      }
    }
  }
  result.count = tokensAdded;
  return result;
}

void
add_token(token_t* tokens,    // tokens array
          token_t *token,     // token to add
          const char *value,  // string to be token's value
          unsigned int* index // `tokensAdded` variable
          ) {
  if (value != NULL) {
    token->value[0] = *value;
    token->value[1] = '\0';
  }
  tokens[(*index)] = (*token);
  (*index)++;
}

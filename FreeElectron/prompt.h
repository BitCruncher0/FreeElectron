#pragma once

/* Prints out a message and prompts the user for input.
   The zero-terminated input is stored in the buffer; the newline is stripped.

   Characters are read up until the first newline or until
   num_chars - 1 are read, whichever comes first.

   Returns a pointer to the buffer. */
char *prompt(const char *msg, char *buffer, size_t num_chars);

/* Like prompt(), except a quit string is given.

   If the input is the same as quit_str, returns 1.
   Returns 0 otherwise. */
char prompt_quit(
    const char *msg, char *buffer, size_t num_chars, const char *quit_str);

/* Continually prompts the user for a long-formatted string until one is given
   or until the input is equal to quit_str.

   If the input was equal to quit_str, then the flag pointed to by req is set
   and returns 0.

   Otherwise, the flag pointed to by req is cleared
   and returns the long value. */
long prompt_long(const char *msg, const char *quit_str, char *req);
double prompt_double(const char *msg, const char *quit_str, char *req);

/* Strips str of the newline character at the end.

   Returns 0 on successful removal or 1 if no newline
   character is found.

   str points to a zero-terminated string that contains at most one
   newline character. */
char removeNewline(char *str);

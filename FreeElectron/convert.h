#pragma once

/* Converts zero-terminated string to long int.
   If no conversion could be made, flag at conversion_error is set and
   returns 0.
   Otherwise, flag at conversion_error is cleared and returns the value. */
long cstr_to_long(const char *, char *conversion_error);
double cstr_to_double(const char *, char *conversion_error);

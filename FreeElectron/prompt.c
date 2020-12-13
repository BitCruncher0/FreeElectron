#include <stdio.h>

#include "prompt.h"


char *prompt(const char *msg, char *buffer, size_t num_chars)
{
    fputs(msg, stdout);
    fgets(buffer, num_chars, stdin);
    removeNewline(buffer);
    return buffer;
}


char prompt_quit(
    const char *msg, char *buffer, size_t num_chars, const char *quit_str)
{
    if(strcmp(prompt(msg, buffer, num_chars), quit_str)) return 0;
    else return 1;
}

#include <stdio.h>
#include <string.h>

#include "defines.h"
#include "prompt.h"
#include "convert.h"


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


long prompt_long(const char *msg, const char *quit_str, char *request_quit)
{
    while(1) {
        char buf[INPUT_BUFFER_SIZE + 1];
        if(prompt_quit(msg, buf, INPUT_BUFFER_SIZE + 1, quit_str)) {
            *request_quit = 1;
            return 0;
        }

        // Attempt to convert string to numerical
        char conversion_error;
        long result = cstr_to_long(buf, &conversion_error);
        if(conversion_error) {
            fputs("Invalid input\n\n", stdout);
            continue;
        }

        *request_quit = 0;
        return result;
    }
}


double prompt_double(const char *msg, const char *quit_str, char *request_quit)
{
    while(1) {
        char buf[INPUT_BUFFER_SIZE + 1];
        if(prompt_quit(msg, buf, INPUT_BUFFER_SIZE + 1, quit_str)) {
            *request_quit = 1;
            return 0;
        }

        // Attempt to convert string to numerical
        char conversion_error;
        double result = cstr_to_double(buf, &conversion_error);
        if(conversion_error) {
            fputs("Invalid input\n\n", stdout);
            continue;
        }

        *request_quit = 0;
        return result;
    }
}


char removeNewline(char *str)
{
    int i;
    for(i = 0; str[i] != 0; i++) {
        if(str[i] == '\n') {
            str[i] = 0;
            return 0;
        }
    }
    return 1;
}

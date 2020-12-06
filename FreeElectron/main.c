#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//#define PRINT_DIAMETERS
//#define PRINT_AREAS
#define RUN_REAL_PROGRAM

#define PI                  3.14159
#define AVOGADROS_NUMBER    6.02 * pow(10, 23);
#define INPUT_BUFFER_SIZE   255

double calculateDiameter(int);
double calcArea(double);
double volumeCylinder(double, double);
char removeNewline(char *);
long prompt_long(const char *show, const char *quit, char *req);
char *prompt(const char *, char *, size_t);
char promptQuit(const char *in, char *out, size_t buf_size, const char *quit);
long int cstr_to_long(const char *, char *conversion_err);
double prompt_double(const char *show, const char *quit, char *req);




struct Material {
    const double ATOMIC_MASS;           //g / mol
    const int FREE_ELECTRONS_PER_ATOM;  //#
    const double VOLUMETRIC_DENSITY;    //g / cm3
};



const struct Material COPPER = {
    63.546,
    1,
    8.96
};

/* Returns diameter (in millimeters) of given AWG */
double calculateDiameter(int awg)
{
    return 0.127 * pow(92, (36.0 - awg) / 39);
}


double calcArea(double radius)
{
    return PI * pow(radius, 2);
}


double volumeCylinder(double radius, double length)
{
    return length * calcArea(radius);
}


int main(int argc, char **argv)
{
#ifdef PRINT_DIAMETERS
    {
        int awg;
        for(awg = 0; awg <= 36; awg++) {
            printf("%d: %.*F\n", awg, 3, calculateDiameter(awg));
        }
    }
    fputc('\n', stdout);
#endif

#ifdef PRINT_AREAS
    {
        int awg;
        for(awg = 0; awg <= 36; awg++) {
            printf("%d: %.*F\n", awg, 3, calcArea(calculateDiameter(awg) / 2.0));
        }
    }
    fputc('\n', stdout);
#endif

#ifdef RUN_REAL_PROGRAM
    /* Todo
       1. Prompt for radius instead of AWG */

    /* PROGRAM FLOW

       1. Prompt for AWG
       2. Prompt for wire length
       3. Give volume */

    char request_exit;
    long awg;
    double radius;
    double diameter;
    double area;
    double volume;
    double length_in_mm;


    awg = -1;
    while((awg < 0) || (awg > 36)) {
        awg = prompt_long(
            "AWG [0 - 36]? ",
            "",
            &request_exit);
        if(request_exit) return 0;
        /* 0 <= AWG <= 36 */
        if((awg < 0) || (awg > 36)) {
            fputs("Not a valid AWG\n", stdout);
        }
    }

    length_in_mm = 0;
    while(length_in_mm <= 0) {
        length_in_mm = prompt_double(
            "Wire length (mm) (0 - inf)? ",
            "",
            &request_exit);
        if(request_exit) return 0;
        /* 0 < Wire length */
        if(length_in_mm <= 0) {
            fputs("Not a valid wire length\n", stdout);
        }
    }
    diameter = calculateDiameter(awg);
    radius = diameter / 2.0;
    area = calcArea(radius);
    volume = volumeCylinder(radius, length_in_mm);
    printf("AWG %li\n", awg);
    printf(
        "radius: %.*F mm\tdia: %.*F mm\tarea: %.*F mm^2\n",
        4,
        radius,
        4,
        diameter,
        4,
        area);
    printf("volume: %.*F mm^3\n", 4, volume);

#endif
}

/* Strips str of the newline character at the end

   Returns 0 on successful removal or 1 or 0 if no newline
   character is found

   str points to a zero-terminated string */
char removeNewline(char *str)
{
    int i;
    for(i = 0; str[i] != 0; i++) {
        if(str[i] == '\n') {
            str[i] = 0;
            return 0;
        }
    } return 1;
}

long prompt_long(
    const char *query,
    const char *quit,
    char *request_quit)
{
    while(1) {
        char input[INPUT_BUFFER_SIZE + 1];
        if(promptQuit(query, input, INPUT_BUFFER_SIZE + 1, quit)) {
            *request_quit = 1;
            return 0;
        }
        else *request_quit = 0;

        /* Convert string to numerical */
        char conversion_error;
        long result = cstr_to_long(input, &conversion_error);
        if(conversion_error) {
            fputs("Invalid input\n", stdout);
            continue;
        }

        return result;
    }
}

char *prompt(const char *out, char *input_buffer, size_t buffer_size)
{
    fputs(out, stdout);          /* Print the prompt */
    fgets(input_buffer, buffer_size, stdin);
    removeNewline(input_buffer); /* fgets() includes the newline, so strip it */
    return input_buffer;
}

char promptQuit(const char *out, char *in, size_t buf_size, const char *quit_str) {
    if(strcmp(prompt(out, in, buf_size), quit_str)) return 0;
    else return 1; /* user entered quit string */
}

long cstr_to_long(const char *str, char *conversion_err) {
    char *end;
    long result = strtol(str, &end, 10);
    *conversion_err = ((*end) == 0) ? 0 : 1;
    return result;
}

double cstr_to_double(const char *str, char *conversion_err) {
    char *end;
    double result = strtod(str, &end);
    *conversion_err = ((*end) == 0) ? 0 : 1;
    return result;
}

double prompt_double(const char *show, const char *quit, char *request_quit) {
    while(1) {
        char input[INPUT_BUFFER_SIZE + 1];
        if(promptQuit(show, input, INPUT_BUFFER_SIZE + 1, quit)) {
            *request_quit = 1;
            return 0;
        }
        else *request_quit = 0;

        /* Convert string to numerical */
        char conversion_error;
        double result = cstr_to_double(input, &conversion_error);
        if(conversion_error) {
            fputs("Invalid input\n", stdout);
            continue;
        }

        return result;
    }
}

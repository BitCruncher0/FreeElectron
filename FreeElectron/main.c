#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define RUN_REAL_PROGRAM

#define PRECISION           3
#define PI                  3.14159
#define AVOGADROS_NUMBER    6.022 * pow(10, 23)
#define ELECTRONIC_CHARGE   1.602 * pow(10, -19)
#define INPUT_BUFFER_SIZE   255

double calc_diameter(int AWG);
double calc_area(double radius);
double calc_volume_cylinder(double radius, double length);
char removeNewline(char *);
long prompt_long(const char *show, const char *quit, char *req);
char *prompt(const char *, char *, size_t);
char prompt_quit(const char *out, char *in, size_t buf_size, const char *quit);
long int cstr_to_long(const char *, char *conversion_err);
double prompt_double(const char *show, const char *quit, char *req);
double mm3_to_cm3(double);
double calc_moles(double mass, double molar_mass);
double calc_num_atoms(double moles);
double calc_free_electrons(double atoms, double free_elec_per_atom);
double calc_charge(double num_electrons);
double calc_carrier_density(double particles, double volume);
double calc_drift_speed(double current, double carr_density, double area);
void TEST_print_awg_diameters(void);
void TEST_print_awg_areas(void);
int get_awg(char *quit);
double get_length(char *quit);




struct Material {
    const char *NAME;
    const double ATOMIC_MASS;           //g / mol
    const int FREE_ELECTRONS_PER_ATOM;  //#
    const double VOLUMETRIC_DENSITY;    //g / cm3
};



struct Material *prompt_material(char *quit);
struct Material *str_to_material(const char *);

const struct Material COPPER = { "copper", 63.546, 1, 8.96 };
const struct Material CARBON = { "carbon", 12.011, 1, 2.26 };

const struct Material NULL_MATERIAL = { "null_material", 0, 0, 0 };

int main(int argc, char **argv)
{
#ifdef RUN_REAL_PROGRAM
    /* Todo
       1. Prompt for radius instead of AWG */

    /* PROGRAM FLOW

       1. Prompt for AWG
       2. Prompt for wire length
       3. Give statistics

       To quit, press enter at prompts */

    while(1) {
        char request_exit;

        const struct Material *material = prompt_material(&request_exit);
        if(request_exit) return 0;

        int awg = get_awg(&request_exit);
        if(request_exit) return 0;

        double length = get_length(&request_exit);
        if(request_exit) return 0;

        double diameter = calc_diameter(awg);
        double radius = diameter / 2.0;
        double area = calc_area(radius);
        double volume = calc_volume_cylinder(radius, length);
        double volume_in_cm3 = mm3_to_cm3(volume);

        // mass = density x volume
        double mass_in_grams =
            material->VOLUMETRIC_DENSITY * volume_in_cm3;

        // moles = mass / molar mass
        double moles =
            mass_in_grams / material->ATOMIC_MASS;

        double atoms = AVOGADROS_NUMBER * moles;

        double free_electrons =
            material->FREE_ELECTRONS_PER_ATOM * atoms;

        double free_charge = free_electrons * -ELECTRONIC_CHARGE;
        double carrier_density = free_electrons / volume;
        double drift_speed = calc_drift_speed(1.0, carrier_density, area);


        printf("%i AWG %s\n", awg, material->NAME);
        printf(
            "radius: %.*F mm\tdia: %.*F mm\tarea: %.*F mm^2\n",
            PRECISION,
            radius,
            PRECISION,
            diameter,
            PRECISION,
            area);
        printf("volume: %.*F mm^3\n", PRECISION, volume);
        printf("mass: %.*F g\n", PRECISION, mass_in_grams);
        printf("moles: %.*F mol\n", 2 * PRECISION, moles);
        printf("atoms: %.*E atom\n", PRECISION, atoms);
        printf("free elec: %.*E elec\n", PRECISION, free_electrons);
        printf("free charge: %.*E C\n", 2 * PRECISION, free_charge);
        printf("carrier density: %.*E elec/mm^3\n", PRECISION, carrier_density);
        printf("sdrift @ 1 A: %.*E mm/s\n", PRECISION, drift_speed);

        fputc('\n', stdout);
    }
#endif
}

struct Material *prompt_material(char *quit)
{
    while(1) {
        char buf[INPUT_BUFFER_SIZE + 1];
        if(prompt_quit("Material? ", buf, INPUT_BUFFER_SIZE + 1, "")) {
            *quit = 1;
            return &NULL_MATERIAL;
        }
        struct Material *p_mat = str_to_material(buf);
        if(p_mat == &NULL_MATERIAL) {
            fputs("Not a valid material\n", stdout);
        }
        else {
            *quit = 0;
            return p_mat;
        }
    }
}

struct Material *str_to_material(const char *str)
{
    if(!strcmp(str, "copper")) return &COPPER;
    else if(!strcmp(str, "carbon")) return &CARBON;
    else return &NULL_MATERIAL;
}

int get_awg(char *quit)
{
    long awg = -1;
    while((awg < 0) || (awg > 36)) {
        awg = prompt_long("AWG [0 - 36]? ", "", quit);
        if(*quit) return 0;

        /* 0 <= AWG <= 36 */
        if((awg < 0) || (awg > 36)) {
            fputs("Not a valid AWG\n", stdout);
        }
    }
    *quit = 0;
    return (int)awg;
}

double get_length(char *quit)
{
    double length = 0;
    while(length <= 0) {
        length =
            prompt_double("Wire length (mm) (0 - inf)? ", "", quit);
        if(*quit) return 0;

        /* 0 < Wire length */
        if(length <= 0) {
            fputs("Not a valid wire length\n", stdout);
        }
    }
    *quit = 0;
    return length;
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
        if(prompt_quit(query, input, INPUT_BUFFER_SIZE + 1, quit)) {
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

/* Prints out a prompt and allows the user to enter some
   input.

   Returns a pointer to the zero-terminated response.
   The newline will be stripped. */
char *prompt(const char *out, char *input_buffer, size_t buffer_size)
{
    fputs(out, stdout);             // Print the prompt
    fgets(input_buffer, buffer_size, stdin); // Receive the response
    removeNewline(input_buffer);
    return input_buffer;
}

/* Prints out a prompt and allows the user to enter some
   input.

   If the response is the same as quit_str, returns 1.
   Returns 0 otherwise.

   in will contain a pointer to the zero-terminated response.
   The newline will be stripped. */
char prompt_quit(const char *out, char *in, size_t buf_size, const char *quit_str)
{
    if(strcmp(prompt(out, in, buf_size), quit_str)) return 0;
    else return 1;
}

long cstr_to_long(const char *str, char *conversion_err)
{
    char *end;
    long result = strtol(str, &end, 10);
    *conversion_err = ((*end) == 0) ? 0 : 1;
    return result;
}

double cstr_to_double(const char *str, char *conversion_err)
{
    char *end;
    double result = strtod(str, &end);
    *conversion_err = ((*end) == 0) ? 0 : 1;
    return result;
}

double prompt_double(const char *show, const char *quit, char *request_quit)
{
    while(1) {
        char input[INPUT_BUFFER_SIZE + 1];
        if(prompt_quit(show, input, INPUT_BUFFER_SIZE + 1, quit)) {
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

/* Returns diameter (in millimeters) of given AWG */
double calc_diameter(int awg)
{
    return 0.127 * pow(92, (36.0 - awg) / 39);
}

double calc_area(double radius)
{
    return PI * pow(radius, 2);
}

double calc_volume_cylinder(double radius, double length)
{
    return length * calc_area(radius);
}

double mm3_to_cm3(double mm3) {
    return mm3 / 1000.0;
}

double calc_moles(double mass, double molar_mass) {
    return mass / molar_mass;
}

double calc_num_atoms(double moles) {
    return moles * AVOGADROS_NUMBER;
}

double calc_free_electrons(double atoms, double free_elec_per_atom) {
    return atoms * free_elec_per_atom;
}

double calc_charge(double num_electrons) {
    return num_electrons * -ELECTRONIC_CHARGE;
}

double calc_carrier_density(double particles, double volume) {
    return particles / volume;
}

double calc_drift_speed(double current, double carr_density, double area) {
    return current / (carr_density * ELECTRONIC_CHARGE * area);
}

void TEST_print_awg_diameters(void)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calc_diameter(awg));
    }
    fputc('\n', stdout);
}

void TEST_print_awg_areas(void)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calc_area(calc_diameter(awg) / 2.0));
    }
    fputc('\n', stdout);
}

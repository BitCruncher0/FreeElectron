#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "defines.h"
#include "prompt.h"
#include "convert.h"
#include "geometry.h"
#include "material.h"
#include "wire.h"


double calc_drift_speed(double current, double carrier_density, double area)
{
    return current / (carrier_density * ELECTRONIC_CHARGE * area);
}


int main(void)
{
#ifdef RUN_REAL_PROGRAM
    /* Todo
       1. Prompt for radius instead of AWG */

    /* PROGRAM FLOW

       1. Prompt for wire material
       2. Prompt for AWG
       3. Prompt for wire length
       4. Give statistics

       To quit, press enter at prompts */

    while(1) {
        char request_program_quit;

        const struct Material *material = prompt_material(&request_program_quit);
        if(request_program_quit) return 0;

        int awg = prompt_awg(&request_program_quit);
        if(request_program_quit) return 0;

        double length = prompt_length(&request_program_quit);
        if(request_program_quit) return 0;

        double diameter = awg_diameter(awg);
        double radius = diameter / 2.0;
        double area = area_circle(radius);
        double volume = volume_cylinder(radius, length);
        double volume_in_cm3 = mm3_to_cm3(volume);

        // mass = density x volume
        double mass_in_grams =
            material->VOLUMETRIC_DENSITY * volume_in_cm3;

        // moles = mass / molar mass
        double moles =
            mass_in_grams / material->ATOMIC_MASS;

        double atoms =
            AVOGADROS_NUMBER * moles;

        double free_electrons =
            material->FREE_ELECTRONS_PER_ATOM * atoms;

        double free_charge =
            free_electrons * -ELECTRONIC_CHARGE;

        double carrier_density =
            free_electrons / volume;

        double drift_speed =
            calc_drift_speed(1.0, carrier_density, area);

        fputc('\n', stdout);

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

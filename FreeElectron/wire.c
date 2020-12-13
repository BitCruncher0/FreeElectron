#include <stdio.h>
#include <math.h>
#include "prompt.h"
#include "geometry.h"

double awg_diameter(int awg)
{
    return 0.127 * pow(92, (36.0 - awg) / 39);
}

int prompt_awg(char *quit)
{
    while(1) {
        long awg = prompt_long("AWG [0 - 36]? ", "", quit);
        if(*quit) return 0;

        // 0 <= AWG <= 36
        else if((awg < 0) || (awg > 36)) fputs("Not a valid AWG\n\n", stdout);
        else {
            *quit = 0;
            return (int)awg;
        }
    }
}

double prompt_length(char *quit)
{
    while(1) {
        double length = prompt_double("Wire length (mm) (0 - inf)? ", "", quit);
        if(*quit) return 0;

        // 0 < Wire length
        else if(length <= 0) fputs("Not a valid wire length\n\n", stdout);
        else {
            *quit = 0;
            return length;
        }
    }
}

void TEST_print_awg_diameters(void)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, awg_diameter(awg));
    }
    fputc('\n', stdout);
}

void TEST_print_awg_areas(void)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%i: %.*F\n", awg, 3, area_circle(awg_diameter(awg) / 2.0));
    }
    fputc('\n', stdout);
}

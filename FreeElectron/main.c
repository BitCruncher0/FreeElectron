#include <stdio.h>
#include <math.h>


#define PI                  3.14159
#define AVOGADROS_NUMBER    6.02 * pow(10, 23);



struct Material {
    const double ATOMIC_MASS;
    const int FREE_ELECTRONS_PER_ATOM;
    const double VOLUMETRIC_DENSITY;
};


double calculateDiameter(int awg)
{
    return 0.127 * pow(92, (36.0 - awg) / 39);
}


double calcArea(double diameter)
{
    return PI * pow(diameter / 2.0, 2);
}


int main(int argc, char **argv)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calculateDiameter(awg));
    }
    fputc('\n', stdout);
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calcArea(calculateDiameter(awg)));
    }
}

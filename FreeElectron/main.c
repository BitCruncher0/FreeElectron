#include <stdio.h>
#include <math.h>


#define PI 3.14159


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

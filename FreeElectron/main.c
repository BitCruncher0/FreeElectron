#include <stdio.h>
#include <math.h>


double calculateDiameter(int awg)
{
    return 0.127 * pow(92, (36.0 - awg) / 39);
}


int main(int argc, char **argv)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calculateDiameter(awg));
    }
}

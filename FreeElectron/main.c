#include <stdio.h>
#include <math.h>


double calculateDiameter(int awg)
{
    return (double)0.127 * pow(92, (double)((36 - awg) / 39));
}


int main(int argc, char **argv)
{
    fputs("Hello, world!", stdout);
}

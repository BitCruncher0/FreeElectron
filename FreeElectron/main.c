#include <stdio.h>
#include <math.h>
#include <string.h>


#define PI                  3.14159
#define AVOGADROS_NUMBER    6.02 * pow(10, 23);
#define INPUT_BUFFER_SIZE   256



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


int queryPositiveInt(const char *query, const char *err)
{
    while(7) {
        fputs(query, stdout);
        char input[INPUT_BUFFER_SIZE] = { 0 };
        memset((char *)input, 0, INPUT_BUFFER_SIZE);
        fgets((char *)input, INPUT_BUFFER_SIZE, stdin);

        /*
        //if(strResult == "quit") return -1;
        // Need to check for invalid conversion of stoi()
        int result = stoi(strResult, nullptr);

        // Must be positive number greater than zero.
        // Anything else is error
        if(!(result > 0)) {
            cout << err << endl;
            continue;
        }
        return result;
        */
    }
}


int main(int argc, char **argv)
{
    int awg;
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calculateDiameter(awg));
    }
    fputc('\n', stdout);
    for(awg = 0; awg <= 36; awg++) {
        printf("%d: %.*F\n", awg, 3, calcArea(calculateDiameter(awg) / 2.0));
    }
    //1. Prompt for awg
    //2. Prompt for length
    //3. Give volume
}

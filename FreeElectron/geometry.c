#include <math.h>
#include "defines.h"

double area_circle(double radius)
{
    return PI * pow(radius, 2);
}

double volume_cylinder(double radius, double length)
{
    return length * area_circle(radius);
}

double mm3_to_cm3(double mm3)
{
    return mm3 / 1000.0;
}

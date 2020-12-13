#pragma once

struct Material {
    const char *NAME;
    const double ATOMIC_MASS;           //g / mol
    const int FREE_ELECTRONS_PER_ATOM;  //#
    const double VOLUMETRIC_DENSITY;    //g / cm3
};

void print_materials_list(void);
const struct Material *str_to_material(const char *str);
const struct Material *prompt_material(char *quit);

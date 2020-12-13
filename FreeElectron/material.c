#include <stdio.h>
#include <string.h>
#include "defines.h"
#include "material.h"
#include "prompt.h"

const struct Material COPPER = {
    "copper",
    63.546,
    1,
    8.96 };

const struct Material ALUMINIUM = {
    "aluminium",
    26.982,
    3,
    2.7 };

const struct Material GOLD = {
    "gold",
    196.97,
    1,
    19.3 };

const struct Material NULL_MATERIAL = {
    "null_material",
    0,
    0,
    0 };

void print_materials_list(void)
{
    fputs("Materials list\n", stdout);
    fputs("1. copper\n", stdout);
    fputs("2. aluminium\n", stdout);
    fputs("3. gold", stdout);
}

const struct Material *str_to_material(const char *str)
{
    if(!strcmp(str, "copper")) return &COPPER;
    else if(!strcmp(str, "aluminium")) return &ALUMINIUM;
    else if(!strcmp(str, "gold")) return &GOLD;
    else return &NULL_MATERIAL;
}

const struct Material *prompt_material(char *quit)
{
    while(1) {
        print_materials_list();
        fputs("\n\n", stdout);

        char buf[INPUT_BUFFER_SIZE + 1];
        if(prompt_quit("Material? ", buf, INPUT_BUFFER_SIZE + 1, "")) {
            *quit = 1;
            return &NULL_MATERIAL;
        }
        else {
            const struct Material *p_mat = str_to_material(buf);
            if(p_mat == &NULL_MATERIAL) {
                fputs("Not a valid material\n\n", stdout);
            }
            else {
                *quit = 0;
                return p_mat;
            }
        }
    }
}

#pragma once

/* Returns diameter (in millimeters) of given AWG */
double awg_diameter(int AWG);

/* Continually prompts the user for a valid wire gauge number until one is
   entered or until an empty string is entered.

   If an empty string is entered, the flag pointed to by quit is set and
   returns 0, otherwise the flag at quit is cleared and returns the wire
   gauge. */
int prompt_awg(char *quit);
double prompt_length(char *quit);

void TEST_print_awg_diameters(void);
void TEST_print_awg_areas(void);

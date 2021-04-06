#include "stdio.h"
#include "stdlib.h"

// Inclusion des différentes fonctions
#include "define.h"
#include "affichage.h"

int main(int argc, char const *argv[])
{
    oxy myOxy;
    myOxy.pouls = 96;
    myOxy.spo2 = 125;

    affichage(myOxy);
    return EXIT_SUCCESS;
}

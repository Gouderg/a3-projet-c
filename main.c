#include "stdio.h"
#include "stdlib.h"

// Inclusion des différentes fonctions
#include "define.h"
#include "iir.h"
#include "fir.h"
#include "mesure.h"
#include "integration.h"
#include "lecture.h"
#include "affichage.h"


int main() {  

    absorp data = initAbsorp();
    absorp y = initAbsorp();
    absorp x_1 = initAbsorp();
    oxy oxy = initOxy();
    periode myPeriode = initPeriode();
    ac_struct buffer[51] = {0}; // buffer circulaire initialisé à 0
    FILE* fichier = initFichier("record1_bin.dat");
    int etat = 0;
    if (fichier != NULL) {
        do {
            data = lecture(fichier, &etat); // lecture de la ligne
            //printf("%f %f %f %f \n", data.acr, data.dcr, data.acir, data.dcir);
            if (etat != EOF) {
                data = FIR(data, buffer); // Application du filtre FIR
                y = IIR(data, x_1, y);    // Application du filtre IIR
                x_1 = data;
                oxy = mesure(y, &myPeriode);    // On effectue la mesure
                affichage(oxy);
            }
            
        } while (etat != EOF);
    }
    finFichier(fichier);
    return EXIT_SUCCESS;
}

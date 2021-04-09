/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: integration.c                     - */
/* - Utilisation: fonctions liées à intégration - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#include "integration.h"

/* ------------------------------------------------- */
/* - Nom: integrationTest                          - */
/* - Description: Appel successivement chaque      - */
/* -              fonction après ouvert un fichier - */
/* - Paramètre: char*                              - */
/* - Return: void                                  - */
/* ------------------------------------------------- */
void integrationTest(char* filename) {
    absorp data = initAbsorp();
    absorp y = initAbsorp();
    absorp x_1 = initAbsorp();
    oxy oxy = initOxy();
    periode myPeriode = initPeriode();
    ac_struct buffer[51] = {0}; // buffer circulaire initialisé à 0
    FILE* fichier = initFichier(filename);
    int etat = 0;

    if (fichier != NULL) {
        do {
            data = lireFichier(fichier, &etat); // lecture de la ligne
            if (etat != EOF) {
                data = FIR(data, buffer);       // Application du filtre FIR
                y = IIR(data, &x_1, y);         // Application du filtre IIR
                oxy = mesure(y, &myPeriode);    // On effectue la mesure
                affichage(oxy);
            }
        } while (etat != EOF);
    }
    finFichier(fichier);
}
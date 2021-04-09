/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: iir.c                             - */
/* - Utilisation: fonctions liées au filtre iir - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#include "iir.h"

/* ------------------------------------------------- */
/* - Nom: iirTest                                  - */
/* - Description: Lis chaque trame dans un fichier - */
/* -                  et applique la fonction IIR  - */
/* - Paramètre: char*                              - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp iirTest(char* filename) {
    absorp x = initAbsorp();
    absorp y = initAbsorp();
    absorp x_1 = initAbsorp();
    int etat = 0;
    // Ouvre le fichier filename et renvoie un pointeur sur le premier caractère
    FILE* fichier = initFichier(filename);

    if (fichier != NULL) {
        do {
            x = lireFichier(fichier, &etat);    // Lis une trame et la renvoie sous forme absorp 
            if (etat != EOF) {
                y = IIR(x, &x_1, y);            // Applique le filtre IIR
            }
        } while (etat != EOF);
    }
    
    // Ferme le fichier
    finFichier(fichier);

    return y;
}

/* ------------------------------------------------- */
/* - Nom: FIR                                      - */
/* - Description: Applique un filtre passe-haut    - */
/* - Paramètre: absorp, absorp*, absorp            - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp IIR(absorp x, absorp* x_1, absorp y_1) {

    float acr = 0, acir = 0;

    acr = x.acr - x_1->acr + ALPHA * y_1.acr;
    acir = x.acir - x_1->acir + ALPHA * y_1.acir;
    
    *x_1 = x;
    x.acr = acr;
    x.acir = acir;
    return x;
}

/* ------------------------------------------------- */
/* - Nom: initOxy                                  - */
/* - Description: Initialise une structure oxy     - */
/* - Paramètre: void                               - */
/* - Return: oxy                                   - */
/* ------------------------------------------------- */
oxy initOxy(void) {
    oxy temp;
    temp.spo2 = 85;
    temp.pouls = 69;
    return temp;
}
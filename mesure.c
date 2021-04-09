/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: mesure   .c                       - */
/* - Utilisation: fonctions liées à mesure      - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#include "mesure.h"

/* ----------------------------------------------- */
/* - Nom: mesureTest                             - */
/* - Description: Lecture fichier et appel       - */
/* -             fonction mesure                 - */
/* - Paramètre: oxy                              - */
/* - Return: void                                - */
/* ----------------------------------------------- */
oxy mesureTest(char* filename) {
    periode myPeriode = initPeriode();

    oxy myOxy;
    absorp data;
    int etat = 0;
    FILE* fichier = initFichier(filename);
    
    if (fichier != NULL) {
        do {
            data = lireFichier(fichier, &etat);
            if (etat != EOF) {
                myOxy = mesure(data, &myPeriode);   // Appel de la fonction mesure
            }
        } while (etat != EOF);
    }

    finFichier(fichier);
    return myOxy;
}

/* ------------------------------------------------- */
/* - Nom: mesure                                   - */
/* - Description: Calcul un pouls et un sp02       - */  
/* -              en fonction de data              - */
/* - Paramètre: absorp, periode*                   - */
/* - Return: oxy                                   - */
/* ------------------------------------------------- */
oxy mesure(absorp data, periode* perio) {
    
    // Si on détecte un front montant
    if (data.acr >= 0 && perio->lastValue < 0) {
        // On calcul le pouls en faisant la moyenne avec la valeur précédente
        perio->lastoxy.pouls = (perio->lastoxy.pouls + 30000/perio->compteur_pouls)/2;
        
        // On calcul le ration RsIR
        float ratio = (((perio->acr_max - perio->acr_min)/data.dcr) / ((perio->acir_max - perio->acir_min)/data.dcir));
        
        // En fonction du ratio on applique une formule
        if (ratio < 0.4) {
            perio->lastoxy.spo2 = 100;
        } else if (ratio > 3.4) {
            perio->lastoxy.spo2 = 0;
        } else if (ratio > 1) {
            perio->lastoxy.spo2 = -35.71 * ratio + 121.42;
        } else {
            perio->lastoxy.spo2 = -25 * ratio + 110;
        }
        
        //printf("periode: %d => spo2: %d \n",perio->lastoxy.pouls, perio->lastoxy.spo2);
        perio->acir_max = 0;
        perio->acir_min = 0;
        perio->acr_max = 0;
        perio->acr_min = 0;
        perio->compteur_pouls = 0;
    }

    else if (data.acr > 0) {
        perio->acr_max = (data.acr > perio->acr_max) ? data.acr : perio->acr_max;   // Max acr
    } else {
        perio->acr_min = (data.acr < perio->acr_min) ? data.acr : perio->acr_min;   // Min acr
    }

    if (data.acir > 0) {
        perio->acir_max = (data.acir > perio->acir_max) ? data.acir : perio->acir_max;  // Max acir
    } else {
        perio->acir_min = (data.acir < perio->acir_min) ? data.acir : perio->acir_min;  // Min acir
    }
    
    perio->lastValue = data.acr;
    perio->compteur_pouls += 1;
    return perio->lastoxy;
}

/* ------------------------------------------------- */
/* - Nom: initPeriode                              - */
/* - Description: Initialise une strucutre periode - */
/* - Paramètre: void                               - */
/* - Return: periode                               - */
/* ------------------------------------------------- */
periode initPeriode(void) {
    periode myPeriode;

    myPeriode.compteur_pouls = 0;
    myPeriode.acir_max = 0;
    myPeriode.acir_min = 0;
    myPeriode.acr_max = 0;
    myPeriode.acr_min = 0;
    myPeriode.lastoxy.pouls = 0;
    myPeriode.lastoxy.spo2 = 0;
    myPeriode.lastValue = 0;

    return myPeriode;
}
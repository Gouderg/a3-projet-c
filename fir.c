/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: fir.c                             - */
/* - Utilisation: fonctions liées au filtre fir - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#include "fir.h"

/* ------------------------------------------------- */
/* - Nom: firTest                                  - */
/* - Description: Lis chaque trame dans un fichier - */
/* -                  et applique la fonction FIR  - */
/* - Paramètre: char*                              - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp firTest(char* filename) {
    absorp data, lastValue;
    int etat = 0;
    ac_struct buffer[51] = {0}; // buffer circulaire initialisé à 0

    // Ouvre le fichier filename et renvoie un pointeur sur le premier caractère
    FILE* fichier = initFichier(filename);

    if (fichier != NULL) {
        do {
            data = lireFichier(fichier, &etat); // Lis une trame et la renvoie
            if (etat != EOF) {
                lastValue = FIR(data, buffer); // Applique le filtre FIR
            }
        } while (etat != EOF);
    }

    // Ferme le fichier
    finFichier(fichier);

    // Retourne la dernière valeur d'absorption filtré
    return lastValue;
}

/* ------------------------------------------------- */
/* - Nom: FIR                                      - */
/* - Description: Applique un filtre passe-bas     - */
/* -              avec un buffer circulaire        - */
/* - Paramètre: absorp, ac_struct*                 - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp FIR(absorp data, ac_struct* buffer) {
    const float FIR_TAPS[51]={
        1.4774946e-019,
        1.6465231e-004,
        3.8503956e-004,
        7.0848037e-004,
        1.1840522e-003,
        1.8598621e-003,
        2.7802151e-003,
        3.9828263e-003,
        5.4962252e-003,
        7.3374938e-003,
        9.5104679e-003,
        1.2004510e-002,
        1.4793934e-002,
        1.7838135e-002,
        2.1082435e-002,
        2.4459630e-002,
        2.7892178e-002,
        3.1294938e-002,
        3.4578348e-002,
        3.7651889e-002,
        4.0427695e-002,
        4.2824111e-002,
        4.4769071e-002,
        4.6203098e-002,
        4.7081811e-002,
        4.7377805e-002,
        4.7081811e-002,
        4.6203098e-002,
        4.4769071e-002,
        4.2824111e-002,
        4.0427695e-002,
        3.7651889e-002,
        3.4578348e-002,
        3.1294938e-002,
        2.7892178e-002,
        2.4459630e-002,
        2.1082435e-002,
        1.7838135e-002,
        1.4793934e-002,
        1.2004510e-002,
        9.5104679e-003,
        7.3374938e-003,
        5.4962252e-003,
        3.9828263e-003,
        2.7802151e-003,
        1.8598621e-003,
        1.1840522e-003,
        7.0848037e-004,
        3.8503956e-004,
        1.6465231e-004,
        1.4774946e-019
    };
    
    int i;
    float acr = 0, acir = 0;

    // Je dégage la 50ième valeur pour libéré la place en 0
    for (i = 50; i > 0; i--) {
        buffer[i] = buffer[i-1];
    }
    // J'affecte la nouvelle valeur
    buffer[0].acr = data.acr;
    buffer[0].acir = data.acir;


    // On effectue le filtrage
    for (i = 0; i < 51; i++) {
        acir += FIR_TAPS[i] * buffer[i].acir;
        acr += FIR_TAPS[i] * buffer[i].acr;
    }
    
    data.acr = acr;
    data.acir = acir;
    return data;
}

/* ------------------------------------------------- */
/* - Nom: initAbsorp                               - */
/* - Description: Initialise une strucutre absorp  - */
/* - Paramètre: void                               - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp initAbsorp(void) {
    absorp temp;

    temp.acir = 0;
    temp.acr = 0;
    temp.dcr = 0;
    temp.dcir = 0;

    return temp;
}
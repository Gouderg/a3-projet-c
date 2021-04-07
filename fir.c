#include "fir.h"

// record1.dat
absorp firTest(char* filename) {
    absorp data, lastValue;
    int etat = 0;
    ac_struct buffer[51] = {0}; // buffer circulaire initialisé à 0

    // Ouvre le fichier str et lit ses valeurs
    FILE* fichier = initFichier(filename);

    if (fichier != NULL) {
        do {
            data = lireFichier(fichier, &etat);
            if (etat != EOF) {
                lastValue = FIR(data, buffer);
            }
        } while (etat != EOF);
    }
    
    finFichier(fichier);

    // Retourne la dernière valeur d'absorption filtré
    return lastValue;
}

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
    // J'ajoute la nouvelle valeur de data dans mon buffer
    for (i = 50; i > 0; i--) {
        buffer[i] = buffer[i-1];
    }
    buffer[0].acr = data.acr;
    buffer[0].acir = data.acir;


    // // On effectue le filtrage
    for (i = 0; i < 51; i++) {
        acir += FIR_TAPS[i] * buffer[i].acir;
        acr += FIR_TAPS[i] * buffer[i].acr;
    }

    data.acr = acr;
    data.acir = acir;
    return data;
}

absorp initAbsorp(void) {
    absorp temp;

    temp.acir = 0;
    temp.acr = 0;
    temp.dcr = 0;
    temp.dcir = 0;

    return temp;
}
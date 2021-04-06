#include "iir.h"


// record1_fir.dat
absorp iirTest(char* str) {
    absorp x, y, x_1;
    int etat = 0; // Savoir si on est à la fin du programme
    // Ouvre le fichier str et lit ses valeurs
    FILE* fichier = initFichier(str);

    if (fichier != NULL) {
        do {
            x = lireFichier(fichier, &etat);
            if (etat != EOF) {
                y = IIR(x, x_1, y);
                x_1 = x;
            }
        } while (etat != EOF);
    }
    
    finFichier(fichier);

    // Renvoie la dernière valeur filtré
    return y;
}

absorp IIR(absorp x, absorp x_1, absorp y_1) {
    float acr = 0, acir = 0;

    acr = x.acr - x_1.acr + ALPHA * y_1.acr;
    acir = x.acir - x_1.acir + ALPHA * y_1.acir;
    
    x.acr = acr;
    x.acir = acir;
    return x;
}

oxy initOxy(void) {
    oxy temp;
    temp.spo2 = 0;
    temp.pouls = 0;

    return temp;

}
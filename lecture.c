#include "lecture.h"

//record1_bin.dat
absorp lecture(FILE* pf, int* etat) {
    absorp data = initAbsorp();
    //*etat = EOF;
    char trame[21] = {0};
    char caractere = 'c';
    int i;
    
    if (pf != NULL) {
        // On récupère chaque caractère
        for (i = 0; i < 21; i++) {
            caractere = fgetc(pf);
            if (caractere != EOF) {
                trame[i] = caractere;
            } else {
                *etat = EOF;
                return data;
            }
        }

        data.acr = ((trame[0] - 48) * 1000 + (trame[1] - 48) * 100 + (trame[2] - 48) * 10 + (trame[3] - 48)) - 2048;
        data.dcr = (trame[5] - 48) * 1000 + (trame[6] - 48) * 100 + (trame[7] - 48) * 10 + (trame[8] - 48); 
        data.acir = ((trame[10] - 48) * 1000 + (trame[11] - 48) * 100 + (trame[12] - 48) * 10 + (trame[13] - 48)) - 2048; 
        data.dcir = (trame[15] - 48) * 1000 + (trame[16] - 48) * 100 + (trame[17] - 48) * 10 + (trame[18] - 48); 

    } else {
        *etat = EOF;
    }


    return data;
}

// Liaison USB
absorp lectureUSB() {
    
}

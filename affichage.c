#include "affichage.h"

void affichage(oxy myOxy) {
    if (access(".verrouData", F_OK) != -1) {
        // no thing to do
    } else {
        // On crée le fichier verrouData
        fopen(".verrouData", "r");

        // On écrit dans le fichier Data.txt
        FILE* data = NULL;
        data = fopen("Data.txt", "w");
        
        if (data != NULL) {
            fprintf(data, "%d\n%d", myOxy.spo2, myOxy.pouls);
            fclose(data);
        }

        // On supprime le fichier
        remove(".verrouData");
    }

}
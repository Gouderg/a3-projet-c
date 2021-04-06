#include "affichage.h"

void affichage(oxy myOxy) {
    if (access(".verrouData", F_OK) != -1) {
        // return
    } else {
        // On crée le fichier
        FILE* fichier = NULL;
        fichier = fopen(".verrouData", "r");
        fclose(fichier);

        // On affiche

        // On supprime le fichier
        remove(".verrouData");
    }

}
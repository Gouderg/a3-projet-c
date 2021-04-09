/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: affichage.c                       - */
/* - Utilisation: fonctions liées à l'affichage - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */

#include "affichage.h"


/* ----------------------------------------------- */
/* - Nom: affichage                              - */
/* - Description: Écrit dans le fichier Data.txt - */
/* - Paramètre: oxy                              - */
/* - Return: void                                - */
/* ----------------------------------------------- */
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
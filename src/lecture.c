/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: lecture    .c                     - */
/* - Utilisation: fonctions liées à lecture     - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#include "../header/lecture.h"

/* ------------------------------------------------- */
/* - Nom: lecture                                  - */
/* - Description: Lis une trame valide dans        - */
/* -              un fichier et la renvoie         - */
/* - Paramètre: FILE*,  int*                       - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp lecture(FILE* pf, int* etat) {
    absorp data = initAbsorp();

    char trame[21] = {0};
    char caractere = 'c';
    int i = 0;
    
    // On vérifie si le fichier existe
    if (pf != NULL) {
        while (i < 21) {
            caractere = fgetc(pf);
            if (caractere == 0x0d && i != 20) { // Si le caractère est \r n'est pas placé au bonne endroit on remet i à -1
                i = -1;
            } else if (caractere != EOF) {      // Si le caractère est celui de fin de fichier       
                trame[i] = caractere;
            } else {
                *etat = EOF;
                return data;
            }

            i += 1;
        }
        
        // On convertit les octets de la trame valide
        data.acr = ((trame[0] - 48) * 1000 + (trame[1] - 48) * 100 + (trame[2] - 48) * 10 + (trame[3] - 48)) - 2048;
        data.dcr = (trame[5] - 48) * 1000 + (trame[6] - 48) * 100 + (trame[7] - 48) * 10 + (trame[8] - 48); 
        data.acir = ((trame[10] - 48) * 1000 + (trame[11] - 48) * 100 + (trame[12] - 48) * 10 + (trame[13] - 48)) - 2048; 
        data.dcir = (trame[15] - 48) * 1000 + (trame[16] - 48) * 100 + (trame[17] - 48) * 10 + (trame[18] - 48); 
        return data;

    } else {
        *etat = EOF;
        return data;
    }
}


/* ------------------------------------------------- */
/* - Nom: openUSB                                  - */
/* - Description: Ouvre une connexion USB          - */
/* - Paramètre: FT_HANDLE* FT_STATUS*              - */
/* - Return: FT_HANDLE                             - */
/* ------------------------------------------------- */
FT_HANDLE openUSB(FT_HANDLE ftHandle, FT_STATUS* ftStatus) {
    *ftStatus = FT_Open(0, &ftHandle);
    if(*ftStatus != FT_OK) {
        printf("Failed to connect - may be disconnect ! \n");
    }

    return ftHandle;
}


/* ------------------------------------------------- */
/* - Nom: lectureUSB                               - */
/* - Description: Lis une trame valide par         - */
/* -              connexion USB et la renvoie      - */
/* - Paramètre: FT_HANDLE* FT_STATUS*              - */
/* - Return: absorp                                - */
/* ------------------------------------------------- */
absorp lectureUSB(FT_HANDLE* ftHandle, FT_STATUS* ftStatus) {
    absorp data = initAbsorp();
    char trame[21] = {0};
    char caractere = 'c';
    int i = 0;
    DWORD BytesReceived, RxBytes = 1;
    // On vérifie si le fichier existe
    if (*ftStatus == FT_OK) {
        while (i < 21) {
            //printf("df\n");
            *ftStatus = FT_Read(*ftHandle, &caractere, RxBytes, &BytesReceived);
            //printf("%c\n", caractere);
            if (caractere == 0x0d && i != 20) { // Si le caractère est \r n'est pas placé au bonne endroit on remet i à -1
                i = -1;
            } else if (caractere != EOF) {      // Si le caractère est celui de fin de fichier       
                trame[i] = caractere;
            }
            i += 1;
        }
        
        // On convertit les octets de la trame valide
        data.acr = ((trame[0] - 48) * 1000 + (trame[1] - 48) * 100 + (trame[2] - 48) * 10 + (trame[3] - 48)) - 2048;
        data.dcr = (trame[5] - 48) * 1000 + (trame[6] - 48) * 100 + (trame[7] - 48) * 10 + (trame[8] - 48); 
        data.acir = ((trame[10] - 48) * 1000 + (trame[11] - 48) * 100 + (trame[12] - 48) * 10 + (trame[13] - 48)) - 2048; 
        data.dcir = (trame[15] - 48) * 1000 + (trame[16] - 48) * 100 + (trame[17] - 48) * 10 + (trame[18] - 48); 
        return data;

    }
    return data;
}

/* ------------------------------------------------- */
/* - Nom: closeUSB                                 - */
/* - Description: Ferme la connexion USB           - */
/* - Paramètre: FT_HANDLE*                         - */
/* - Return: void                                  - */
/* ------------------------------------------------- */
void closeUSB(FT_HANDLE* ftHandle) {
    FT_Close(*ftHandle);
}
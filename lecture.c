/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: lecture    .c                     - */
/* - Utilisation: fonctions liées à lecture     - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#include "lecture.h"

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
    int caractere = 'c';
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


/*
FT_HANDLE openUSB(FT_HANDLE ftHandle, FT_STATUS* ftStatus) {
    *ftStatus = FT_Open(0, &ftHandle);
    if(*ftStatus != FT_OK) {
        printf("Failed to connect - may be disconnect ! \n");
    }

    return ftHandle;
}


// Liaison USB
absorp lectureUSB(FT_HANDLE* ftHandle, FT_STATUS* ftStatus) {
    absorp data = initAbsorp();
    DWORD RxBytes = 21;
    DWORD BytesReceived;
    char RxBuffer[256];    

    int isOkey = 1;
    do {
        FT_SetTimeouts(*ftHandle, 2, 0); // Attente de 2ms
        *ftStatus = FT_Read(*ftHandle, RxBuffer, RxBytes, &BytesReceived);
        if (ftStatus == FT_OK) {
            if (BytesReceived == RxBytes) {

                printf("%s\n", RxBuffer);
                data.acr = ((RxBuffer[0] - 48) * 1000 + (RxBuffer[1] - 48) * 100 + (RxBuffer[2] - 48) * 10 + (RxBuffer[3] - 48)) - 2048;
                data.dcr = (RxBuffer[5] - 48) * 1000 + (RxBuffer[6] - 48) * 100 + (RxBuffer[7] - 48) * 10 + (RxBuffer[8] - 48); 
                data.acir = ((RxBuffer[10] - 48) * 1000 + (RxBuffer[11] - 48) * 100 + (RxBuffer[12] - 48) * 10 + (RxBuffer[13] - 48)) - 2048; 
                data.dcir = (RxBuffer[15] - 48) * 1000 + (RxBuffer[16] - 48) * 100 + (RxBuffer[17] - 48) * 10 + (RxBuffer[18] - 48); 
                isOkey = 0;
            } else {
                printf("Timeout bro ! \n");
                // FT_READ Timeout
            }
        } else {
            printf("READ error \n");
        }
    } while (isOkey);
    
    return data;
}


void closeUSB(FT_HANDLE* ftHandle) {
    FT_Close(*ftHandle);
}*/
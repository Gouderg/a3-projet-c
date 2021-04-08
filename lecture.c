#include "lecture.h"

//record1_bin.dat
absorp lecture(FILE* pf, int* etat) {
    absorp data = initAbsorp();

    char trame[21] = {0};
    int caractere = 'c';
    int i = 0;
    
    if (pf != NULL) {
        while (i < 21) {
            caractere = fgetc(pf);
            if (caractere == 0x0d && i != 20) {
                i = -1;
            } else if (caractere != EOF) {       
                trame[i] = caractere;
            } else {
                *etat = EOF;
                return data;
            }

            i += 1;
        }
        
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

// Liaison USB
absorp lectureUSB() {
    absorp data = initAbsorp();
    // FT_HANDLE ftHandle;
    // FT_STATUS ftStatus;
    // DWORD RxBytes = 21;
    // DWORD BytesReceived;
    // char RxBuffer[21];

    // ftStatus = FT_Open(0, &ftHandle);
    // if(ftStatus != FT_OK) {
    //     // FT_Open failed
    //     return data;
    // }

    // FT_SetTimeouts(ftHandle, 2, 0);
    // ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
    // if (ftStatus == FT_OK) {
    //     if (BytesReceived == RxBytes) {
    //         data.acr = ((RxBuffer[0] - 48) * 1000 + (RxBuffer[1] - 48) * 100 + (RxBuffer[2] - 48) * 10 + (RxBuffer[3] - 48)) - 2048;
    //         data.dcr = (RxBuffer[5] - 48) * 1000 + (RxBuffer[6] - 48) * 100 + (RxBuffer[7] - 48) * 10 + (RxBuffer[8] - 48); 
    //         data.acir = ((RxBuffer[10] - 48) * 1000 + (RxBuffer[11] - 48) * 100 + (RxBuffer[12] - 48) * 10 + (RxBuffer[13] - 48)) - 2048; 
    //         data.dcir = (RxBuffer[15] - 48) * 1000 + (RxBuffer[16] - 48) * 100 + (RxBuffer[17] - 48) * 10 + (RxBuffer[18] - 48); 
    //     } else {
    //         // FT_READ Timeout
    //     }
    // }

    // FT_Close(ftHandle);
    return data;
}

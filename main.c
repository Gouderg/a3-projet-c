// Inclusion des différentes fonctions
#include "define.h"
#include "iir.h"
#include "fir.h"
#include "mesure.h"
#include "integration.h"
#include "lecture.h"
#include "affichage.h"
#include "ftd2xx.h"


int main() {  
    // Si le fichier .verrouData existe on le supprime (prévention)
    if (access(".verrouData", F_OK) != -1) {
        remove(".verrouData");
    }

    /* Main qui devrait marché avec la carte*/
    //Initialisation des variables
    absorp data = initAbsorp();
    absorp y = initAbsorp();
    absorp x_1 = initAbsorp();
    oxy oxy = initOxy();
    periode myPeriode = initPeriode();
    ac_struct buffer[51] = {0};
    FT_STATUS ftStatus;

    FT_HANDLE ftHandle = openUSB(ftHandle, &ftStatus);



    if (ftStatus == FT_OK) {
        printf("ok\n");
        do {
            data = lectureUSB(&ftHandle, &ftStatus); // lecture de la ligne
            //printf("%f %f %f %f \n", data.acr, data.dcr, data.acir, data.dcir);
            if (ftStatus == FT_OK) {
                data = FIR(data, buffer); // Application du filtre FIR
                y = IIR(data, &x_1, y);    // Application du filtre IIR
                oxy = mesure(y, &myPeriode);    // On effectue la mesure
                affichage(oxy);
            }
            
        } while (ftStatus == FT_OK);
    }
    closeUSB(&ftHandle);


    /* Main qui marche avec lecture normale */
    // // Initialisation des variables
    // absorp data = initAbsorp();
    // absorp y = initAbsorp();
    // absorp x_1 = initAbsorp();
    // oxy oxy = initOxy();
    // periode myPeriode = initPeriode();
    // ac_struct buffer[51] = {0};
    // FILE* fichier = initFichier("record1_bin.dat");
    // int etat = 0;

    // if (fichier != NULL) {
    //     do {
    //         data = lecture(fichier, &etat); // lecture de la ligne
    //         //printf("%f %f %f %f \n", data.acr, data.dcr, data.acir, data.dcir);
    //         if (etat != EOF) {
    //             data = FIR(data, buffer); // Application du filtre FIR
    //             y = IIR(data, &x_1, y);    // Application du filtre IIR
    //             oxy = mesure(y, &myPeriode);    // On effectue la mesure
    //             affichage(oxy);
    //         }
            
    //     } while (etat != EOF);
    // }
    // finFichier(fichier);
    return EXIT_SUCCESS;
}

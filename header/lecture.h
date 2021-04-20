/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: lecture.h                         - */
/* - Utilisation: fichier d'entête de lecture   - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#ifndef LECTURE_H
#define LECTURE_H
#include "../header/define.h"
#include "../header/fir.h"
#include "../lib/ftd2xx.h"

absorp lecture(FILE* pf, int* etat);
FT_HANDLE openUSB(FT_HANDLE ftHandle, FT_STATUS* ftStatus);
absorp lectureUSB(FT_HANDLE* ftHandle, FT_STATUS* ftStatus);
void closeUSB(FT_HANDLE* ftHandle);


#endif
/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: mesure.h                          - */
/* - Utilisation: fichier d'entête de mesure    - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#ifndef MESURE_H
#define MESURE_H

#include "../header/define.h"
#include "../header/fichiers.h"

oxy mesureTest(char* test);
oxy mesure(absorp data, periode* perio);
periode initPeriode(void);

#endif
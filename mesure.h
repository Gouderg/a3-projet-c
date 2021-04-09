/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: mesure.h                          - */
/* - Utilisation: fichier d'entête de mesure    - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#ifndef MESURE_H
#define MESURE_H

#include "define.h"
#include "fichiers.h"

oxy mesureTest(char* test);
oxy mesure(absorp data, periode* perio);
periode initPeriode(void);

#endif
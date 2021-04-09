/* ---------------------------------------------- */
/* - Auteur: ILLIEN Victor                      - */
/* - Fichier: fir.h                             - */
/* - Utilisation: fichier d'entête de fir       - */
/* - Version: 1.0                               - */
/* ---------------------------------------------- */
#ifndef FIR_H
#define FIR_H

#include "stdio.h"
#include "stdlib.h"
#include "define.h"
#include "fichiers.h"
#include "string.h"

absorp firTest(char* filename);
absorp FIR(absorp data, ac_struct* buffer);
absorp initAbsorp(void);

#endif
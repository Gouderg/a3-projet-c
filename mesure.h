#ifndef MESURE_H
#define MESURE_H

#include "stdlib.h"
#include "stdio.h"

#include "define.h"
#include "fichiers.h"

oxy mesureTest(char* test);
oxy mesure(absorp data, periode* perio);
periode initPeriode(void);

#endif
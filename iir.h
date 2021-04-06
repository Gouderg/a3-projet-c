#ifndef IIR_H
#define IIR_H
#include "stdio.h"
#include "stdlib.h"
#include "define.h"
#include "fichiers.h"

#define ALPHA 0.992

absorp iirTest(char* str);
absorp IIR(absorp x, absorp x_1, absorp y_1);
oxy initOxy(void);

#endif
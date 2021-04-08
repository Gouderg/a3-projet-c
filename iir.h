#ifndef IIR_H
#define IIR_H
#include "define.h"
#include "fir.h"

#define ALPHA 0.992

absorp iirTest(char* filename);
absorp IIR(absorp x, absorp* x_1, absorp y_1);
oxy initOxy(void);

#endif
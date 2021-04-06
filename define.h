// #define ALPHA 0.992
#ifndef DEFINE_H
#define DEFINE_H

typedef struct {
    float acr;      // AC R
    float dcr;      // DC R
    float acir;     // AC IR
    float dcir;     // DC IR
} absorp;

typedef struct {
    int spo2;       // SP02
    int pouls;      // Pouls
} oxy;

typedef struct {
    oxy lastoxy;
    float acr_min, acir_min, acr_max, acir_max, lastValue; 
    long compteur_pouls;
} periode;

#endif
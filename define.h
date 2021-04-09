/* ------------------------------------------------------ */
/* - Auteur: ILLIEN Victor                              - */
/* - Fichier: define.h                                  - */
/* - Utilisation: Ensemble des structures du programme  - */
/* - Version: 1.0                                       - */
/* ------------------------------------------------------ */
#ifndef DEFINE_H
#define DEFINE_H

#include "stdio.h"
#include "stdlib.h"

// Structure contenant les valeurs envoyées par la carte
typedef struct {
    float acr, dcr, acir, dcir;
} absorp;

// Structure utilisé pour le buffer circulaire
typedef struct {
    float acr, acir;
} ac_struct;

// Structure utilisé pour stocké les valeurs de pouls et de sp02
typedef struct {
    int spo2, pouls;
} oxy;

// Structure utilisé pour conservé des valeurs lors de la mesure
typedef struct {
    oxy lastoxy;
    float acr_min, acir_min, acr_max, acir_max, lastValue; 
    long compteur_pouls;
} periode;

#endif
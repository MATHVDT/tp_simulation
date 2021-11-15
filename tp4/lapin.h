#ifndef LAPIN_H
#define LAPIN_H

#include "tp4.h"

enum Sexe
{
    male,
    femelle
};

typedef struct lapin
{
    int age; // Age en mois
    enum Sexe sexe;

} lapin_t;

lapin_t *creerLapin(enum Sexe inSexe);

int maturite(lapin_t *lapin);

#endif
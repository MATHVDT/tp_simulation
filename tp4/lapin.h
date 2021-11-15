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
    int ageMmaturite;

} lapin_t;

lapin_t *creerLapin(enum Sexe inSexe);

void initMaturite(lapin_t *lapin);
int maturite(lapin_t *lapin);

void mortLapin(lapin_t *lapin);

#endif
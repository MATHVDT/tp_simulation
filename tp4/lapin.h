#ifndef LAPIN_H
#define LAPIN_H

#include "tp4.h"

enum Sexe
{
    male,
    femelle
};

enum Maturite
{
    bebe,
    adulte
};

typedef struct lapin
{
    int age; // Age en mois
    enum Sexe sexe;
    int ageMaturite;
    enum Maturite maturite;

    // Pour les femelles
    int nbPortees;

} lapin_t;

lapin_t *creerLapin(enum Sexe inSexe);

void initMaturite(lapin_t *lapin);
int maturite(lapin_t *lapin);
int anniversaireLapin(lapin_t **p_lapin);

int mortLapin(lapin_t *lapin);

enum Sexe choixSexe();

int porteeLapin(lapin_t *femelle,
                lapin_t *male);

#endif
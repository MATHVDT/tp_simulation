
#include "lapin.h"

/*********************************************************/
/*  choixSexe : Donne le sexe male(50%) ou femelle(50%)  */
/*                                                       */
/*  Entree : rien                                        */
/*                                                       */
/*  Sortie : enum Sexe : male(50%) ou femelle(50%)       */
/*                                                       */
/*********************************************************/
enum Sexe choixSexe()
{
    return (genrand_real2() < 0.5 ? male : femelle);
}

/*********************************************************/
/* creerLapin : Cree un lapin du sexe donne en parametre */
/*              et initialise ses caracteristiques       */
/*                                                       */
/* Entree : le sexe du lapin                             */
/*                                                       */
/* Sortie  : l'adresse du lapin cree (malloc)            */
/*********************************************************/
lapin_t *creerLapin(enum Sexe inSexe)
{
    lapin_t *lapin = malloc(sizeof(lapin_t));
    if (lapin != NULL)
    {
        lapin->age = 0;
        lapin->sexe = inSexe;
        initMaturite(lapin);
        lapin->maturite = bebe;
    }
    else
    {
        printf("Erreur creation lapin\n");
    }
    return lapin;
}

/*********************************************************/
/*  initMaturite : fonction qui initialise aleatoirement */
/*                 l'age a partir duquel un lapin devient*/
/*                 mature (entre 4 et 8)                 */
/*                                                       */
/*  Entree : Un lapin                                    */
/*********************************************************/
void initMaturite(lapin_t *lapin)
{
    double random = genrand_real1();

    if (random < 0.25)
    {
        lapin->ageMaturite = 5;
    }
    else if (random < 0.50)
    {
        lapin->ageMaturite = 6;
    }
    else if (random < 0.75)
    {
        lapin->ageMaturite = 7;
    }
    else
    {
        lapin->ageMaturite = 8;
    }
}

/*********************************************************/
/*  maturite : fonction qui indique si un lapin est      */
/*              mature ou non                            */
/*                                                       */
/*  Entree : Un lapin                                    */
/*                                                       */
/*  Sortie : Un entier qui vaut 0 si le lapin n'est pas  */
/*           mature et 1 sinon                           */
/*********************************************************/
int maturite(lapin_t *lapin)
{
    // return lapin->age >= lapin->ageMaturite;
    return lapin->maturite == adulte;
}

/*********************************************************/
/*  anniversaireLapin : Ajoute 1 a l'age du lapin et     */
/*                      verifie s'il devient un adulte   */
/*                                                       */
/*  Entree : Un lapin                                    */
/*                                                       */
/*  Sortie : 0 si le lapin ne passe pas de bebe->adulte  */
/*           1 si le lapin devient un adulte             */
/*                                                       */
/*********************************************************/
int anniversaireLapin(lapin_t **p_lapin)
{
    int estDevenueAdulte = 0;
    (*p_lapin)->age++;

    // Verifie s'il devient un adulte
    if (!maturite(*p_lapin))
    { // Encore un bebe
        if ((*p_lapin)->age >= (*p_lapin)->ageMaturite)
        { // Devient un adulte
            (*p_lapin)->maturite = adulte;
            estDevenueAdulte = 1;
        }
    }
    // Toujours un bebe
    return estDevenueAdulte;
}

/*********************************************************/
/*  mortLapin : fonction qui determine si un lapin meurt */
/*              ce moi-ci                                */
/*                                                       */
/*  Entree : Un lapin                                    */
/*                                                       */
/*  Sortie : Un entier qui vaut 0 si le lapin vit, 1 si  */
/*           le lapin meurt, et -1 en cas d'erreur       */
/*           (age en annee hors de [| 0 ; 15 |])         */
/*********************************************************/
int mortLapin(lapin_t *lapin)
{
    // age année -> chance survie :
    // 10 ans -> 0.5 (an) / 0.94387 (mois)
    // 11 ans -> 0.4 (an) / 0.92648 (mois)
    // 12 ans -> 0.3 (an) / 0.90454 (mois)
    // 13 ans -> 0.2 (an) / 0.87449 (mois)
    // 14 ans -> 0.1 (an) / 0.82540 (mois)
    // 15 ans -> 0.0001 (an) / 0.46416 (mois)
    //
    // Age < 10 ans :
    // Adulte -> 0.6  (an) / 0.95832 (mois)
    // Bebe   -> 0.35 (an) / 0.91623 (mois)

    double random = genrand_real1();
    int mort = 0;

    // printf("random mort %lf\n", random);

    switch (lapin->age / 12)
    {
    case 10:
        if (random > 0.94387)
            mort = 1;
        break;
    case 11:
        if (random > 0.92648)
            mort = 1;
        break;
    case 12:
        if (random > 0.90454)
            mort = 1;
        break;
    case 13:
        if (random > 0.87449)
            mort = 1;
        break;
    case 14:
        if (random > 0.82540)
            mort = 1;
        break;
    case 15:
        // if (random > 0.46416)
        mort = 1;
        break;
    default:
        if ((!maturite(lapin) && random > 0.91623) ||
            (maturite(lapin) && random > 0.95832))
        {
            mort = 1;
        }
        else
        {
            mort = -1;
        }
    }

    // if (lapin->maturite == adulte)
    // {
    //     // mort = genrand_real2() < 0.95832 ? 0 : 1;
    //     mort = genrand_real2() < 0.95832 - lapin->age / 12 / 10 ? 0 : 1;
    // }
    // else
    // {
    //     // mort = genrand_real2() < 0.91513 ? 0 : 1;
    //     mort = genrand_real2() < 0.91513 ? 0 : 1;
    // }

    // printf("mort = %d\n", mort);
    return mort;
}

/*********************************************************/
/* porteeLapin : Donne le nb de bebe sur la portee      */
/*                suit une loi uniforme entre 3 et 6     */
/*                                                       */
/*  Entree : Un lapin male                               */
/*  Entree : Un lapin femelle                            */
/*                                                       */
/*  Sortie : le nb de de bebe de la portee               */
/*                                                       */
/*********************************************************/
int porteeLapin(lapin_t *femelle,
                lapin_t *male)
{
    int portee = uniform(3, 6);

    return portee;
}

/*********************************************************/
/* nbPorteesAnnee : Donne le nb de portees de l'annee    */
/*                  qui suit une loi N(6,1)              */
/*                                                       */
/*  Entree : rien                                        */
/*                                                       */
/*  Sortie : le nb de portee qui suit N(6,1)             */
/*                                                       */
/*********************************************************/
int nbPorteesAnneeLapin()
{
    return loiNormale(6, 1);
}

/*********************************************************/
/* porteesAnnee : Complete le calendrier de portee d'une */
/*                lapine, ie calcul le nb et les mois    */
/*                                                       */
/*  Entree : un lapin : femelle                          */
/*                                                       */
/*  Sortie : rien                                        */
/*                                                       */
/*********************************************************/
void porteesAnneeLapin(lapin_t **p_lapin)
{
    // Test si lapin femelle, noramlement tj oui
    if ((*p_lapin)->sexe == femelle)
    {
        int i, mois;

        // Calcule le nb de portees pour l'annee
        int nbPortee = nbPorteesAnneeLapin();
        (*p_lapin)->nbPortees = nbPortee;

        // Reset les mois ou les portees sont prevues
        for (i = 0; i < 12; i++)
        {
            (*p_lapin)->moisPortees[i] = 0;
        }

        // Definie les mois des portees pour l'annee
        while (nbPortee > 0)
        {
            mois = uniform(0, 11);
            if (!(*p_lapin)->moisPortees[mois])
            {
                // Planifie le mois
                (*p_lapin)->moisPortees[mois] = 1;
                nbPortee--;
            }
        }
    }
    else
    {
        printf("Euh..., je ne crois pas qu'un lapin male puisse avoir une portee ?\n");
    }
}

/*********************************************************/
/* checkMoisPortee : Check s'il le lapin a une portee    */
/*                   ce mois ci et decremente le nb de   */
/*                   portees restantes                   */
/*                                                       */
/*  Entree : un lapin : femelle                          */
/*                                                       */
/*  Sortie : 1 -> la lapine a une portee ce mois ci      */
/*           0 -> la lapine n'a pas de portee ce mois ci */
/*                                                       */
/*********************************************************/
int checkMoisPortee(lapin_t *lapin,
                    int nbMoisEcoulees)
{
    int mois = nbMoisEcoulees % 12; // Mois de l'annee
    int aUnePortee = 0;

    // Regarde s'il s'agit d'un mois de portee
    if (lapin->moisPortees[mois])
    {
        aUnePortee = 1;
        // Inutile, c'est si on voulait tenir a jour
        // le nb de portees restantes
        // (*p_lapin)->moisPortees[mois] = 0;
        // (*p_lapin)->nbPortees--;
    }
    return aUnePortee;
}
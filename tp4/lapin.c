
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
    // age année -> chance survie
    // 10 ans -> 0.5 (an) / 0.94387 (mois)
    // 11 ans -> 0.4 (an) / 0.92648 (mois)
    // 12 ans -> 0.3 (an) / 0.90454 (mois)
    // 13 ans -> 0.2 (an) / 0.87449 (mois)
    // 14 ans -> 0.1 (an) / 0.82540 (mois)
    // 15 ans -> 0.0001 (an) / 0.46416 (mois)
    //
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
/*  porteeLapin : Donne le nb de bebe sur la portee      */
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

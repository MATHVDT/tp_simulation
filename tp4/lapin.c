
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
int anniversaireLapin(lapin_t *lapin)
{
    int estDevenueAdulte = 0;
    lapin->age++;

    // Verifie s'il devient un adulte
    if (!maturite(lapin))
    { // Encore un bebe
        if (lapin->age >= lapin->ageMaturite)
        { // Devient un adulte
            lapin->maturite = adulte;
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
    long random = genrand_real1();
    int mort = 0;

    switch (lapin->age / 12)
    {
    case 10:
        if (random > 50)
            mort = 1;
        break;
    case 11:
        if (random > 40)
            mort = 1;
        break;
    case 12:
        if (random > 30)
            mort = 1;
        break;
    case 13:
        if (random > 20)
            mort = 1;
        break;
    case 14:
        if (random > 10)
            mort = 1;
        break;
    case 15:
        mort = 1;
        break;
    default:
        if ((maturite(lapin) && random > 35) || ((lapin->age >= 0) && (lapin->age < 10) && random > 60))
        {
            mort = 1;
        }
        else
        {
            mort = -1;
        }
    }
    return mort;
}


/*********************************************************/
/*  porteeLapin : Donne le nb de bebe sur la porte       */
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
    int portee = uniform(3,6);

    return portee;
}
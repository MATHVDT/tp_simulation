
#include "lapin.h"

// A DEPLACER DANS UN FICHIER LAPIN
/********************************************************/
/* creerLapin : Cree un lapin du sexe donne en parametre*/
/*              et initialise ses caracteristiques      */
/*                                                      */
/* Entree : le sexe du lapin                            */
/*                                                      */
/* Sortie  : l'adresse du lapin cree                    */
/********************************************************/
lapin_t *creerLapin(enum Sexe inSexe)
{
    lapin_t *lapin = malloc(sizeof(lapin_t));
    if (lapin != NULL)
    {
        lapin->age = 0;
        lapin->sexe = inSexe;
    }
    else
    {
        printf("Erreur creation lapin\n");
    }
    return lapin;
}
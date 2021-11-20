/* 
TP Simulation
Lab # 4a–A more realistic population growth 

VILLEDIEU DE TORCY Mathieu
ZZ2 F 2 G22
*/

#include "rabbit_simu.h"

population_t pop;
infoPop_t infoPop;

int main()
{

    // population_t *pop;
    // infoPop_t *infoPop;

    // Initialisation de la population
    initPopulation(pop, infoPop);

    printf("%d", infoPop.nbTotal);

    // affichagePop(infoPop);
    // actualisationPopMois(pop, infoPop);
    // affichagePop(infoPop);

    return 0;
}

/*********************************************************/
/* initPopulation : Initialise la population de lapin    */
/*                  avec un male et une femelle bebes    */
/*                  et met a jour les info sur la pop    */
/*                                                       */
/* Entree : population de lapins                         */
/*          info sur la  population de lapins            */
/*                                                       */
/* Sortie  : rien                                        */
/*********************************************************/
void initPopulation(population_t *pop, infoPop_t *infoPop)
{
    // Initialisation des espaces mémoires
    pop = malloc(sizeof(population_t));
    infoPop = malloc(sizeof(infoPop_t));

    if (pop == NULL)
        printf("Erreur d'allocation de pop\n");
    if (infoPop == NULL)
        printf("Erreur d'allocation de infoPop\n");

    // Initialisation information population
    infoPop->nbMale = 1;
    infoPop->nbMaleAdulte = 0;
    infoPop->nbMaleBebe = 1;

    infoPop->nbFemelle = 1;
    infoPop->nbFemelleAdulte = 0;
    infoPop->nbFemelleBebe = 1;

    infoPop->nbAdulte = 0;
    infoPop->nbBebe = 2;
    infoPop->nbTotal = 2;

    // Ajout de deux lapins initiaux
    pop->male[0] = creerLapin(male);
    pop->femelle[0] = creerLapin(femelle);
}

/*********************************************************/
/* actualisationPopMois : Calcul le nouveau etat de la   */
/*                        population de lapin du mois    */
/*                                                       */
/* Entree : population de lapins                         */
/*          info sur la  population de lapins            */
/*                                                       */
/* Sortie  : rien                                        */
/*********************************************************/
void actualisationPopMois(population_t *pop,
                          infoPop_t *infoPop)
{

    // Anniversaire
    // age de Maturite
    // Rerpoduction
    // Mort
    int indiceMale = 0;
    int indiceFemelle = 0;

    lapin_t *lapinMale;
    lapin_t *lapinFemelle;

    while (indiceMale < infoPop->nbMale &&
           indiceFemelle < infoPop->nbFemelle)
    {
        lapinMale = pop->male[indiceMale];
        lapinFemelle = pop->femelle[indiceFemelle];

        // Anniversaire des lapins
        anniversaire(infoPop, lapinMale);
        anniversaire(infoPop, lapinFemelle);

        // Verifier maturite
        // ... verifier dans anniversaire?

        // Reproduction
        if (maturite(lapinMale) && maturite(lapinFemelle))
        {
            // Reproduction du couple
            // ...
            reproduction(pop, infoPop,
                         lapinMale, lapinFemelle);

            // Passage au couple suivant
            indiceMale++;
            indiceFemelle++;
        }
        else // Un des deux lapins n'est pas mature
        {
            // Lapin encore un bebe
            // Passe au lapin suivant
            if (!maturite(lapinMale))
            {
                indiceMale++;
            }
            if (!maturite(lapinFemelle))
            {
                indiceFemelle++;
            }
        }

        // Mort des lapins
        checkMort(pop, infoPop,
                  lapinMale, indiceMale);
        checkMort(pop, infoPop,
                  lapinFemelle, indiceFemelle);
    }

    // Pour les lapins males restants
    while (indiceMale < infoPop->nbMale)
    {
        lapinMale = pop->male[indiceMale];
        anniversaire(infoPop, lapinMale);
        checkMort(pop, infoPop,
                  lapinMale, indiceMale);
    }

    // Pour les lapins femelles restantes
    while (indiceFemelle < infoPop->nbFemelle)
    {
        lapinFemelle = pop->femelle[indiceFemelle];
        anniversaire(infoPop, lapinFemelle);
        checkMort(pop, infoPop,
                  lapinFemelle, indiceFemelle);
    }
}

/*********************************************************/
/*  anniversaire : augemente l'age d'un lapin et tient   */
/*                 a jour les infos sur la population    */
/*                                                       */
/*  Entree : infoPop : info sur la population de lapin   */
/*           Un lapin                                    */
/*                                                       */
/*  Sortie : rien                                        */
/*                                                       */
/*********************************************************/
void anniversaire(infoPop_t *infoPop, lapin_t *lapin)
{
    int estDevenueAdulte = anniversaireLapin(lapin);
    infoPop->nbAdulte += estDevenueAdulte;
    infoPop->nbBebe -= estDevenueAdulte;
}

/*********************************************************/
/*  checkMort : Tue le lapin s'il doit mourir et garde a */
/*              jour les informations sur la population  */
/*                                                       */
/*  Entree : pop     : population de lapin               */
/*           infoPop : info sur la population de lapin   */
/*           Un lapin                                    */
/*           indice du lapin dans la liste de la pop     */
/*                                                       */
/*  Sortie : rien                                        */
/*                                                       */
/*********************************************************/
void checkMort(population_t *pop,
               infoPop_t *infoPop,
               lapin_t *lapin,
               int indiceLapin)
{
    int doitMourir = mortLapin(lapin);

    // Mise a jour des informations de la population
    if (doitMourir)
    {

        if (maturite(lapin))
        { // Adulte
            switch (lapin->sexe)
            {
            case male:
                infoPop->nbMale;
                infoPop->nbMaleAdulte;
            case femelle:
                infoPop->nbFemelle--;
                infoPop->nbFemelleAdulte--;
            default:
                infoPop->nbAdulte--;
                break;
            }
        }
        else
        { // Bebe
            switch (lapin->sexe)
            {
            case male:
                infoPop->nbMale;
                infoPop->nbMaleBebe;
            case femelle:
                infoPop->nbFemelle--;
                infoPop->nbFemelleBebe--;
            default:
                infoPop->nbBebe--;
                break;
            }
        }
        infoPop->nbTotal--;
    }

    // Suppression du lapin, recopie du dernier dedans
    switch (lapin->sexe)
    {
    case male:
        free(pop->male[indiceLapin]);
        pop->male[indiceLapin] = pop->male[infoPop->nbMale];
        break;
    case femelle:
        free(pop->femelle[indiceLapin]);
        pop->femelle[indiceLapin] = pop->femelle[infoPop->nbMale];
        break;
    }
}

/*********************************************************/
/* reproduction : Effectue la reproduction entre 2lapins */
/*                ie : cree la portee de lapin et les    */
/*                ajoute dans la population en tenant a  */
/*                a jour les infos sur la population     */
/*                                                       */
/*  Entree : pop     : population de lapin               */
/*           infoPop : info sur la population de lapin   */
/*           Un lapin male                               */
/*           Un lapin femelle                            */
/*                                                       */
/*  Sortie : rien                                        */
/*                                                       */
/*********************************************************/
void reproduction(population_t *pop,
                  infoPop_t *infoPop,
                  lapin_t *lapinMale,
                  lapin_t *lapinFemelle)
{

    // Verification maturite des lapins
    // Normalement deja verifier avant
    if (!maturite(lapinMale) || !maturite(lapinFemelle))
    {
        printf("Lapin non mature, on devrait pas entrer dans la focntion reproduction !\n");
    }

    // Donne le nombre de bebe pour la portee
    int nbBebesPortee = porteeLapin(lapinFemelle,
                                    lapinMale);
    // int nbBebesPortee = 3;
    lapin_t *lapinBebe;
    enum Sexe sexeLapinBebe;

    // Creation de la portee de lapin
    // Et maintient a jour des infos sur la pop
    for (int k = 0; k < nbBebesPortee; k++)
    {
        sexeLapinBebe = choixSexe();
        lapinBebe = creerLapin(sexeLapinBebe);

        switch (sexeLapinBebe)
        {
        case male:
            pop->male[infoPop->nbMale] = lapinBebe;
            infoPop->nbMale++;
            infoPop->nbMaleBebe++;
        case femelle:
            pop->femelle[infoPop->nbFemelle] = lapinBebe;
            infoPop->nbFemelle++;
            infoPop->nbFemelleBebe++;
        default:
            infoPop->nbBebe++;
            infoPop->nbTotal++;
            break;
        }
    }
}

void affichagePop(infoPop_t *infoPop)
{
    printf("\n nbMale : %d", infoPop->nbMale);
    printf("\n nbMaleAdulte : %d", infoPop->nbMaleAdulte);
    printf("\n nbMaleBebe : %d", infoPop->nbMaleBebe);

    printf("\n");

    printf("\n nbFemelle : %d", infoPop->nbFemelle);
    printf("\n nbFemelleAdulte : %d", infoPop->nbFemelleAdulte);
    printf("\n nbFemelleBebe : %d", infoPop->nbFemelleBebe);

    printf("\n nbAdulte : %d", infoPop->nbAdulte);
    printf("\n nbBebe : %d", infoPop->nbBebe);
    printf("\n nbTotal : %d", infoPop->nbTotal);

    printf("\n");
}
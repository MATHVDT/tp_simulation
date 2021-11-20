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
    init_mt();

    int nbAnnees = 10;
    int nbMois = 12 * nbAnnees;
    int i, nbMoisEcoules = 0;
    // Initialisation de la population
    initPopulation();

    affichagePop();
    for (i = 1; i < nbMois; i++)
    {
        // nbMoisEcoules++;
        // printf("\nMois i = %d\n", i);
        actualisationPopMois(i);
        if (infoPop.nbTotal == 0 || infoPop.nbFemelle == 0 || infoPop.nbMale == 0)
        {
            printf("\nMois d'extinction %d \n", i);
            break;
        }
    }
    affichagePop();

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
void initPopulation()
{
    // Initialisation des espaces mémoires
    // pop = malloc(sizeof(population_t));
    // infoPop = malloc(sizeof(infoPop_t));

    // if (pop == NULL)
    //     printf("Erreur d'allocation de pop\n");
    // if (infoPop == NULL)
    //     printf("Erreur d'allocation de infoPop\n");

    // Initialisation information population
    infoPop.nbMale = 1;
    infoPop.nbMaleAdulte = 0;
    infoPop.nbMaleBebe = 1;

    infoPop.nbFemelle = 1;
    infoPop.nbFemelleAdulte = 0;
    infoPop.nbFemelleBebe = 1;

    infoPop.nbAdulte = 0;
    infoPop.nbBebe = 2;
    infoPop.nbTotal = 2;

    // Ajout de deux lapins initiaux
    pop.male[0] = creerLapin(male);
    pop.femelle[0] = creerLapin(femelle);
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
void actualisationPopMois(int nbMoisEcoules)
{

    int indiceMale = 0;
    int indiceFemelle = 0;

    lapin_t *lapinMale;
    lapin_t *lapinFemelle;

    while (indiceMale < infoPop.nbMale &&
           indiceFemelle < infoPop.nbFemelle)
    {
        lapinMale = pop.male[indiceMale];
        lapinFemelle = pop.femelle[indiceFemelle];

        // Anniversaire des lapins
        anniversaire(&lapinMale);
        anniversaire(&lapinFemelle);

        // Reproduction
        if (maturite(lapinMale) && maturite(lapinFemelle))
        {
            // Reproduction du couple
            reproduction(lapinMale, lapinFemelle);

            // Mort des lapins
            if (nbMoisEcoules > PROTECTION_JEUNE_POP)
            {
                checkMort(&lapinMale, indiceMale);
                checkMort(&lapinFemelle, indiceFemelle);
            }

            // Passage au couple suivant
            indiceMale++;
            indiceFemelle++;
        }
        else // Un des deux lapins n'est pas mature
        {
            // Mort des lapins
            if (nbMoisEcoules > PROTECTION_JEUNE_POP)
            {
                checkMort(&lapinMale, indiceMale);
                checkMort(&lapinFemelle, indiceFemelle);
            }
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
    }

    // Pour les lapins males restants
    while (indiceMale < infoPop.nbMale)
    {
        lapinMale = pop.male[indiceMale];
        anniversaire(&lapinMale);
        if (nbMoisEcoules > PROTECTION_JEUNE_POP)
        {
            checkMort(&lapinMale, indiceMale);
        }
        indiceMale++;
    }

    // Pour les lapins femelles restantes
    while (indiceFemelle < infoPop.nbFemelle)
    {
        lapinFemelle = pop.femelle[indiceFemelle];
        anniversaire(&lapinFemelle);
        if (nbMoisEcoules > PROTECTION_JEUNE_POP)
        {
            checkMort(&lapinFemelle, indiceFemelle);
        }
        indiceFemelle++;
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
void anniversaire(lapin_t **p_lapin)
{
    int estDevenueAdulte = anniversaireLapin(p_lapin);

    if (estDevenueAdulte)
    {
        // printf("Anniversaire d'une lapin\n");
        switch ((*p_lapin)->sexe)
        {
        case male:
            infoPop.nbMaleBebe--;
            infoPop.nbMaleAdulte++;
            break;
        case femelle:
            infoPop.nbFemelleBebe--;
            infoPop.nbFemelleAdulte++;
            break;
        }
        infoPop.nbBebe--;
        infoPop.nbAdulte++;
    }
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
void checkMort(lapin_t **p_lapin,
               int indiceLapin)
{
    int doitMourir;
    doitMourir = mortLapin(*p_lapin);

    // intervention divine pour sauver le lapin
    // doitMourir = 0;

    if (doitMourir == 1)
    {
        // printf("Un lapin doit mourrir\n");
        // Mise a jour des informations de la population
        if (maturite(*p_lapin))
        { // Adulte
            switch ((*p_lapin)->sexe)
            {
            case male:
                infoPop.nbMale--;
                infoPop.nbMaleAdulte--;
                break;
            case femelle:
                infoPop.nbFemelle--;
                infoPop.nbFemelleAdulte--;
                break;
            }
            infoPop.nbAdulte--;
        }
        else
        { // Bebe
            switch ((*p_lapin)->sexe)
            {
            case male:
                infoPop.nbMale--;
                infoPop.nbMaleBebe--;
                break;
            case femelle:
                infoPop.nbFemelle--;
                infoPop.nbFemelleBebe--;
                break;
            }
            infoPop.nbBebe--;
        }
        infoPop.nbTotal--;

        // Suppression du lapin, recopie du dernier dedans
        switch ((*p_lapin)->sexe)
        {
        case male:
            free(pop.male[indiceLapin]);
            pop.male[indiceLapin] = pop.male[infoPop.nbMale];
            break;
        case femelle:
            free(pop.femelle[indiceLapin]);
            pop.femelle[indiceLapin] = pop.femelle[infoPop.nbFemelle];
            break;
        default:
            printf("gujrsdgjrdgorhgo\n");
            break;
        }
    }
    else
    { // Doit pas mourir
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
void reproduction(lapin_t *lapinMale,
                  lapin_t *lapinFemelle)
{

    // Verification maturite des lapins
    // Normalement deja verifier avant
    if (!maturite(lapinMale) || !maturite(lapinFemelle))
    {
        // printf("Lapin non mature, on devrait pas entrer dans la focntion reproduction !\n");
    }

    // Donne le nombre de bebe pour la portee
    int nbBebesPortee = porteeLapin(lapinFemelle,
                                    lapinMale);
    // int nbBebesPortee = 3;

    // printf("La taille de la portee est de %d\n",nbBebesPortee);

    lapin_t *lapinBebe;
    enum Sexe sexeLapinBebe;

    // Creation de la portee de lapin
    // Et maintient a jour des infos sur la pop
    for (int k = 0; k < nbBebesPortee; k++)
    {
        sexeLapinBebe = choixSexe();
        lapinBebe = creerLapin(sexeLapinBebe);

        if (lapinBebe != NULL)
        {
            switch (sexeLapinBebe)
            {
            case male:
                pop.male[infoPop.nbMale] = lapinBebe;
                infoPop.nbMale++;
                infoPop.nbMaleBebe++;
                break;
            case femelle:
                pop.femelle[infoPop.nbFemelle] = lapinBebe;
                infoPop.nbFemelle++;
                infoPop.nbFemelleBebe++;
                break;
            }
            infoPop.nbBebe++;
            infoPop.nbTotal++;
            if (infoPop.nbMale + 10 >= POPULATION_MAX)
            {
                printf("\nPopulation de MALE trop grande pas assez de place dans le tableau\n");
            }
            if (infoPop.nbFemelle + 10 >= POPULATION_MAX)
            {
                printf("\nPopulation de FEMELLE trop grande pas assez de place dans le tableau\n");
            }
        }
        else
        {
            printf("Erreur d'allocation\n");
        }
    }
}

void affichagePop()
{
    printf("\n Affichage etat de la population\n");

    printf("\n nbMale : %d", infoPop.nbMale);
    printf("\n nbMaleAdulte : %d", infoPop.nbMaleAdulte);
    printf("\n nbMaleBebe : %d", infoPop.nbMaleBebe);

    printf("\n");

    printf("\n nbFemelle : %d", infoPop.nbFemelle);
    printf("\n nbFemelleAdulte : %d", infoPop.nbFemelleAdulte);
    printf("\n nbFemelleBebe : %d", infoPop.nbFemelleBebe);

    printf("\n");

    printf("\n nbAdulte : %d", infoPop.nbAdulte);
    printf("\n nbBebe : %d", infoPop.nbBebe);
    printf("\n nbTotal : %d", infoPop.nbTotal);

    printf("\n");
}
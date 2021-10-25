/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

static unsigned long mt[N]; /* the array for the state vector  */
static int mti = N + 1;     /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
void init_genrand(unsigned long s)
{
    mt[0] = s & 0xffffffffUL;
    for (mti = 1; mti < N; mti++)
    {
        mt[mti] =
            (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
void init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    init_genrand(19650218UL);
    i = 1;
    j = 0;
    k = (N > key_length ? N : key_length);
    for (; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1664525UL)) + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL;                                                             /* for WORDSIZE > 32 machines */
        i++;
        j++;
        if (i >= N)
        {
            mt[0] = mt[N - 1];
            i = 1;
        }
        if (j >= key_length)
            j = 0;
    }
    for (k = N - 1; k; k--)
    {
        mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * 1566083941UL)) - i; /* non linear */
        mt[i] &= 0xffffffffUL;                                                  /* for WORDSIZE > 32 machines */
        i++;
        if (i >= N)
        {
            mt[0] = mt[N - 1];
            i = 1;
        }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N)
    { /* generate N words at one time */
        int kk;

        if (mti == N + 1)         /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

        for (kk = 0; kk < N - M; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (; kk < N - 1; kk++)
        {
            y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
            mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
        mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,0x7fffffff]-interval */
long genrand_int31(void)
{
    return (long)(genrand_int32() >> 1);
}

/* generates a random number on [0,1]-real-interval */
double genrand_real1(void)
{
    return genrand_int32() * (1.0 / 4294967295.0);
    /* divided by 2^32-1 */
}

/* generates a random number on [0,1)-real-interval */
double genrand_real2(void)
{
    return genrand_int32() * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on (0,1)-real-interval */
double genrand_real3(void)
{
    return (((double)genrand_int32()) + 0.5) * (1.0 / 4294967296.0);
    /* divided by 2^32 */
}

/* generates a random number on [0,1) with 53-bit resolution*/
double genrand_res53(void)
{
    unsigned long a = genrand_int32() >> 5, b = genrand_int32() >> 6;
    return (a * 67108864.0 + b) * (1.0 / 9007199254740992.0);
}
/* These real versions are due to Isaku Wada, 2002/01/09 added */

/***************** Debut question 2 ******************************/

/* -------------------------------------------------------------- */
/* uniform : retourne un nombre aléatoire entre deux réels a et b */
/*                                                                */
/* Entrée : deux réels a et b                                     */
/* Sortie : un nombre aléatoire entre a et b                      */
/* -------------------------------------------------------------- */
double uniform(double a, double b)
{
    double rand = genrand_real2();
    return a + (b - a) * rand;
}

/* -------------------------------------------------------------- */
/* test_uniform : test differentes valeurs pour n de tirage       */
/*                de la fct uniform(a, b)                         */
/* Entrée : deux réels a et b                                     */
/* Sortie : un nombre aléatoire entre a et b                      */
/* -------------------------------------------------------------- */
void test_uniform(float a, float b)
{
    int n = 1000000; //Nombre de tirage
    float temp[n];   //Tableau stockant les differentes valeurs
    float moyenne = 0;

    float val = uniform(a, b);
    temp[0] = val;

    float max = val;
    float min = val;

    for (int i = 1; i < n; i++)
    {
        val = uniform(a, b);
        temp[i] = val;
        moyenne += val;
        if (val > max)
            max = val;
        if (val < min)
            val = min;
    }
    moyenne /= n;

    printf("\nPour %d tirage sur une loi uniforme entre %.2f et %.2f\n", n, a, b);
    printf("moyenne = %.2f, vrai moyenne (%.2f + %.2f)/2 = %.2f\n", moyenne, a, b, (a + b) / 2);
    printf("max = %.2f\n", max);
    printf("min = %.2f\n", min);
    printf("\n");
}
/******************* Fin question 2 ******************************/

/***************** Debut question 3 ******************************/

/* -------------------------------------------------------------- */
/* discrete_distribution : cree un distribution discrete 3classes */
/*                         avec P(A)=0.5; P(B)=0.1; P(C)=0.4      */
/* Entrée : entier n -> nb drawings                               */
/* Sortie : rien                                                  */
/* -------------------------------------------------------------- */
void discrete_distribution(int n)
{
    double rand;
    int i;

    int population[3];
    float proba[3];

    //Initialise les differentes population a 0
    for (i = 0; i < 3; i++)
    {
        population[i] = 0;
    }

    for (i = 0; i < n; ++i)
    {
        rand = genrand_real2();

        if (rand < 0.5) //Appartient a la classe A
        {
            population[0]++;
        }
        else
        {
            if (rand < 0.6) // Appartient a la classe B
            {
                population[1]++;
            }
            else //Appartient a la classe C
            {
                population[2]++;
            }
        }
    }

    printf("\nn = %d drawings\n", n);
    for (i = 0; i < 3; i++)
    {
        proba[i] = (float)population[i] / (float)n;
        printf("population %d = %d et frequence = %f\n", i, population[i], proba[i]);
    }
}

//Calcul et affiche la proba et proba_cumulee croissante d'une distribution
void tab_observation(int taille, int observation[taille])
{
    int i;
    int nb_observation = 0;
    float proba[taille];
    float proba_cumul[taille];

    for (i = 0; i < taille; i++)
    {
        nb_observation += observation[i];
    }
    for (i = 0; i < taille; i++)
    {
        proba[i] = (float)observation[i] / (float)nb_observation;
        proba_cumul[i] = proba[i];
        if (i != 0)
            proba_cumul[i] += proba_cumul[i - 1];
    }

    printf("\nIl y a %d observation.\n", nb_observation);
    for (i = 0; i < taille; i++)
    {
        printf("proba[i]=%.3f et ", proba[i]);
        printf("proba_cumul[i]=%.3f\n", proba_cumul[i]);
    }
}
/******************* Fin question 3 ******************************/

/***************** Debut question 4 ******************************/
//Trace un histogramme
/* --------------------------------------------------------------------- */
/* trace_histo :  affiche un histogramme d'un tableau de valeurs         */
/*                                                                       */
/* Entrée :   un tableau d'entier                                        */
/*            un entier : taille du tableau                              */
/*            un entier : precision de l'unite de l'histo                */
/* Sortie : rien                                                         */
/* --------------------------------------------------------------------- */
void trace_histo(int bin[], int nb_bin, int precision)
{
    printf("histogramme\n");
    printf("unite/valeurs quantite*precision");
    int quantite;
    int tot = 0;

    for (int i = 0; i < nb_bin; i++)
    {
        //Affiche l'axe des unites/valeurs
        //printf("\n[%2d..%2d] ", i, i + 1); //exponentiel negative
        //printf("\n%3d ", i);                 //somme lance de 20 des
        printf("\n[%+.1f..%+.1f] ", (float)i / 10. - 1.0,
                                    (float)i / 10. - 0.9); //Box Muller

        quantite = bin[i] / precision;

        printf("%3d*%d ", quantite, precision);

        for (int j = 0; j < quantite; j++)
        {
            printf("■");
        }
    }
    printf("\n");
}

/* -------------------------------------------------------------- */
/* negExp :  f^(-1) d'une loi exponentielle négative uniforme     */
/*                                                                */
/* Entrée : un real : moyenne                                     */
/* Sortie : un nb généré aléatoirement suivant                    */
/*          une loi exp negative                                  */
/* -------------------------------------------------------------- */
double negExp(double mean)
{
    double rand = genrand_real2();
    double tmp = 1. - rand;
    return (-mean * log(tmp));
}

/* -------------------------------------------------------------- */
/* testnegExp :  test negExp en affichant un histo                */
/*                                                                */
/* Entrée : un real : mean                                        */
/*          un entier n : nombre de tirage                        */
/*          un entier precision_histo                             */
/* Sortie : rien                                                  */
/* -------------------------------------------------------------- */
void test_negExp(double mean, int n, int precision_histo)
{
    double average = 0.;
    double tirage;
    int bin[20]; // tableau comptant les valeurs entre un certain intervalle

    //Initialisation du tableau
    for (int k = 0; k < 20; k++)
        bin[k] = 0;

    for (int i = 0; i < n; ++i)
    {
        tirage = negExp(mean);
        average += tirage;
        if (tirage > 20.)
        {
            bin[19]++;
        }
        else
            bin[(int)tirage]++;
    }
    average /= n;

    printf("\n\nnegExp(%.3f) -> moyenne calculee est : %.3f pour %d tirages\n", mean, average, n);
    trace_histo(bin, 20, precision_histo);
}

/******************* Fin question 4 ******************************/

/******************* Debut question 5 ****************************/

/************** Somme de 20 lances de des ***********************/

/* -------------------------------------------------------------- */
/* dice_6 :  genere un nb aleatoire uniforme entre 1 et 6         */
/*                                                                */
/* Entrée : rien                                                  */
/*                                                                */
/* Sortie : un entier : nb aleatoire uniforme entre 1 et 6        */
/* -------------------------------------------------------------- */
int dice_6()
{
    double rand = uniform(1, 7);
    return (int)rand;
}


/* -------------------------------------------------------------- */
/* dice_sum :  somme du resultat de m lance de des                */
/*                                                                */
/* Entrée : un entier : nombre de lance de de                     */
/*                                                                */
/* Sortie : un entier : somme du resultat de m lance de des       */
/* -------------------------------------------------------------- */
int dice_sum(int m)
{
    int dice = 0;

    for (int i = 0; i < m; ++i)
    {
        dice += dice_6();
    }
    return dice;
}

//repete n fois l'experience de m lances de de avec somme du resultat
/* -------------------------------------------------------------- */
/* repeat_sum_dice :  repete plusieur fois la somme du res de des */
/*                    trace l'histogramme des occurrences         */
/*                    et calcul la moyenne                        */
/*                                                                */
/* Entrée : un entier n : nombre d'iteration de l'experience      */
/*          un entier histo_precision : precision pour histo      */
/*          un entier m : nombre de lance de des pour la somme    */
/*                                                                */
/* Sortie : rien                                                  */
/* -------------------------------------------------------------- */
void repeat_sum_dice(int n, int histo_precision, int m)
{
    int score_max = m * 6;     // Valeur maximale de score possible
    int score[score_max + 1];  // Tableau comptant les occurences des scores
    int moyenne = 0;           // Moyenne
    
    // Initialisation du tableau des occurences
    for (int k = 0; k < score_max + 1; k++)
    {
        score[k] = 0;
    }

    int res_sum = 0;

    // Effecture n fois la somme du resultat de m lance de des
    for (int i = 0; i < n; ++i)
    {
        res_sum = dice_sum(m);
        score[res_sum]++;
        moyenne += res_sum;
    }

    moyenne /= n;

    printf("\nSomme de m = %d des et n = %d iteretions", m, n);
    printf("\nmoyenne calculee = %d\n", moyenne);
    trace_histo(score, score_max + 1, histo_precision);
}

/************** Box muller ***********************/
/* -------------------------------------------------------------- */
/* box_muller :  methode de box et muller                         */
/*                                                                */
/* Entrée : un entier n : nombre d'iteration de l'experience      */
/*          un entier histo_precision : precision pour histo      */
/*                                                                */
/* Sortie : 2 entier x1 et x2 suivant N(0,1)                      */
/* -------------------------------------------------------------- */
void box_muller(int n, int histo_precision)
{
    double rn1, rn2;
    double x1, x2;

    //Initialisation tableau de compteur
    int test20bin[20];
    for (int i = 0; i < 20; ++i)
    {
        test20bin[i] = 0;
    }

    for (int k = 0; k < n; k++)
    {
        //Calcul nombre aleatoire suivant une gaussienne N(0,1)
        rn1 = genrand_real2();
        rn2 = genrand_real2();
        x1 = cos(2 * M_PI * rn2) * sqrt(-2 * log(rn1));
        x2 = sin(2 * M_PI * rn2) * sqrt(-2 * log(rn1));

        //Comptabilise les valeurs entre -1 et 1
        if (x1 > -1 && x1 < 1)
            test20bin[(int)((x1 + 1) * 10)]++;
        if (x2 > -1 && x2 < 1)
            test20bin[(int)((x2 + 1) * 10)]++;
    }
    printf("Box and Muller : N(0,1) \n");
    printf("Avec %d tirages et une precision de %d -> ", n, histo_precision);
    trace_histo(test20bin, 20, histo_precision);
}

/******************* Fin question 5 ******************************/

int main(void)
{
/*
    int i;
    // Test pour comparaison avec fichier .out
    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(init, length);
    printf("1000 outputs of genrand_int32()\n");
    for (i=0; i<1000; i++) {
      printf("%10lu ", genrand_int32());
      if (i%5==4) printf("\n");
    }
    printf("\n1000 outputs of genrand_real2()\n");
    for (i=0; i<1000; i++) {
      printf("%10.8f ", genrand_real2());
      if (i%5==4) printf("\n");
    }
*/
/*
    double a = -89.2;
    double b = 56.7;
    printf("Generate pseudo-random numbers between %3.2f and %3.2f : %3.2f \n", a, b, uniform(a, b));
    test_uniform(a, b);


    discrete_distribution(1000);
    discrete_distribution(1000000);

    int tab[3] = {500, 100, 400};
    tab_observation(3, tab);
*/
/*
    printf("\n");

    test_negExp(10, 1000, 10);
    test_negExp(10, 1000000, 1000);
*/
/*
    printf("\n");

    repeat_sum_dice(1000000, 1000, 20);

    printf("\n");
*/

    box_muller(1000000, 1000);

    return 0;
}

/*
gcc mt19937ar.c -o prog -lm
*/
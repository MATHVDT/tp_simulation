#include <stdio.h>
#include <stdlib.h>

/*
gcc tp1.c  -o ./tp1 ; ./prog
*/

void middle_square_tech(int seed)
{

    int valeur = seed;
    int carre;

    int N = 120;

    for (int i = 0; i < N; i++)
    {
        carre = valeur * valeur;
        printf("iteration %d\n", i);
        printf("%04d\n", valeur);
        printf("%08d\n", carre);
        printf("\n");

        valeur = carre / 100;
        valeur = valeur % 10000;
    }
}

void coin_tossing()
{
    int pile = 0;
    int face = 0;
    int jet;

    int N = 10000;
    for (int i = 0; i < N; i++)
    {
        jet = rand();
        if (jet < RAND_MAX / 2)
            pile++;
        else
            face++;
    }

    printf("Pour %d iteration\n", N);
    printf("pile %d | face %d\n", pile, face);
}

void regular_dice_simulation()
{
    int jet;
    int distribution[6];

    for (int k = 0; k < 6; k++)
        distribution[k] = 0;

    int N = 1000000;
    for (int i = 0; i < N; i++)
    {
        jet = rand();
        if (jet < (RAND_MAX / 6))
            distribution[0]++;
        else if (jet < 2 * (RAND_MAX / 6))
            distribution[1]++;
        else if (jet < 3 * (RAND_MAX / 6))
            distribution[2]++;
        else if (jet < 4 * (RAND_MAX / 6))
            distribution[3]++;
        else if (jet < 5 * (RAND_MAX / 6))
            distribution[4]++;
        else if (jet < 6 * (RAND_MAX / 6))
            distribution[5]++;
    }

    printf("valeur optimale : %d\n", N / 6);
    for (int j = 0; j < 6; j++)
        printf("%d | ", distribution[j]);
}

void dice10_simulation()
{

    int jet;
    int distribution[10];

    for (int k = 0; k < 10; k++)
        distribution[k] = 0;

    int N = 100000000;
    for (int i = 0; i < N; i++)
    {
        jet = rand();
        distribution[jet % 10]++;
    }

    printf("valeur optimale : %d\n", N / 10);
    for (int j = 0; j < 10; j++)
        printf("%d | ", distribution[j]);
}

int LCG(int a, int c, int m, int x)
{
    return (a * x + c) % m;
}

static int x_static = 5;
int intRand()
{
    x_static = (5 * x_static + 1) % 16;
    return x_static;
}


float floatRand()
{
    x_static = (5 * x_static + 1) % 16;
    return (((float)x_static) / 16.);
}

void LCG_simulation(int x0)
{

    int x;
    float x_dec;

    int N = 32;
    for (int i = 0; i < N; i++)
    {
        //x = LCG(a, c, m, x);
        //x = intRand();
        //printf("%d, ", x);
        x_dec = floatRand();
        printf("%.4f, ", x_dec);
    }
    printf("\n");
}

int main()
{
    int n0 = 2141;
    //middle_square_tech(n0);
    //coin_tossing();
    //regular_dice_simulation();
    //dice10_simulation();
    LCG_simulation(5);
}

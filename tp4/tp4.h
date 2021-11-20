#ifndef TP_3_H
#define TP_3_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
gcc tp4.c -o prog -lm
option -O2  pour optimiser 
*/
/*
./prog > res.txt ; diff res.txt mt19937ar.out ; echo $?
*/

// Fonction generateur MT
void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
long genrand_int31(void);
double genrand_real1(void);
double genrand_real2(void);
double genrand_real3(void);
double genrand_res53(void);

int init_mt();
int test_mt(void);

// Generation de loi aleatoire

double uniform(double a, double b);
double negExp(double mean);
int box_muller();
int loiNormale(int mu, int sigma);

// Mes fonction tp4
long fibo_rec(int n);
long fibo_rec_terminale(int n, long u_n, long u_n_1);

#endif
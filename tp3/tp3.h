#ifndef TP_3_H
#define TP_3_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
gcc tp3.c -o prog -lm
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

// Mes fonction tp3
double simPi(int n);
void mean_simPi(int nb_launch, int nb_point);



#endif
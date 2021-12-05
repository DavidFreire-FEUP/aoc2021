#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BITS 5
//#define BITS 12

int bin2dec(long int bin){
    int dec=0;
    long int aux = bin;

    for (size_t i = 0; aux>0; i++)
    {
        //printf("%d\n",aux%10);
        dec+=aux%10<<i;
        aux=aux/10;
    }

    return dec;
}

int bitAt(long int bits, int pos){
    long int aux = bits;
    for (size_t i = pos; i > 0; i--)
    {
        aux = aux/10;
    }
    
    int dec = aux%10;
    return dec;
}


void part2()
{
   FILE *f;

    f = fopen("input.txt","r");

    long int bits;
    int comm[2][BITS]={0};
    int oxygen,diox;
    long int andoxy = 0,anddiox=0;


    while (fscanf(f,"%ld",&bits)!=EOF)
    {   
        for (size_t i = 0; i < BITS; i++)
        {
            comm[bits%10][i]++;
            bits = bits/10;
        }
    }

    int countoxy,countdiox;
    int oxy,dio;
    
    for (size_t i = BITS-1; i > 0; i--)
    {
        rewind(f);

        if(comm[1][BITS-1-i] >= comm[0][BITS-1-i]) andoxy+=pow(10,i);
        if(comm[0][BITS-1-i] > comm[1][BITS-1-i]) anddiox+=pow(10,i);

        countoxy=0; countdiox=0;
        while (fscanf(f,"%ld",&bits)!=EOF)
        {   
            if((bin2dec(bits) & bin2dec(andoxy)) == bin2dec(bits)){
                oxy=bin2dec(bits);
                countoxy++;
            }

            if((bin2dec(bits) & bin2dec(anddiox)) == bin2dec(bits)){
                dio=bin2dec(bits);
                countdiox++;
            }
        }
        
        if(countdiox==1){
            diox = dio;
        }
        if(countoxy==1){
            oxygen = oxy;
        }
    }

    printf("Part 2: %d\n", oxygen*diox);
    
    return;
}

void part1()
{
   FILE *f;

    f = fopen("input.txt","r");

    long int bits;
    int comm[2][BITS]={0};
    long int gamma,beta;


    while (fscanf(f,"%ld",&bits)!=EOF)
    {   
        //printf("%ld\n",bits);
        for (size_t i = 0; i < BITS; i++)
        {
            comm[bits%10][i]++;
            bits = bits/10;
        }
    }
    
    for (size_t i = 0; i < BITS; i++)
    {
        if(comm[1][i] > comm[0][i]) gamma+=pow(10,i);
        if(comm[0][i] > comm[1][i]) beta+=pow(10,i);
    }

    printf("Part 1: %d\n", bin2dec(gamma)*bin2dec(beta));
    
    return;
}


int main()
{
    //part1();
    part2();
    return 0;
}



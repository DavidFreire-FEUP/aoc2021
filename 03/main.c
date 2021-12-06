#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BITS 12

int bin2dec(long int bin){
    int dec=0;
    long int aux = bin;

    for (size_t i = 0; aux>0; i++)
    {
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
    int commoxy[2]={0},commdiox[2]={0};
    int oxygen=0,diox=0,oxy,dio;

    int countoxy,countdiox;
    int bit,mostcommoxy,mostcommdiox,equaloxy,equaldiox;
    long int andoxy=0,anddiox=0;

    for (int i = BITS-1; i >= 0; i--)
    {
        commoxy[0]=0; commoxy[1]=0;
        commdiox[0]=0; commdiox[1]=0;
        
        while (fscanf(f,"%ld",&bits)!=EOF)
        {   
            if (((bin2dec(bits) ^ bin2dec(andoxy)) < 1<<(i+1)) || i==BITS-1)
            {
                bit = bitAt(bits,i);
                commoxy[bit]=commoxy[bit]+1;
            }  

            if (((bin2dec(bits) ^ bin2dec(anddiox)) < 1<<(i+1)) || i==BITS-1)
            {
                bit = bitAt(bits,i);
                commdiox[bit]=commdiox[bit]+1;
            }  
        }

        equaloxy=0; equaldiox=0;
        if(commoxy[1]>commoxy[0]) {
            mostcommoxy=1;
            andoxy+=pow(10,i); 
        }
        else if(commoxy[0]>commoxy[1]) {
            mostcommoxy=0;
        }
        else if(commoxy[1]==commoxy[0]) {
            equaloxy=1;
            andoxy+=pow(10,i);
        }

        if(commdiox[1]>commdiox[0]) {
            mostcommdiox=1;
        }
        else if(commdiox[0]>commdiox[1]) {
            mostcommdiox=0;
            anddiox+=pow(10,i); 
        }
        else if(commdiox[1]==commdiox[0]) {
            equaldiox=1;
        }

        rewind(f);

        while (fscanf(f,"%ld",&bits)!=EOF)
        {   
            if(((bin2dec(bits) ^ bin2dec(andoxy)) < 1<<(i+1))){
                if(bitAt(bits,i)==mostcommoxy && !equaloxy){
                    oxy = bin2dec(bits);
                }
                else if(equaloxy){
                    if(bitAt(bit,i) == 1){
                        oxy = bin2dec(bits);
                    }
                }
            }

            if(((bin2dec(bits) ^ bin2dec(anddiox)) < 1<<(i+1))){
                if(bitAt(bits,i)!=mostcommdiox && !equaldiox){
                    dio = bin2dec(bits);
                }
                else if(equaldiox){
                    if(bitAt(bit,i) == 0){
                        dio = bin2dec(bits);
                    }
                }

                
            }
            
        }

        rewind(f);
        
        oxygen = oxy;
        diox = dio;
    }
    
    //printf("oxygen: %d\ndiox: %d\n", oxygen,diox);

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
        for (size_t i = 0; i < BITS; i++)
        {
            comm[1-bits%10][i]++;
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
    part1();
    part2();
    return 0;
}



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

    f = fopen("sample.txt","r");

    long int bits;
    int comm[2]={0};
    int oxygen=0,diox=0,oxy,dio;

    int countoxy,countdiox;
    int bit,mostcomm,equal;
    long int andoxy=0,anddiox=0;
    long int aux = 0;

    for (int i = BITS-1; i >= 0; i--)
    {
        comm[0]=0; comm[1]=0;
        printf("%ld\n",andoxy);
        
        while (fscanf(f,"%ld",&bits)!=EOF)
        {   
            //printf("%d %d\n",bin2dec(bits) ^ bin2dec(andoxy),aux);
            if ((bin2dec(bits) ^ bin2dec(andoxy) < aux) || i==BITS-1)
            {
                bit = bitAt(bits,i);
                comm[bit]=comm[bit]+1;
            }  
        }

        aux+=1<<i;

        printf("%d %d\n", comm[0],comm[1]);

        equal=0;
        if(comm[1]>comm[0]) {
            mostcomm=1;
            andoxy+=pow(10,i); 
        }
        else if(comm[0]>comm[1]) mostcomm=0;
        else if(comm[1]==comm[0]) {
            equal=1;
            andoxy+=pow(10,i);
        }

        rewind(f);

        countoxy=0;
        while (fscanf(f,"%ld",&bits)!=EOF)
        {   
            if(bitAt(bits,i)==mostcomm && !equal){
                oxy = bin2dec(bits);
                countoxy++;
            }
            
            else if(equal){
                if(bitAt(bit,i) == 1){
                    oxy = bin2dec(bits);
                    countoxy++;
                }
            }

        }

        rewind(f);
        
        if(countoxy==1) oxygen = oxy;
    }
    
    printf("oxygen: %d\ndiox: %d\n", oxygen,diox);

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
    //printf("%d\n",compareBits(1101,1111,2));
    //part1();
    part2();
    return 0;
}



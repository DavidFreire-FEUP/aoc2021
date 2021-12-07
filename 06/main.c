#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef unsigned short int USINT;
typedef unsigned int UINT;
typedef unsigned long long int ULLI;

#define SIMULATION_DAYS 80

void printState(UINT qtd_fish,USINT fish[qtd_fish])
{
    for (size_t i = 0; i < qtd_fish; i++)
    {
        printf("%d ",fish[i]);
    }
    printf("\n");
    
}

USINT *appendNewFish(UINT *size,USINT *vec,UINT new_fish_qtd)
{
    UINT new_size = *size+new_fish_qtd;
    USINT * new = malloc(sizeof(USINT)*new_size);

    for (size_t i = 0; i < *size; i++)
    {
        new[i]=vec[i];
    }
    for (size_t i = 0; i < new_fish_qtd; i++)
    {
        new[*size+i] = 8;
    }
    free(vec);

    *size = new_size;
    return new;
}

void part1()
{
    FILE *f;

    f = fopen("input.txt","r");

    char line[1024];
    char line_copy[1024];
    UINT qtd_fish=0;

    fgets(line,1024,f);

    strcpy(line_copy,line);
    char *token = strtok(line_copy,",");
    while (token!=NULL)
    {
        qtd_fish++;
        token = strtok(NULL,",");
    }

    USINT *fish = malloc(sizeof(USINT)*qtd_fish);

    token = strtok(line,",");
    for (size_t i = 0; i < qtd_fish; i++)
    {
        fish[i]=atoi(token);

        token = strtok(NULL,",");
    }
    
    UINT newfish;
    for (size_t i = 0; i < SIMULATION_DAYS; i++)
    {
        newfish=0;
        for (size_t j = 0; j < qtd_fish; j++)
        {
            if(fish[j] == 0)
            {
                newfish++;
                fish[j]=6;
            }
            else fish[j]--;
        }
        if(newfish>0) fish = appendNewFish(&qtd_fish,fish,newfish);
    }

    printf("Part 1: %d\n", qtd_fish);
    free(fish);
    return;
}

void tsoding(USINT sim_days)
{
    FILE *f;

    f = fopen("input.txt","r");

    char line[1024];
    ULLI fish[9]={0};

    fgets(line,1024,f);

    char *token = strtok(line,",");
    while (token!=NULL)
    {
        fish[atoi(token)]++;
        token = strtok(NULL,",");
    }

    ULLI atzero;
    for (size_t i = 0; i < sim_days; i++)
    {
        atzero = fish[0];
        for (size_t j = 0; j < 8; j++)
        {
            fish[j]=fish[j+1];
        }

        fish[6]+=atzero;
        fish[8]=atzero;
    }

    ULLI qtd_fish=0;
    for (size_t i = 0; i < 9; i++)
    {
        qtd_fish+=fish[i];
    }
    
    printf("Part 2 Tsoding: %llu\n", qtd_fish);
    return;
}


int main()
{
    part1();
    tsoding(256);
    return 0;
}
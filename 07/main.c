#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef unsigned short int USINT;
typedef unsigned int UINT;
typedef unsigned long long int ULLI;

void part1()
{
    FILE *f;

    f = fopen("input.txt","r");

    char line[4096];
    USINT count=0;
    
    fgets(line,4096,f);

    char *token = strtok(line,",");
    while (token!=NULL) 
    {
        count++;
        token = strtok(NULL,",");
    }
    rewind(f);
    fgets(line,4096,f);

    USINT points[count];
    USINT checked[count];

    token = strtok(line,",");
    for (size_t i = 0; i < count && token!=NULL; i++)
    {
        points[i]=atoi(token);
        token = strtok(NULL,",");
        checked[i]=0;
    }
    
    USINT sorted[count];
    USINT min=SHRT_MAX, pos=0;
    for (size_t i = 0; i < count; i++)
    {
        min = SHRT_MAX;
        for (size_t j = 0; j < count; j++)
        {
            if (points[j]<min && checked[j]==0)
            {
                min=points[j];
                pos=j;
            }
        }
        checked[pos]=1;
        sorted[i] = min;
    }

    USINT median;
    if (count%2==0)
    {
        USINT sum_middle = sorted[count/2]+sorted[count/2-1];
        median = (sum_middle)/2;       
    }
    else median = sorted[(count-1)/2];

    UINT total_fuel=0;
    for (size_t i = 0; i < count; i++) total_fuel += abs(median-sorted[i]);

    printf("Part 1: %d\n", total_fuel);
    return;
}

void part2()
{
    FILE *f;

    f = fopen("input.txt","r");

    char line[4096];
    USINT count=0;
    
    fgets(line,4096,f);

    char *token = strtok(line,",");
    while (token!=NULL) 
    {
        count++;
        token = strtok(NULL,",");
    }
    rewind(f);
    fgets(line,4096,f);

    USINT points[count];
    UINT sum=0;

    token = strtok(line,",");
    for (size_t i = 0; i < count && token!=NULL; i++)
    {
        sum+=atoi(token);
        points[i]=atoi(token);
        token = strtok(NULL,",");
    }

    long unsigned int total_fuel=0;
    USINT avg = sum/count;

    for (size_t i = 0; i < count; i++)
    {
        for (size_t j = 0; j <= abs((int)avg-(int)points[i]); j++) total_fuel+=j;
    }
    
    printf("Part 2: %lu\n", total_fuel);
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
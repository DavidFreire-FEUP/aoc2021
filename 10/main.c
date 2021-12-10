#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

typedef unsigned short int USINT;
typedef unsigned int UINT;
typedef unsigned long long int ULLI;

#if 1
#define INPUT_FILE "input.txt"
#else
#define INPUT_FILE "sample.txt"
#endif

#define CAP 256
#define LEGAL_PAIRS 4

const char *pairs="()[]{}<>";
const int points[4]={3,57,1197,25137};

int isPair(char a,char b)
{
    for (size_t i = 0; i < LEGAL_PAIRS*2; i+=2)
    {
        if(a==pairs[i] && b==pairs[i+1]) return 1;
    }

    return 0;
}

int equalMaps(int sz, int a[sz],int b[sz])
{
    for (size_t i = 0; i < sz; i++)
    {
        //printf("%d %d\n",a[i],b[i]);
        if(a[i]!=b[i]) return 0;
    }

    return 1;
}

void printMap(size_t line_size, int map[line_size]){
    for (size_t i = 0; i < line_size; i++)
    {
        printf("%d",map[i]);
    }
    printf("\n");
}

int isClosingElement(char a)
{
    for (size_t i = 1; i < LEGAL_PAIRS*2; i+=2)
    {
        if (a == pairs[i]) return 1;
    }

    return 0;
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    int score = 0;
    char line[CAP];
    char a,b;
    size_t idx,line_size;
    while (fscanf(f,"%s",line)!=EOF)
    {
        line_size = strlen(line);
        int map[line_size]; // save indexes of previously closed chunks
        int auxmap[line_size]; // copy of map
        for (size_t i = 0; i < line_size; i++) map[i]=0;

        while (1)
        {
            for (size_t i = 0; i < line_size; i++) auxmap[i]=map[i]; // save state of map

            for (size_t i = 0; i < line_size-1; i++) // look for pair
            {
                a = line[i];
                idx = i;
                while (map[i+1] && i<line_size-1) i++;
                
                if(isPair(a,line[i+1])){
                    map[idx]=1;
                    map[i+1]=1;
                }
            }
            if(equalMaps(line_size,auxmap,map)) break; // if we didn't add any new chunks, exit this
        }
        
        // find illegal pair
        for (size_t i = 0; i < line_size; i++)
        {
            if(!map[i] && isClosingElement(line[i])){

                USINT isIllegal=0;
                if (i>0)
                {
                    for (size_t j = i-1; j > 0; j--)
                    {
                        if (!map[j] && !isPair(line[j],line[i])) // This ensures we are not in an unchecked pair closing element
                        {
                            isIllegal=1;
                        }
                        
                    }
                }

                if (isIllegal)
                {
                    switch (line[i])
                    {
                        case ')':
                            score += points[0];
                            break;
                        case ']':
                            score += points[1];
                            break;
                        case '}':
                            score += points[2];
                            break;
                        case '>':
                            score += points[3]; 
                            break;
                        default:
                            break;
                    }

                    break; // break since we only want the first one
                }
            }   
        }  
        
    }

    printf("Part 1: %d\n", score);
    return;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    char line[CAP];
    char a;
    size_t idx,line_size,line_count=0;

    while (fscanf(f,"%s",line)!=EOF) line_count++;

    long long int score[line_count];
    for (size_t i = 0; i < line_count; i++) score[i]=0;

    rewind(f);

    line_count=0;

    while (fscanf(f,"%s",line)!=EOF)
    {
        line_size = strlen(line);
        int map[line_size]; // save indexes of previously closed chunks
        int auxmap[line_size]; // just copy of map
        for (size_t i = 0; i < line_size; i++) map[i]=0;

        // FINDS INITIAL PAIRS
        while (1)
        {
            for (size_t i = 0; i < line_size; i++) auxmap[i]=map[i]; // save map state

            for (size_t i = 0; i < line_size-1; i++) // look for pairs
            {
                a = line[i];
                idx = i;
                while (map[i+1] && i<line_size-1) i++;
                
                if(isPair(a,line[i+1])){
                    map[idx]=1;
                    map[i+1]=1;
                }
            }

            if(equalMaps(line_size,auxmap,map)) break; // if we didn't add any new chunks, exit this
        }
        //

        // FIND ILLEGAL PAIR
        USINT isIllegal=0;
        for (size_t i = 0; i < line_size && !isIllegal; i++)
        {
            if(!map[i] && isClosingElement(line[i])){
                
                if (i>0)
                {
                    for (size_t j = i-1; j > 0; j--)
                    {
                        if (!map[j] && !isPair(line[j],line[i])) // This ensures we are not in an unchecked pair closing element
                        {
                            isIllegal=1;
                            break;
                        }
                    }
                }
            }   
        }  

        if (isIllegal) continue; // we only care about lines without illegal pairs

        for (int i = line_size-1; i >=0; i--)
        {
            if (!map[i])
            {
                score[line_count]*= 5;
                if (isPair(line[i],')')) score[line_count] += 1;
                else if (isPair(line[i],']')) score[line_count] += 2;
                else if (isPair(line[i],'}')) score[line_count] += 3;
                else if (isPair(line[i],'>')) score[line_count] += 4;
 
            }
        }

        line_count++;
    }


    long long int ordered_scored[line_count];

    // simple sorting algorithm
    USINT checked[line_count];
    for (size_t i = 0; i < line_count; i++) checked[i]=0;
    long long int min=LLONG_MAX;
    int pos=0;
    for (size_t i = 0; i < line_count; i++)
    {
        min = LLONG_MAX;
        for (size_t j = 0; j < line_count; j++)
        {
            if (score[j]<min && checked[j]==0)
            {
                min=score[j];
                pos=j;
            }
        }
        checked[pos]=1;
        ordered_scored[i] = min;
    }
    
    printf("Part 2: %lld\n", ordered_scored[(line_count-1)/2]);
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
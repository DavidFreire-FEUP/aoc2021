/// This problem could have both parts solved with part2's implementation of 
/// applyInsertionsSmart() function, but I still left the "dumb" (inefficient)
/// implementation of applyInsertionsDumb() here since it's probably the most trivial
/// and would work for part1's requirements

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

#define STEPS_1 10
#define STEPS_2 40
#define P_CAP 100000
#define C_CAP 26

typedef struct _insertion
{
    char pair[3];
    char element;
} Insertion;

char polymer[P_CAP];
int p_sz=0;

void applyInsertionsDumb(char polymer[P_CAP],int ins_sz, Insertion in[ins_sz])
{
    int insertionOrder[P_CAP]={-1};
    int insertion_count=0;
    char p_copy[p_sz];

    for (size_t i = 0; i < p_sz; i++) p_copy[i]=polymer[i];

    for (size_t i = 0; i < ins_sz; i++)
    {
        for (size_t j = 1; j < p_sz; j++)
        {
            if(polymer[j] == in[i].pair[1] && polymer[j-1] == in[i].pair[0])
            {
                insertionOrder[j]=i;
                insertion_count++;
            }
        }
    }

    size_t l=0,k=0;
    
    for (size_t j = 0; j < p_sz; j++)
    {
        if(insertionOrder[j]>=0)
        {
            polymer[l] = in[insertionOrder[j]].element;
            l++;
            polymer[l] = p_copy[k];
            k++;
        }
        else 
        {
            polymer[l] = p_copy[k];
            k++;
        }
        l++;
        
    }

    p_sz +=insertion_count;

    return;
}

void applyInsertionsSmart(ULLI pairTracker[26][26], int ins_sz, Insertion in[ins_sz],ULLI char_counter[26])
{
    ULLI pairTrackCopy[26][26];
    for (size_t i = 0; i < 26; i++)
        for (size_t j = 0; j < 26; j++)
            pairTrackCopy[i][j] = 0;
    
    int a,b,c;
    ULLI aux;
    for (size_t i = 0; i < ins_sz; i++)
    {
        a = in[i].pair[0] - 'A';
        b = in[i].element - 'A';
        c = in[i].pair[1] - 'A';
        if (pairTracker[a][c]>0)
        {
            pairTrackCopy[a][b]+=pairTracker[a][c];
            pairTrackCopy[b][c]+=pairTracker[a][c];
            char_counter[b]+=pairTracker[a][c];
            pairTracker[a][c]=0;
        }
    }

    for (size_t i = 0; i < 26; i++)
        for (size_t j = 0; j < 26; j++)
            pairTracker[i][j] += pairTrackCopy[i][j];

    return;
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");

    char line[64];

    size_t i=0;
    for (i=0; fscanf(f,"%s",line)!=EOF; i++)
    {
        if(i==0)
        {
            strcpy(polymer,line);
            p_sz += strlen(line); 
        }
    }

    Insertion ins[i-2];
    char *token;
    rewind(f);

    i=0;
    while (fgets(line,64,f)!=NULL)
    {
        if(strstr(line,"->")!=NULL)
        {
            token = strtok(line," -> ");
            ins[i].pair[0]=token[0];
            ins[i].pair[1]=token[1];
            ins[i].pair[2]='\0';
            token = strtok(NULL," -> ");
            ins[i].element = token[0];
            i++;
        }
    }
    int ins_count = i;

    for (size_t s = 0; s < STEPS_1; s++) applyInsertionsDumb(polymer,ins_count,ins);

    int char_count[26]={0};
    for (i = 0; i < p_sz; i++) char_count[polymer[i]-'A']++;

    int max = 0, min = INT_MAX;
    for (size_t i = 0; i < 26; i++)
    {
        if(char_count[i]>max && char_count[i]>0) max = char_count[i];
        if(char_count[i]<min && char_count[i]>0) min = char_count[i]; 
    }

    printf("Part 1: %d\n", max-min);
    return;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");

    ULLI pairTrack[26][26];
    for (size_t i = 0; i < 26; i++) for (size_t j = 0; j < 26; j++) pairTrack[i][j] = 0;

    char line[64];

    size_t i=0;
    ULLI char_count[26]={0};
    for (i=0; fscanf(f,"%s",line)!=EOF; i++)
    {
        if(i==0)
        {
            for (size_t j = 0; j < strlen(line)-1; j++)
            {
                pairTrack[line[j]-'A'][line[j+1]-'A']++;
                char_count[line[j]-'A']++;
                if(j==strlen(line)-2)
                    char_count[line[j+1]-'A']++;
            }
            
        }  
    }
    
    Insertion ins[i-2];
    char *token;
    rewind(f);

    i=0;
    while (fgets(line,64,f)!=NULL)
    {
        if(strstr(line,"->")!=NULL)
        {
            token = strtok(line," -> ");
            ins[i].pair[0]=token[0];
            ins[i].pair[1]=token[1];
            ins[i].pair[2]='\0';
            token = strtok(NULL," -> ");
            ins[i].element = token[0];
            i++;
        }
    }
    int ins_count = i;
    
    for (size_t i = 0; i < STEPS_2; i++) applyInsertionsSmart(pairTrack,ins_count,ins,char_count);

    ULLI max = 0, min = ULLONG_MAX;
    for (size_t i = 0; i < 26; i++)
    {
        if(char_count[i]>max && char_count[i]>0) max = char_count[i];
        if(char_count[i]<min && char_count[i]>0) min = char_count[i]; 
    }
    
    printf("Part 2: %llu\n", max-min);
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
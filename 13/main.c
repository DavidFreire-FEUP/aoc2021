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

enum Axis {X_AXIS,Y_AXIS};

typedef struct _Instruction
{
    enum Axis axis;
    int coord;
} Instruction;

void drawGrid(int oX, int oY, int x, int y, int grid[oY][oX])
{
    printf("\n");
    for (size_t i = 0; i < y; i++)
    {
        for (size_t j = 0; j < x; j++)
        {
            if (grid[i][j]) printf("#");
            else printf(" ");
        }
        printf("\n");
    }

    return;
}

void foldGrid(int oX,int oY,int *x,int *y,int grid[oY][oX], Instruction instruction)
{
    int newCoord = instruction.coord;

    if (instruction.axis == X_AXIS)
    {
        for (size_t i = 0; i < *y; i++)
        {
            for (size_t j = 0; j < newCoord; j++)
            {
                if(*x-j-1 > newCoord)
                    grid[i][j] = grid[i][j] || grid[i][*x-j-1];
            }
        }
        *x=newCoord;
    }
    else if (instruction.axis == Y_AXIS)
    {
        for (size_t i = 0; i < newCoord; i++)
        {
            for (size_t j = 0; j < *x; j++)
            {
                if(*y-i-1 > newCoord)
                    grid[i][j] = grid[i][j] || grid[*y-i-1][j];
            }
        }
        *y=newCoord;
    }
    
    return;
}


void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");

    char line[64];
    size_t instruction_sz=0;
    int maxX=-1,maxY=-1;
    char *token,*token2;

    while (fgets(line,64,f)!=NULL) if (strstr(line,"fold")!=NULL) instruction_sz++;

    rewind(f);

    Instruction ins[instruction_sz];
    instruction_sz=0;
   
    while (fgets(line,64,f)!=NULL)
    {
        if (strstr(line,"fold")!=NULL)
        {
            token = strtok(line,"=");
            if (token[strlen(token)-1]=='x')        
                ins[instruction_sz].axis = X_AXIS;
            else if (token[strlen(token)-1]=='y')   
                ins[instruction_sz].axis = Y_AXIS;

            token = strtok(NULL,"=");
            ins[instruction_sz].coord = atoi(token);
            instruction_sz++;
        }
    }

    rewind(f);

    for (size_t i = 0; i < instruction_sz; i++)
    {
        if(maxX>=0 && maxY>=0) break;
        if (ins[i].axis==X_AXIS && maxX==-1) maxX= 2*ins[i].coord+1;
        else if(ins[i].axis==Y_AXIS && maxY==-1) maxY= 2*ins[i].coord+1;
    }
    
    int grid[maxY][maxX];

    for (size_t i = 0; i < maxY; i++) for (size_t j = 0; j < maxX; j++) grid[i][j]=0;
    
    while (fgets(line,64,f)!=NULL)
    {
        if(strstr(line,",")!=NULL)
        {
            token = strtok(line,",");
            token2 = strtok(NULL,",");
            grid[atoi(token2)][atoi(token)] = 1;
        }   
    }

    int oX=maxX,oY=maxY;

    foldGrid(oX,oY,&maxX,&maxY,grid,ins[0]);  

    int result=0;
    for (size_t i = 0; i < maxY; i++)
    {
        for (size_t j = 0; j < maxX; j++)
            if(grid[i][j]) result++;
    }
    
    printf("Part 1: %d\n",result);
    return;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");

    char line[64];
    size_t instruction_sz=0;
    int maxX=-1,maxY=-1;
    char *token,*token2;

    while (fgets(line,64,f)!=NULL) if (strstr(line,"fold")!=NULL) instruction_sz++;

    rewind(f);

    Instruction ins[instruction_sz];
    instruction_sz=0;
   
    while (fgets(line,64,f)!=NULL)
    {
        if (strstr(line,"fold")!=NULL)
        {
            token = strtok(line,"=");
            if (token[strlen(token)-1]=='x')        
                ins[instruction_sz].axis = X_AXIS;
            else if (token[strlen(token)-1]=='y')   
                ins[instruction_sz].axis = Y_AXIS;

            token = strtok(NULL,"=");
            ins[instruction_sz].coord = atoi(token);
            instruction_sz++;
        }
    }

    rewind(f);

    for (size_t i = 0; i < instruction_sz; i++)
    {
        if(maxX>=0 && maxY>=0) break;
        if (ins[i].axis==X_AXIS && maxX==-1) maxX= 2*ins[i].coord+1;
        else if(ins[i].axis==Y_AXIS && maxY==-1) maxY= 2*ins[i].coord+1;
    }
    
    int grid[maxY][maxX];

    for (size_t i = 0; i < maxY; i++) for (size_t j = 0; j < maxX; j++) grid[i][j]=0;
    
    while (fgets(line,64,f)!=NULL)
    {
        if(strstr(line,",")!=NULL)
        {
            token = strtok(line,",");
            token2 = strtok(NULL,",");
            grid[atoi(token2)][atoi(token)] = 1;
        }   
    }

    int oX=maxX,oY=maxY;

    for (size_t i = 0; i < instruction_sz; i++) foldGrid(oX,oY,&maxX,&maxY,grid,ins[i]);  

    printf("Part 2: ");
    drawGrid(oX,oY,maxX,maxY,grid);
    
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
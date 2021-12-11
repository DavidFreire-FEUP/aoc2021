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

#define GRID_SIDE 10
#define STEPS 100

ULLI flashes = 0;

void tryFlash(int i,int j,int grid[GRID_SIDE][GRID_SIDE])
{
    if (i>=GRID_SIDE || j>=GRID_SIDE)
    {
        printf("Out of bounds: %d %d", i,j);
        return;
    }
    
    if(grid[i][j]>9)
    {
        flashes++;
        grid[i][j]=0;
        if (i==0)
        {
            if (j==0)
            {
                if(grid[i][j+1] <= 9 && grid[i][j+1])
                {
                    grid[i][j+1]++;
                    tryFlash(i,j+1,grid);
                }
                if(grid[i+1][j] <= 9 && grid[i+1][j])
                {
                    grid[i+1][j]++;
                    tryFlash(i+1,j,grid);
                }
                if(grid[i+1][j+1] <= 9 && grid[i+1][j+1])
                {
                    grid[i+1][j+1]++;
                    tryFlash(i+1,j+1,grid);
                }
            }
            else if (j==GRID_SIDE-1)
            {
                if(grid[i][j-1] <= 9 && grid[i][j-1])
                {
                    grid[i][j-1]++;
                    tryFlash(i,j-1,grid);
                }
                if(grid[i+1][j] <= 9 && grid[i+1][j])
                {
                    grid[i+1][j]++;
                    tryFlash(i+1,j,grid);
                }
                if(grid[i+1][j-1] <= 9 && grid[i+1][j-1])
                {
                    grid[i+1][j-1]++;
                    tryFlash(i+1,j-1,grid);
                }
            }
            else
            {
                if(grid[i][j-1] <= 9 && grid[i][j-1])
                {
                    grid[i][j-1]++;
                    tryFlash(i,j-1,grid);
                }
                if(grid[i][j+1] <= 9 && grid[i][j+1])
                {
                    grid[i][j+1]++;
                    tryFlash(i,j+1,grid);
                }
                if(grid[i+1][j-1] <= 9  && grid[i+1][j-1])
                {
                    grid[i+1][j-1]++;
                    tryFlash(i+1,j-1,grid);
                }
                if(grid[i+1][j] <= 9 && grid[i+1][j])
                {
                    grid[i+1][j]++;
                    tryFlash(i+1,j,grid);
                }
                if(grid[i+1][j+1] <= 9 && grid[i+1][j+1])
                {
                    grid[i+1][j+1]++;
                    tryFlash(i+1,j+1,grid);
                }
            }
            
        }
        else if (i==GRID_SIDE-1)
        {
            if (j==0)
            {
                if(grid[i][j+1] <= 9 && grid[i][j+1])
                {
                    grid[i][j+1]++;
                    tryFlash(i,j+1,grid);
                }
                if(grid[i-1][j] <= 9 && grid[i-1][j])
                {
                    grid[i-1][j]++;
                    tryFlash(i-1,j,grid);
                }
                if(grid[i-1][j+1] <= 9 && grid[i-1][j+1])
                {
                    grid[i-1][j+1]++;
                    tryFlash(i-1,j+1,grid);
                }
            }
            else if (j==GRID_SIDE-1)
            {
                if(grid[i][j-1] <= 9 && grid[i][j-1])
                {
                    grid[i][j-1]++;
                    tryFlash(i,j-1,grid);
                }
                if(grid[i-1][j] <= 9 && grid[i-1][j])
                {
                    grid[i-1][j]++;
                    tryFlash(i-1,j,grid);
                }
                if(grid[i-1][j-1] <= 9 && grid[i-1][j-1])
                {
                    grid[i-1][j-1]++;
                    tryFlash(i-1,j-1,grid);
                }
            }
            else
            {
                if(grid[i][j-1] <= 9 && grid[i][j-1])
                {
                    grid[i][j-1]++;
                    tryFlash(i,j-1,grid);
                }
                if(grid[i][j+1] <= 9 && grid[i][j+1])
                {
                    grid[i][j+1]++;
                    tryFlash(i,j+1,grid);
                }
                if(grid[i-1][j-1] <= 9 && grid[i-1][j-1])
                {
                    grid[i-1][j-1]++;
                    tryFlash(i-1,j-1,grid);
                }
                if(grid[i-1][j] <= 9 && grid[i-1][j])
                {
                    grid[i-1][j]++;
                    tryFlash(i-1,j,grid);
                }
                if(grid[i-1][j+1] <= 9 && grid[i-1][j+1])
                {
                    grid[i-1][j+1]++;
                    tryFlash(i-1,j+1,grid);
                }
            }
        }
        else
        {
            if (j==0)
            {
                if(grid[i][j+1] <= 9 && grid[i][j+1])
                {
                    grid[i][j+1]++;
                    tryFlash(i,j+1,grid);
                }
                if(grid[i-1][j] <= 9 && grid[i-1][j])
                {
                    grid[i-1][j]++;
                    tryFlash(i-1,j,grid);
                }
                if(grid[i+1][j] <= 9 && grid[i+1][j])
                {
                    grid[i+1][j]++;
                    tryFlash(i+1,j,grid);
                }
                if(grid[i-1][j+1] <= 9 && grid[i-1][j+1])
                {
                    grid[i-1][j+1]++;
                    tryFlash(i-1,j+1,grid);
                }
                if(grid[i+1][j+1] <= 9 && grid[i+1][j+1])
                {
                    grid[i+1][j+1]++;
                    tryFlash(i+1,j+1,grid);
                }
            }
            else if (j==GRID_SIDE-1)
            {
                if(grid[i][j-1] <= 9 && grid[i][j-1])
                {
                    grid[i][j-1]++;
                    tryFlash(i,j-1,grid);
                }
                if(grid[i-1][j] <= 9 && grid[i-1][j])
                {
                    grid[i-1][j]++;
                    tryFlash(i-1,j,grid);
                }
                if(grid[i+1][j] <= 9 && grid[i+1][j])
                {
                    grid[i+1][j]++;
                    tryFlash(i+1,j,grid);
                }
                if(grid[i-1][j-1] <= 9 && grid[i-1][j-1])
                {
                    grid[i-1][j-1]++;
                    tryFlash(i-1,j-1,grid);
                }
                if(grid[i+1][j-1] <= 9 && grid[i+1][j-1])
                {
                    grid[i+1][j-1]++;
                    tryFlash(i+1,j-1,grid);
                }
            }
            else
            {
                if(grid[i][j-1] <= 9 && grid[i][j-1])
                {
                    grid[i][j-1]++;
                    tryFlash(i,j-1,grid);
                }
                if(grid[i][j+1] <= 9 && grid[i][j+1])
                {
                    grid[i][j+1]++;
                    tryFlash(i,j+1,grid);
                }
                if(grid[i-1][j-1] <= 9 && grid[i-1][j-1])
                {
                    grid[i-1][j-1]++;
                    tryFlash(i-1,j-1,grid);
                }
                if(grid[i-1][j+1] <= 9 && grid[i-1][j+1])
                {
                    grid[i-1][j+1]++;
                    tryFlash(i-1,j+1,grid);
                }
                if(grid[i+1][j-1] <= 9 && grid[i+1][j-1])
                {
                    grid[i+1][j-1]++;
                    tryFlash(i+1,j-1,grid);
                }
                if(grid[i+1][j+1] <= 9 && grid[i+1][j+1])
                {
                    grid[i+1][j+1]++;
                    tryFlash(i+1,j+1,grid);
                }
                if(grid[i-1][j] <= 9 && grid[i-1][j])
                {
                    grid[i-1][j]++;
                    tryFlash(i-1,j,grid);
                }
                if(grid[i+1][j] <= 9 && grid[i+1][j])
                {
                    grid[i+1][j]++;
                    tryFlash(i+1,j,grid);
                }
            }
        }
      
    }

    return;
}

void printGrid(int grid[GRID_SIDE][GRID_SIDE])
{
    for (size_t i = 0; i < GRID_SIDE; i++)
    {
        for (size_t j = 0; j < GRID_SIDE; j++)
        {
            printf("%d",grid[i][j]);
        }
        printf("\n");
    }
    return;
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    int grid[GRID_SIDE][GRID_SIDE];
    char line[GRID_SIDE+1];
    

    for (size_t i = 0; fscanf(f,"%s",line)!=EOF; i++) 
    {
        for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j] = line[j] - '0';
    }

    for (size_t s = 0; s < STEPS; s++)
    {
        for (size_t i = 0; i < GRID_SIDE; i++)
        {
            for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j]++;
        }

        for (size_t i = 0; i < GRID_SIDE; i++)
        {
            for (size_t j = 0; j < GRID_SIDE; j++) tryFlash(i,j,grid);
        }
    }
    
    printf("Part 1: %llu\n",flashes);
    return;
}

int allFlash(int grid[GRID_SIDE][GRID_SIDE])
{
    for (size_t i = 0; i < GRID_SIDE; i++)
    {
        for (size_t j = 0; j < GRID_SIDE; j++)
        {
            if(grid[i][j]) return 0;
        }
    }
    return 1;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    int grid[GRID_SIDE][GRID_SIDE];
    char line[GRID_SIDE+1];
    

    for (size_t i = 0; fscanf(f,"%s",line)!=EOF; i++) 
    {
        for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j] = line[j] - '0';
    }

    size_t s=0;
    while (1)
    {
        for (size_t i = 0; i < GRID_SIDE; i++)
        {
            for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j]++;
        }

        for (size_t i = 0; i < GRID_SIDE; i++)
        {
            for (size_t j = 0; j < GRID_SIDE; j++) tryFlash(i,j,grid);
        }

        if(allFlash(grid)) break;

        s++;
    }
    
    printf("Part 2: %lu\n",s+1);
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
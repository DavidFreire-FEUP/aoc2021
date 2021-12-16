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
#define GRID_SIDE 100
#else
#define INPUT_FILE "sample.txt"
#define GRID_SIDE 10
#endif 

#define PATH_CAP GRID_SIDE*GRID_SIDE

typedef struct _node
{
    int i;
    int j;
} Node;

void printGrid(int grid[GRID_SIDE][GRID_SIDE])
{
    for (size_t i = 0; i < GRID_SIDE; i++)
    {
        for (size_t j = 0; j < GRID_SIDE; j++)
            printf("%d", grid[i][j]);
        printf("\n");
    }
}

int risk=INT_MAX;
int path_count=0;

void paths_util(Node start, Node end, /*int visited[GRID_SIDE][GRID_SIDE], Node path[PATH_CAP], int *path_index,*/int *path_risk, int grid[GRID_SIDE][GRID_SIDE])
{
    //visited[start.i][start.j] = 1;
    if(start.i!=0 || start.j!=0)
        *path_risk+=grid[start.i][start.j];
    //path[*path_index]=start;
    //*path_index = *path_index+1;

    if (start.i==end.i && start.j==end.j)
    {
        if (*path_risk<risk) risk=*path_risk;
        printf("%d %d\n",path_count,risk);
        path_count++;
    }
    else
    {
        Node a,b;
        a.i = start.i;      a.j = start.j + 1;
        b.i = start.i + 1;  b.j = start.j;
        if (a.i>=0 && a.j>=0 && a.i<=GRID_SIDE-1 && a.j<=GRID_SIDE-1 && *path_risk+grid[a.i][a.j]<risk /*&& grid[a.i][a.j]<=grid[b.i][b.j]*/)
        {
            paths_util(a,end,path_risk,grid);
        }
            
        if (b.i>=0 && b.j>=0 && b.i<=GRID_SIDE-1 && b.j<=GRID_SIDE-1 && *path_risk+grid[b.i][b.j]<risk /*&& grid[a.i][a.j]>=grid[b.i][b.j]*/)
        {
            paths_util(b,end,path_risk,grid);
        }
    }
    
    //*path_index = *path_index-1;
    //visited[start.i][start.j] = 0;    
    *path_risk-=grid[start.i][start.j];

    return;
}

void paths(Node start, Node end, int grid[GRID_SIDE][GRID_SIDE])
{
    /*int visited[GRID_SIDE][GRID_SIDE];
    
    for (size_t i = 0; i < GRID_SIDE; i++)
        for (size_t j = 0; j < GRID_SIDE; j++)
            visited[i][j]=0;*/

    /*Node path[PATH_CAP];
    int path_index = 0;*/
    //int path_risk=0;
    //paths_util(start,end,/*visited,path,&path_index,*/&path_risk,grid);

    //return;
}

Node minDistance(int dist[GRID_SIDE][GRID_SIDE], int visited[GRID_SIDE][GRID_SIDE])
{   
    int min = INT_MAX;
    Node min_index;
 
    for (size_t i = 0; i < GRID_SIDE; i++)
    {
        for (size_t j = 0; j < GRID_SIDE; j++)
        {
            if(!visited[i][j] && dist[i][j]<=min)
            {
                min = dist[i][j];
                min_index.i=i; min_index.j=j;
            }
                
        }
        
    }
    
    return min_index;
}

int areAdjacent(Node u,Node v)
{
    if((u.i+1==v.i && u.j==v.j) || (u.i==v.i && u.j+1==v.j))
        return 1;
    return 0;
}

int dijkstra(int grid[GRID_SIDE][GRID_SIDE])
{
    int dist[GRID_SIDE][GRID_SIDE]; 
    int visited[GRID_SIDE][GRID_SIDE];

    for (size_t i = 0; i < GRID_SIDE; i++)
    {
        for (size_t j = 0; j < GRID_SIDE; j++)
        {
            dist[i][j] = INT_MAX;
            visited[i][j]=0;
        }   
    }

    dist[0][0]=0;
    Node v;
    Node u;

    for (int count = 0; count < GRID_SIDE*GRID_SIDE; count++) {
        u = minDistance(dist,visited);
        visited[u.i][u.j] = 1;
        
        v.i=u.i+1;
        v.j=u.j;
        if(!visited[v.i][v.j] && dist[u.i][u.j]!=INT_MAX && dist[u.i][u.j] + grid[u.i][u.j] < dist[v.i][v.j])
            dist[v.i][v.j] = dist[u.i][u.j] + grid[u.i][u.j];

        v.i=u.i;
        v.j=u.j+1;
        if(!visited[v.i][v.j] && dist[u.i][u.j]!=INT_MAX && dist[u.i][u.j] + grid[u.i][u.j] < dist[v.i][v.j])
            dist[v.i][v.j] = dist[u.i][u.j] + grid[u.i][u.j];

    }

    for (size_t i = 0; i < GRID_SIDE; i++)
    {
        for (size_t j = 0; j < GRID_SIDE; j++)
        {
            printf("%d ",dist[i][j]);
        }
        printf("\n");
        
    }
    
    
    return dist[GRID_SIDE-1][GRID_SIDE-1];
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    int grid[GRID_SIDE][GRID_SIDE];
    char line[GRID_SIDE];

    for (size_t i = 0; fscanf(f,"%s",line)!=EOF && i<GRID_SIDE; i++) 
        for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j] = line[j] - '0';

    grid[0][0]=7;

    Node start,end;
    start.i=0;          start.j=0;
    end.i=GRID_SIDE-1;  end.j=GRID_SIDE-1;

    //printGrid(grid);
    //return;

    //paths(start,end,grid);

    //int min = INT_MAX;

    /*for (size_t i = 0; i < risk_idx; i++)
        if(risk[i]<min) min=risk[i];*/
    int result = dijkstra(grid);
    printf("Part 1: %d\n",risk);
    return;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    
    printf("Part 2: \n");
    return;
}

int main()
{
    part1();
    //part2();
    return 0;
}
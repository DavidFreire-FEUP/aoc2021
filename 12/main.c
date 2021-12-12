#include <ctype.h>
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
#elif 0
#define INPUT_FILE "sample.txt"
#else
#define INPUT_FILE "sample2.txt"
#endif 

enum caveType {SMALL, BIG, SE};

#define CAP 256
#define PATH_CAP 1000
#define CONNECTION_CAP 1000

typedef struct Cave
{       
    char name[16];
    enum caveType type;
    struct Cave *connections;
    size_t connections_sz;
} Cave;

Cave caves[CAP];
size_t cave_sz = 0;
int path_count=0;

void printCave(Cave a)
{
    char type[16];
    switch (a.type)
    {
        case SMALL:
            strcpy(type,"small");
            break;
        case BIG:
            strcpy(type,"big");
            break;
        case SE:
            strcpy(type,"start/end");
            break;
        default:
            break;
    }
    printf("Name: %s\tType: %s\t Connections: %zu\n", a.name, type, a.connections_sz);
    for (size_t i = 0; i < a.connections_sz; i++) printf("%s-%s\n", a.name, a.connections[i].name);
}

void addConnection(Cave *dest, Cave src)
{
    size_t i;
    for (i = 0; i < dest->connections_sz; i++)
        if (!strcmp(dest->connections[i].name,src.name))
            return;

    dest->connections_sz++;
    Cave *aux = (Cave*)malloc(sizeof(Cave)*dest->connections_sz);

    for (i = 0; i < dest->connections_sz - 1; i++) aux[i] = dest->connections[i];
    aux[i] = src;

    if (dest->connections_sz>1)  
        dest->connections = realloc(dest->connections,sizeof(Cave)*dest->connections_sz);
    else 
        dest->connections = (Cave*)malloc(sizeof(Cave));

    for (i = 0; i < dest->connections_sz; i++) dest->connections[i]=aux[i];

    return;
}

int existsCave(char *name)
{
    for (size_t i = 0; i < cave_sz; i++) 
        if (!strcmp(caves[i].name,name)) 
            return i;
    return -1;
}

void addCaves(char * name1, char* name2)
{
    int exists1 = existsCave(name1);
    int exists2 = existsCave(name2);
    if (exists1==-1) 
    {
        strcpy(caves[cave_sz].name,name1);
        if (!strcmp(name1,"start") || !strcmp(name1,"end")) 
            caves[cave_sz].type = SE;
        else if (isupper(name1[0]))                         
            caves[cave_sz].type = BIG;
        else                                                
            caves[cave_sz].type = SMALL;
        cave_sz++;
    }
    if (exists2==-1)
    {
        strcpy(caves[cave_sz].name,name2);
        if (!strcmp(name2,"start") || !strcmp(name2,"end")) 
            caves[cave_sz].type = SE;
        else if (isupper(name2[0]))                         
            caves[cave_sz].type = BIG;
        else                                                
            caves[cave_sz].type = SMALL;
        cave_sz++;
    }
    
    exists1 = existsCave(name1);
    exists2 = existsCave(name2);

    addConnection(&caves[exists1],caves[exists2]);
    addConnection(&caves[exists2],caves[exists1]);

    return;
}

void paths_util(int start, int end, int visited[cave_sz], int path[PATH_CAP], int *path_index)
{
    visited[start]=1;
    path[*path_index]=end;
    *path_index = *path_index+1;

    if (start==end)
    {
        path_count++;
    }
    else
    {
        for (size_t i = 0; i < caves[start].connections_sz; i++)
        {   
            int next = existsCave(caves[start].connections[i].name);
            if(!visited[next] || caves[next].type == BIG) 
                paths_util(next,end,visited,path,path_index);
        }
    }
    
    *path_index = *path_index-1;
    visited[start] = 0;    

    return;
}

int isAnySmallCaveAlreadyVisitedTwice(int visited[cave_sz])
{
    for (size_t i = 0; i < cave_sz; i++) 
        if(visited[i]>=2 && caves[i].type==SMALL) return 1;
    return 0;
}

void paths_util2(int start, int end, int visited[cave_sz], int path[PATH_CAP], int *path_index)
{
    visited[start]++;
    path[*path_index]=end;
    *path_index = *path_index+1;

    if (start==end)
    {
        path_count++;
    }
    else
    {
        for (size_t i = 0; i < caves[start].connections_sz; i++)
        {   
            int next = existsCave(caves[start].connections[i].name);
            if(!visited[next] || caves[next].type == BIG || (caves[next].type == SMALL && visited[next]<2 && !isAnySmallCaveAlreadyVisitedTwice(visited))) 
                paths_util2(next,end,visited,path,path_index);
        }
    }
    
    *path_index = *path_index-1;
    visited[start]--;    

    return;
}

void paths(int start, int end, int sol)
{
    int visited[cave_sz];
    for (size_t i = 0; i < cave_sz; i++) visited[i]=0;

    int path[PATH_CAP];
    int path_index = 0;

    switch (sol)
    {
    case 1:
        paths_util(start,end,visited,path,&path_index);
        break;
    case 2:
        paths_util2(start,end,visited,path,&path_index);
        break;
    default:
        break;
    }

    return;
}

void solution(int sol)
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");

    char line[16],lineaux[16];
    char *name1,*name2;

    while (fscanf(f,"%s",line)!=EOF)
    {
        strcpy(lineaux, line);
        name1 = strtok(lineaux,"-");
        name2 = strtok(NULL,"-");
        addCaves(name1,name2);
    }

    int startindex = existsCave("start");
    int endindex = existsCave("end");

    path_count = 0;
    paths(startindex,endindex,sol);

    printf("Part %d: %d\n",sol,path_count);
    return;
}

int main()
{
    solution(1);
    solution(2);
    return 0;
}
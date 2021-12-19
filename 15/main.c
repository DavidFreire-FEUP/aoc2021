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

typedef struct _coord
{
    int i;
    int j;
} Coord;

typedef struct node {
    Coord xy;
    int dist;
    struct node* next;
} Node;
 
Node* newNode(Coord xy, int dist)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->xy = xy;
    temp->dist = dist;
    temp->next = NULL;
    return temp;
}
 
int peekDistance(Node** head){
    return (*head)->dist;
}
Coord peekCoord(Node** head){
    return (*head)->xy;
}

void pop(Node** head){
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
 
void push(Node** head, Coord xy, int p)
{
    Node* start = (*head);
    Node* temp = newNode(xy, p);

    if ((*head)->dist > p) {
        temp->next = *head;
        (*head) = temp;
    }
    else 
    {
        while (start->next != NULL &&
            start->next->dist < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}
 
int isEmpty(Node** head){
    return (*head) == NULL;
}

void printGrid(int side, int grid[side][side])
{
    for (size_t i = 0; i < side; i++)
    {
        for (size_t j = 0; j < side; j++)
            printf("%d", grid[i][j]);
        printf("\n");
    }
    return;
}

void printHeap(Node *heap)
{
    Node* temp = heap->next;
    if(heap!=NULL)
        printf("(%d %d) %d -> ", heap->xy.i, heap->xy.j,heap->dist);
    while (temp!=NULL)
    {
        printf("(%d %d) %d -> ", temp->xy.i, temp->xy.j,temp->dist);
        temp = temp->next;
    }
    printf("\n");
    
}

void printDist(int side, int dist[side][side])
{
    for (size_t i = 0; i < side; i++)
    {
        for (size_t j = 0; j < side; j++)
        {
            printf("%d ",dist[i][j]);
        }
        printf("\n");
    }
    return;
}

int dijkstra(int side, int grid[side][side])
{
    int dist[side][side]; 
    int visited[side][side];

    for (size_t i = 0; i < side; i++)
    {
        for (size_t j = 0; j < side; j++)
        {
            dist[i][j] = INT_MAX;
            visited[i][j]=0;
        }   
    }
    dist[0][0]=0;
    Coord orig = {.i = 0, .j = 0};
    Node* pq = newNode(orig, 0);
    Coord u,v;

    while (!isEmpty(&pq)) {
        int d = peekDistance(&pq);
        u = peekCoord(&pq);
        pop(&pq);

        if(!visited[u.i][u.j])
        {
            visited[u.i][u.j] = 1;
            if(u.i+1 <= side - 1)
            {
                if(dist[u.i][u.j] + grid[u.i+1][u.j] < dist[u.i+1][u.j])
                {
                    dist[u.i+1][u.j] = dist[u.i][u.j] + grid[u.i+1][u.j];
                    v.i = u.i+1; v.j = u.j;
                    if(!isEmpty(&pq))  
                        push(&pq, v, dist[v.i][v.j]);
                    else pq = newNode(v, dist[v.i][v.j]);
                }
            }
                
            if(u.j+1 <= side - 1)
            {
                if(dist[u.i][u.j] + grid[u.i][u.j+1] < dist[u.i][u.j+1])
                {
                    dist[u.i][u.j+1] = dist[u.i][u.j] + grid[u.i][u.j+1];
                    v.i = u.i; v.j = u.j+1;
                    if(!isEmpty(&pq))  
                        push(&pq, v, dist[v.i][v.j]);
                    else pq = newNode(v, dist[v.i][v.j]);  
                }
            }

            if(u.i-1 > 0)
            {
                if(dist[u.i][u.j] + grid[u.i-1][u.j] < dist[u.i-1][u.j])
                {
                    dist[u.i-1][u.j] = dist[u.i][u.j] + grid[u.i-1][u.j];
                    v.i = u.i-1; v.j = u.j;
                    if(!isEmpty(&pq))  
                        push(&pq, v, dist[v.i][v.j]);
                    else pq = newNode(v, dist[v.i][v.j]);  
                }
            }

            if(u.j-1 > 0 ) 
            {
                if(dist[u.i][u.j] + grid[u.i][u.j-1] < dist[u.i][u.j-1])
                {
                    dist[u.i][u.j-1] = dist[u.i][u.j] + grid[u.i][u.j-1];
                    v.i = u.i; v.j = u.j-1;
                    if(!isEmpty(&pq))  
                        push(&pq, v, dist[v.i][v.j]);
                    else pq = newNode(v, dist[v.i][v.j]);  
                }
            }
        }
    }

    //printDist(side, dist);

    return dist[side-1][side-1];
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    int grid[GRID_SIDE][GRID_SIDE];
    char line[GRID_SIDE];

    for (size_t i = 0; fscanf(f,"%s",line)!=EOF && i<GRID_SIDE; i++) 
        for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j] = line[j] - '0';

    grid[0][0] = GRID_SIDE == 10 ? 1 : 7;

    int result = dijkstra(GRID_SIDE,grid);
    printf("Part 1: %d\n",result);
    return;
}

void part2()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    int grid[GRID_SIDE][GRID_SIDE];
    char line[GRID_SIDE];

    for (size_t i = 0; fscanf(f,"%s",line)!=EOF && i<GRID_SIDE; i++) 
        for (size_t j = 0; j < GRID_SIDE; j++) grid[i][j] = line[j] - '0';

    grid[0][0] = GRID_SIDE==10 ? 1 : 7;

    int newgrid[GRID_SIDE*5][GRID_SIDE*5];
    for (size_t i = 0; i < GRID_SIDE*5; i++) for (size_t j = 0; j < GRID_SIDE*5; j++) newgrid[i][j]=0;
    

    for (size_t i = 0; i < GRID_SIDE; i++) for (size_t j = 0; j < GRID_SIDE; j++) newgrid[i][j] = grid[i][j];

    for (size_t i = GRID_SIDE; i < GRID_SIDE*5; i++) // copy in y axis
    {
        for (size_t j = 0; j < GRID_SIDE*5; j++)
        {
            if(newgrid[i-GRID_SIDE][j] < 9)
                newgrid[i][j] = newgrid[i-GRID_SIDE][j]+1;
            else newgrid[i][j] = 1;
        }
    }

    for (size_t i = 0; i < GRID_SIDE*5; i++) // copy in x axis
    {
        for (size_t j = GRID_SIDE; j < GRID_SIDE*5; j++)
        {
            if(newgrid[i][j-GRID_SIDE] < 9)
                newgrid[i][j] = newgrid[i][j-GRID_SIDE]+1;
            else newgrid[i][j] = 1;
        }
    }

    int result = dijkstra(GRID_SIDE*5,newgrid);
    printf("Part 2: %d\n",result);
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
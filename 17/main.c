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

typedef struct _state
{
    int x_pos;
    int y_pos;
    int x_vel;
    int y_vel;
} State;

typedef struct _target
{
    int x[2];
    int y[2];
} Target;

int isInsideTarget(State s, Target t)
{
    if(s.x_pos >= t.x[0] && s.x_pos <=t.x[1] && s.y_pos >= t.y[0] && s.y_pos <= t.y[1])
        return 1;
    return 0;
}

void nextStep(State *s)
{
    s->x_pos += s->x_vel;
    if(s->x_vel > 0) s->x_vel--;
    else if (s->x_vel < 0) s->x_vel++;
    s->y_pos += s->y_vel;
    s->y_vel--;
    return;
}

void part1()
{
    FILE *f;

    f = fopen(INPUT_FILE,"r");
    char line[64];
    Target T;
    char xs[6]={'\0'},ys[6]={'\0'};
    char *token;
    fgets(line,64,f);
    for (size_t i = 0; i < strlen(line); i++)
    {
        if(line[i]=='x')
        {
            i+=2;
            for (size_t j = 0; line[i+j]!=','; j++)
                xs[j]=line[i+j];
            token = strtok(xs,"..");
            T.x[0]=atoi(token);
            token = strtok(NULL,"..");
            T.x[1]=atoi(token);
        }
        else if(line[i]=='y')
        {
            i+=2;
            for (size_t j = 0; j+i<strlen(line)+1; j++)
                ys[j]=line[i+j];
            token = strtok(ys,"..");
            T.y[0]=atoi(token);
            token = strtok(NULL,"..");
            T.y[1]=atoi(token);
        }
    }
    
    //printf("Target: %d..%d, %d..%d\n", T.x[0],T.x[1],T.y[0],T.y[1]);

    State S={.x_pos=0,.y_pos=0, .x_vel=0,.y_vel=0}; //starts at 0,0
    int initial_x,initial_y;
    int maxy=INT_MIN,max=INT_MIN;
    int x=1,y=0,oldx=-1,oldy=-1;
    while (0)
    {
        S.x_pos = 0; S.y_pos = 0;
        S.x_vel = x;
        S.y_vel = y;
        if(x==oldx && y==oldy) break;
        printf("%d %d\n",x,y);
        maxy=INT_MIN;
        for (size_t steps = 0; S.x_pos <= T.x[1] && S.y_pos >= T.y[0] ; steps++)
        {
            nextStep(&S);
            if(S.y_pos >= maxy) maxy=S.y_pos;
            if(isInsideTarget(S,T)) break;
        }
        oldx = x;
        oldy = y;

        if(isInsideTarget(S,T) /*&& maxy > max*/)
        {
            if(maxy > max)
                max = maxy;
            y++;
            continue;
        }
        else if(S.x_pos > T.x[1]) x--;
        else if (S.x_pos < T.x[0]) x++; 
    }

    S.x_pos = 0; S.y_pos = 0;
    S.x_vel = 5;
    S.y_vel = 0;
    printf("%d..%d %d..%d\n", T.x[0],T.x[1],T.y[0], T.y[1]);
    for (size_t steps = 0; S.x_pos <= T.x[1] && S.y_pos >= T.y[0] ; steps++)
    {
        nextStep(&S);
        if(isInsideTarget(S,T)){
            printf("ayo\n");
            break;
        } 
        printf("step %zu %d %d\n", steps,S.x_pos,S.y_pos);
        if(S.x_pos > T.x[1] && S.y_pos < T.y[0]) printf("ayo\n");
    }


    
    printf("Part 1: %d\n",max);
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
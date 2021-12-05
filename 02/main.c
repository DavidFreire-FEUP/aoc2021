#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part2()
{
    FILE *f;

    f = fopen("input.txt","r");

    char line[16];
    int x;
    long int horizontal = 0, depth = 0, aim=0;

    while (fscanf(f,"%s %d",line,&x)!=EOF)
    {
        //printf("%s %d\n", line,x);
        if(!strcmp(line,"up")){
            aim-=x;
        }
        else if (!strcmp(line,"down"))
        {
            aim+=x;
        }
        else if (!strcmp(line,"forward"))
        {
            horizontal+=x;
            depth+=aim*x;
        }
        
        
    }

    printf("Part 2: %ld\n", horizontal*depth);

    return;
}

void part1()
{
   FILE *f;

    f = fopen("input.txt","r");

    char line[16];
    int x;
    int horizontal = 0, depth = 0;

    while (fscanf(f,"%s %d",line,&x)!=EOF)
    {
        
        if(!strcmp(line,"up")){
            depth-=x;
        }
        else if (!strcmp(line,"down"))
        {
            depth+=x;
        }
        else if (!strcmp(line,"forward"))
        {
            horizontal+=x;
        }
        
        
    }

    printf("Part 1: %d\n", horizontal*depth);
    

    return;
}


int main()
{
    part1();
    part2();
    return 0;
}



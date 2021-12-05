#include <stdio.h>
#include <stdlib.h>

void part2()
{
    FILE *f;

    f = fopen("input.txt","r");

    int a=-1, b=-1, c=-1;
    int count = 0;
    int prev =-1;

    fscanf(f,"%d",&a);
    fscanf(f,"%d",&b);
    
    while (fscanf(f,"%d",&c)!=EOF)
    {

        if (prev==-1)
        {
            //printf("%d (N/A)\n",a+b+c);
        }
        else
        {
            if (prev>a+b+c)
            {
                //printf("%d (decreased)\n",a+b+c);
            }   
            else if (prev<a+b+c)
            {
                //printf("%d (increased)\n",a+b+c);
                count++;
            }
        }

        prev = a+b+c;
        a=b;
        b=c;
    }

    printf("Part 2: %d\n", count);
    

    return;
}

void part1()
{
    FILE *f;

    f = fopen("input.txt","r");
    
    int prev = -1, x = 0;
    int count = 0;

    while (fscanf(f,"%d",&x)!=EOF)
    {
        if (prev==-1)
        {
            //printf("%d (N/A)\n",x);
        }
        else
        {
            if (prev>x)
            {
                //printf("%d (decreased)\n",x);
            }   
            else if (prev<x)
            {
                //printf("%d (increased)\n",x);
                count++;
            }
        }

        prev = x;
        
    }

    printf("Part 1: %d\n", count);
    

    return;
}

int main()
{
    part1();
    part2();
    return 0;
}



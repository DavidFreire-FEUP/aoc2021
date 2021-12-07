#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct 
{
    unsigned int x[2];
    unsigned int y[2];
} Line;

void getBounds(unsigned int * minX,unsigned int * maxX,unsigned int * minY,unsigned int * maxY,Line* line, unsigned int qtd){
    unsigned int mx=INT_MAX,MX=0,my=INT_MAX,MY=0;
    for (size_t i = 0; i < qtd; i++)
    {
        mx = line[i].x[0]<mx ? line[i].x[0] : mx;
        mx = line[i].x[1]<mx ? line[i].x[1] : mx;

        MX = line[i].x[0]>MX ? line[i].x[0] : MX;
        MX = line[i].x[1]>MX ? line[i].x[1] : MX;

        my = line[i].y[0]<my ? line[i].y[0] : my;
        my = line[i].y[1]<my ? line[i].y[1] : my;

        MY = line[i].y[0]>MY ? line[i].y[0] : MY;
        MY = line[i].y[1]>MY ? line[i].y[1] : MY;
    }

    *minX = mx; *maxX = MX; *minY = my; *maxY = MY;

    return;
}

void printWindow(unsigned int X,unsigned int Y,unsigned int window[X][Y]){
    for (size_t i = 0; i < X; i++)
    {
        for (size_t j = 0; j < Y; j++)
        {
            if (window[i][j]==0)
            {
                printf(".");
            }
            else
            {
                printf("%d",window[i][j]);
            }
            
        }
        printf("\n");
        
    }
    
}

void solution(unsigned int part)
{
    FILE *f;

    f = fopen("input.txt","r");

    char buffer[128];
    unsigned int qtd_lines=0;

    while (fgets(buffer,128,f)!=NULL)
    {
        qtd_lines++;
    }

    rewind(f);
    
    Line line[qtd_lines];

    for (size_t i = 0; i < qtd_lines; i++)
    {
        fscanf(f,"%d,%d -> %d,%d", &line[i].x[0],&line[i].y[0],&line[i].x[1],&line[i].y[1]);
    }

    unsigned int minX,maxX,minY,maxY,x_axis_size,y_axis_size; 
    getBounds(&minX,&maxX,&minY,&maxY,line,qtd_lines);

    x_axis_size = maxX-minX+1;
    y_axis_size = maxY-minY+1;


    unsigned int window[y_axis_size][x_axis_size];
    
    for (size_t i = 0; i < y_axis_size; i++)
    {
        for (size_t j = 0; j < x_axis_size; j++)
        {
            window[i][j]=0;
        }
        
    }

    unsigned int start,end;
    unsigned int startX,endX,startY,endY;

    for (size_t i = 0; i < qtd_lines; i++)
    {
        if(line[i].x[0]==line[i].x[1]) // vertical line
        { 
            start = line[i].y[0]-minY;
            end = line[i].y[1]-minY;
            while (start!=end)
            {
                window[start][line[i].x[0]-minX]++;
                start = start>end ? start-1 : start+1;
                if(start==end){
                    window[start][line[i].x[0]-minX]++;
                }
            }
        }
        else if (line[i].y[0]==line[i].y[1]) // horizontal line
        {
            start = line[i].x[0]-minX;
            end = line[i].x[1]-minX;
            while (start!=end)
            {
                window[line[i].y[0]-minY][start]++;
                start = start>end ? start-1 : start+1;
                if(start==end){
                    window[line[i].y[0]-minY][start]++;
                }
            }
        } 
        else if(part == 2) // diagonal line, only for part 2
        {
            startX = line[i].x[0]-minX;
            startY = line[i].y[0]-minY;
            endX = line[i].x[1]-minX;
            endY = line[i].y[1]-minY;
            
            while (startX!=endX && startY!=endY)
            {
                window[startY][startX]++;
                startX = startX>endX ? startX-1 : startX+1;
                startY = startY>endY ? startY-1 : startY+1;
                if(startX==endX && startY==endY){
                    window[startY][startX]++;
                }
            }

        }
        
    }

    unsigned int overlap=0;

    //printWindow(y_axis_size,x_axis_size,window);

    for (size_t i = 0; i < y_axis_size; i++)
    {
        for (size_t j = 0; j < x_axis_size; j++)
        {
            if (window[i][j]>=2)
            {
                overlap++;
            }
        }
        
    }

   
    printf("Part %d: %d\n", part,overlap);

    
    return;
}

int main()
{
    solution(1);
    solution(2);
    return 0;
}
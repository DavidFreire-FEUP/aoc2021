#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef unsigned short int USINT;
typedef unsigned int UINT;
typedef unsigned long long int ULLI;

typedef struct {
    int origin_x;
    int origin_y;
    int size;
} Basin;

typedef struct {
    int x;
    int y;
} Point;

//#define MAP_COLUMNS 10
//#define MAP_ROWS 5

#define MAP_COLUMNS 100
#define MAP_ROWS 100

void part1()
{
    FILE *f;

    f = fopen("input.txt","r");

    char map[MAP_ROWS][MAP_COLUMNS];
    char line[MAP_COLUMNS];
    USINT counter=0;
    int riskFactor=0;

    for (size_t i = 0; fscanf(f,"%s",map[i])!=EOF; i++) {}

    for (size_t i = 0; i < MAP_ROWS; i++)
    {
        for (size_t j = 0; j < MAP_COLUMNS; j++)
        {
            if(i==0) // first row
            {
                if (j==0) // first element
                {
                    if (map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';

                }
                else if (j==MAP_COLUMNS-1) // last element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i+1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';
                }
                else // middle element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';

                }

            }
            else if (i==MAP_ROWS-1) // last row
            {
                if (j==0) // first element
                {
                    if (map[i][j]<map[i][j+1] && map[i][j]<map[i-1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';

                }
                else if (j==MAP_COLUMNS-1) // last element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i-1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';

                }
                else // middle element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i][j+1] && map[i][j]<map[i-1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';
                }
            }
            else // middle row
            {
                if (j==0) // first element
                {
                    if (map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j] && map[i][j]<map[i-1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';
  
                }
                else if (j==MAP_COLUMNS-1) // last element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i+1][j] && map[i][j]<map[i-1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';
  
                }
                else // middle element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j] && map[i][j]<map[i-1][j]) riskFactor += 1 + (int)map[i][j] - (int)'0';

                }
            }
        }
    }
    
    
    printf("Part 1: %d\n", riskFactor);
    return;
}


int basinSize(int x,int y,char map[MAP_ROWS][MAP_COLUMNS],Point *found_points, int size_found){
    int res=1;

    //printf("%d %d\n", x,y);

    for (size_t i = 0; i < size_found; i++)
    {
        if(found_points[i].x == x && found_points[i].y == y) return 0;
    }

    for (size_t i = 0; i < size_found; i++)
    {
        if(found_points[i].x == -1 && found_points[i].y == -1) {
            found_points[i].x = x;
            found_points[i].y = y;
            break;
        }
    }

    if(x==0){
        if (y==0)
        {
            if(map[x][y]<map[x][y+1] && map[x][y+1]<'9') res += basinSize(x,y+1,map,found_points,size_found);

            if (map[x][y]<map[x+1][y] && map[x+1][y]<'9') res += basinSize(x+1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y+1] || map[x][y+1]=='9') && (map[x][y]>map[x+1][y] || map[x+1][y]=='9')) return 1;

        }
        else if (y==MAP_COLUMNS-1)
        {
            if(map[x][y]<map[x][y-1] && map[x][y-1]<'9') res += basinSize(x,y-1,map,found_points,size_found);

            if (map[x][y]<map[x+1][y] && map[x+1][y]<'9') res += basinSize(x+1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y-1] || map[x][y-1]=='9') && (map[x][y]>map[x+1][y] || map[x+1][y]=='9')) return 1;
        }
        else 
        {
            if(map[x][y]<map[x][y+1] && map[x][y+1]<'9') res += basinSize(x,y+1,map,found_points,size_found);

            if(map[x][y]<map[x][y-1] && map[x][y-1]<'9') res += basinSize(x,y-1,map,found_points,size_found);

            if (map[x][y]<map[x+1][y] && map[x+1][y]<'9') res += basinSize(x+1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y+1] || map[x][y+1]=='9') && (map[x][y]>map[x][y-1] || map[x][y-1]=='9') && (map[x][y]>map[x+1][y] || map[x+1][y]=='9')) return 1;
        }
        
        
    }
    else if(x==MAP_ROWS-1)
    {
        if (y==0)
        {
            if(map[x][y]<map[x][y+1] && map[x][y+1]<'9') res += basinSize(x,y+1,map,found_points,size_found);

            if (map[x][y]<map[x-1][y] && map[x-1][y]<'9') res += basinSize(x-1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y+1] || map[x][y+1]=='9') && (map[x][y]>map[x-1][y] || map[x-1][y]=='9')) return 1;
        }
        else if (y==MAP_COLUMNS-1)
        {
            if(map[x][y]<map[x][y-1] && map[x][y-1]<'9') res += basinSize(x,y-1,map,found_points,size_found);

            if (map[x][y]<map[x-1][y] && map[x-1][y]<'9') res += basinSize(x-1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y-1] || map[x][y-1]=='9') && (map[x][y]>map[x-1][y] || map[x-1][y]=='9')) return 1;
        }
        else 
        {
            if(map[x][y]<map[x][y-1] && map[x][y-1]<'9') res += basinSize(x,y-1,map,found_points,size_found);

            if(map[x][y]<map[x][y+1] && map[x][y+1]<'9') res += basinSize(x,y+1,map,found_points,size_found);

            if (map[x][y]<map[x-1][y] && map[x-1][y]<'9') res += basinSize(x-1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y-1] || map[x][y-1]=='9') && (map[x][y]>map[x][y+1] || map[x][y+1]=='9') && (map[x][y]>map[x-1][y] || map[x-1][y]=='9')) return 1;
        }
    }
    else 
    {
        if (y==0)
        {
            if(map[x][y]<map[x][y+1] && map[x][y+1]<'9') res += basinSize(x,y+1,map,found_points,size_found);

            if (map[x][y]<map[x-1][y] && map[x-1][y]<'9') res += basinSize(x-1,y,map,found_points,size_found);

            if (map[x][y]<map[x+1][y] && map[x+1][y]<'9') res += basinSize(x+1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y+1] || map[x][y+1]=='9') && (map[x][y]>map[x-1][y] || map[x-1][y]=='9') && (map[x][y]>map[x+1][y] || map[x+1][y]=='9')) return 1;
        }
        else if (y==MAP_COLUMNS-1)
        {
            if(map[x][y]<map[x][y-1] && map[x][y-1]<'9') res += basinSize(x,y-1,map,found_points,size_found);

            if (map[x][y]<map[x-1][y] && map[x-1][y]<'9') res += basinSize(x-1,y,map,found_points,size_found);

            if (map[x][y]<map[x+1][y] && map[x+1][y]<'9') res += basinSize(x+1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y-1] || map[x][y-1]=='9') && (map[x][y]>map[x-1][y] || map[x-1][y]=='9') && (map[x][y]>map[x+1][y] || map[x+1][y]=='9')) return 1;
        }
        else 
        {
            if(map[x][y]<map[x][y+1] && map[x][y+1]<'9') res += basinSize(x,y+1,map,found_points,size_found);

            if(map[x][y]<map[x][y-1] && map[x][y-1]<'9') res += basinSize(x,y-1,map,found_points,size_found);

            if (map[x][y]<map[x-1][y] && map[x-1][y]<'9') res += basinSize(x-1,y,map,found_points,size_found);

            if (map[x][y]<map[x+1][y] && map[x+1][y]<'9') res += basinSize(x+1,y,map,found_points,size_found);

            if((map[x][y]>map[x][y-1] || map[x][y-1]=='9') && (map[x][y]>map[x][y+1] || map[x][y+1]=='9') && (map[x][y]>map[x-1][y] || map[x-1][y]=='9') && (map[x][y]>map[x+1][y] || map[x+1][y]=='9')) return 1;
        }
    }
    

    return res;
}

void part2()
{
    FILE *f;

    f = fopen("input.txt","r");

    char map[MAP_ROWS][MAP_COLUMNS];
    USINT low_points[MAP_ROWS][MAP_COLUMNS];

    for (size_t i = 0; i < MAP_ROWS; i++)
    {
        for (size_t j = 0; j < MAP_COLUMNS; j++)
        {
            low_points[i][j]=0;
        }
        
    }
    
    char line[MAP_COLUMNS];
    USINT counter=0;
    int basin_count=0;

    for (size_t i = 0; fscanf(f,"%s",map[i])!=EOF; i++) {}

    for (size_t i = 0; i < MAP_ROWS; i++)
    {
        for (size_t j = 0; j < MAP_COLUMNS; j++)
        {
            if(i==0) // first row
            {
                if (j==0) // first element
                {
                    if (map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j])
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }
                     

                }
                else if (j==MAP_COLUMNS-1) // last element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i+1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }
                }
                else // middle element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }
                }
            }
            else if (i==MAP_ROWS-1) // last row
            {
                if (j==0) // first element
                {
                    if (map[i][j]<map[i][j+1] && map[i][j]<map[i-1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }

                }
                else if (j==MAP_COLUMNS-1) // last element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i-1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }

                }
                else // middle element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i][j+1] && map[i][j]<map[i-1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }
                }
            }
            else // middle row
            {
                if (j==0) // first element
                {
                    if (map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j] && map[i][j]<map[i-1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }
  
                }
                else if (j==MAP_COLUMNS-1) // last element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i+1][j] && map[i][j]<map[i-1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }
  
                }
                else // middle element
                {
                    if (map[i][j]<map[i][j-1] && map[i][j]<map[i][j+1] && map[i][j]<map[i+1][j] && map[i][j]<map[i-1][j]) 
                    {
                        low_points[i][j]=1;
                        basin_count++;
                    }

                }
            }
        }
    }

    Basin basin[basin_count];
    Point *found_points[basin_count];
    for (size_t i = 0; i < basin_count; i++)
    {
        found_points[i]=(Point*)malloc(sizeof(Point)*MAP_ROWS*MAP_COLUMNS);
        for (size_t j = 0; j < MAP_ROWS*MAP_COLUMNS; j++)
        {
            found_points[i][j].x = -1;
            found_points[i][j].y = -1;
        }
        
    }
    
    basin_count=0;

    for (size_t i = 0; i < MAP_ROWS; i++)
    {
        for (size_t j = 0; j < MAP_COLUMNS; j++)
        {
            if (low_points[i][j])
            {
                basin[basin_count].origin_x=i;
                basin[basin_count].origin_y=j;
                basin[basin_count].size=0;
                basin_count++;
            }   
        }
    }

    int x,y;

    for (size_t i = 0; i < basin_count; i++)
    {
        x=basin[i].origin_x;
        y=basin[i].origin_y;
        basin[i].size = basinSize(x,y,map,found_points[i],MAP_ROWS*MAP_COLUMNS);
        //printf("(%d,%d): size=%d\n",x,y,basin[i].size);
    }

    int checked[basin_count]; //used for ordering
    for (size_t i = 0; i < basin_count; i++)
    {
        free(found_points[i]);
        checked[i]=0;
    }

    int max=0, pos=0;
    int result=1;
    for (size_t i = 0; i < 3; i++)
    {
        max = 0;
        for (size_t j = 0; j < basin_count; j++)
        {
            if (basin[j].size>max && checked[j]==0)
            {
                max=basin[j].size;
                pos=j;
            }
        }
        checked[pos]=1;
        result *= max;
    }
    
    printf("Part 2: %d\n", result);
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
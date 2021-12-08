#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef unsigned short int USINT;
typedef unsigned int UINT;
typedef unsigned long long int ULLI;

void part1()
{
    FILE *f;

    f = fopen("input.txt","r");

    char input[10][64];
    char output[4][64];
    size_t len;
    USINT count=0;

    while (fscanf(f,"%s %s %s %s %s %s %s %s %s %s | %s %s %s %s",input[0],input[1],input[2],input[3],input[4],input[5],input[6],input[7],input[8],input[9],output[0],output[1],output[2],output[3])!= EOF)
    {
        for (size_t i = 0; i < 4; i++)
        {
            len = strlen(output[i]);
            if (len==2 || len==3 || len==4 || len==7)
            {
                count++;
            }
            
        }
        
    }
    
    printf("Part 1: %d\n", count);
    return;
}

short int displayToDigit(char *digit){
    short int code=0;
    for (size_t i = 0; i < strlen(digit); i++)
    {
        code += 1<<(6-(int)digit[i]+97);
    }

    switch (code)
    {
    case 0x7E:
        return 0;
        break;
    case 0x30:
        return 1;
        break;
    case 0x6D:
        return 2;
        break;
    case 0x79:
        return 3;
        break;
    case 0x33:
        return 4;
        break;
    case 0x5B:
        return 5;
        break;
    case 0x5F:
        return 6;
        break;
    case 0x70:
        return 7;
        break;
    case 0x7F:
        return 8;
        break;
    case 0x7B:
        return 9;
        break;
    default:
        return -1;
        break;
    }
    
}

void part2()
{
    FILE *f;

    f = fopen("input.txt","r");

    char input[10][64];
    char output[4][64];
    char map[8]={"abcdefg"};
    char maps[8][8]={"abcdefg","abcdefg","abcdefg","abcdefg","abcdefg","abcdefg","abcdefg","abcdefg"};
    
    char test[8];
    size_t len;
    USINT count=0,badmap;
    char auxc;
    USINT map_to_use=0;
    int out=0,result=0;
    
    while (fscanf(f,"%s %s %s %s %s %s %s %s %s %s | %s %s %s %s",input[0],input[1],input[2],input[3],input[4],input[5],input[6],input[7],input[8],input[9],output[0],output[1],output[2],output[3])!= EOF)
    {
        for (size_t i = 0; i < 10; i++)
        {
            if (strlen(input[i])==2) // if its a 1
            {
                map[1]=input[i][0];
                map[2]=input[i][1];
            }
        }

        for (size_t i = 0; i < 10; i++)
        {
            if (strlen(input[i])==3) // if its a 7
            {
                for (size_t j = 0; j < 3; j++) // check char different than the ones in one
                {
                    if (input[i][j]!=map[1] && input[i][j]!=map[2])
                    {   
                        map[0]=input[i][j];
                    }
                }
            }
        }

        for (size_t i = 0; i < 10; i++)
        {
            if (strlen(input[i])==4) // if its a 4
            {
                for (size_t j = 0; j < 4; j++) 
                {
                    if (input[i][j]!=map[1] && input[i][j]!=map[2])
                    {   
                        map[5]=input[i][j];
                    }
                }
                for (size_t j = 0; j < 4; j++) 
                {
                    if (input[i][j]!=map[1] && input[i][j]!=map[2] && input[i][j]!=map[5])
                    {   
                        map[6]=input[i][j];
                    }
                }
            }
        }

        for (size_t i = 0; i < 10; i++)
        {
            if (strlen(input[i])==7) // if its a 8
            {
                for (size_t j = 0; j < 7; j++) 
                {
                    if (input[i][j]!=map[0] && input[i][j]!=map[1] && input[i][j]!=map[2] && input[i][j]!=map[5] && input[i][j]!=map[6])
                    {   
                        map[3]=input[i][j];
                    }
                }
                for (size_t j = 0; j < 7; j++) 
                {
                    if (input[i][j]!=map[0] && input[i][j]!=map[1] && input[i][j]!=map[2] && input[i][j]!=map[3] && input[i][j]!=map[5] && input[i][j]!=map[6])
                    {   
                        map[4]=input[i][j];
                    }
                }
            }
        }
        
        USINT remap=0;
        // create combination maps
        for (size_t i = 0; i < 8; i++)
        {
            strcpy(maps[i],map);
            switch (i)
            {
                case 1: // switch 1 segments
                    auxc = maps[i][2];
                    maps[i][2] = maps[i][1];
                    maps[i][1] = auxc;
                    break;
                case 2: // switch 4 segments
                    auxc = maps[i][5];
                    maps[i][5] = maps[i][6];
                    maps[i][6] = auxc;
                    break;
                case 3: // switch 8 segments
                    auxc = maps[i][3];
                    maps[i][3] = maps[i][4];
                    maps[i][4] = auxc;
                    break;
                case 4: //switch 1,4
                    auxc = maps[i][2];
                    maps[i][2] = maps[i][1];
                    maps[i][1] = auxc;
                    auxc = maps[i][5];
                    maps[i][5] = maps[i][6];
                    maps[i][6] = auxc;
                    break;
                case 5: //switch 1,8
                    auxc = maps[i][2];
                    maps[i][2] = maps[i][1];
                    maps[i][1] = auxc;
                    auxc = maps[i][3];
                    maps[i][3] = maps[i][4];
                    maps[i][4] = auxc;
                    break;
                case 6: //switch 4,8
                    auxc = maps[i][5];
                    maps[i][5] = maps[i][6];
                    maps[i][6] = auxc;
                    auxc = maps[i][3];
                    maps[i][3] = maps[i][4];
                    maps[i][4] = auxc;
                    break;
                case 7: //switch 1,4,8
                    auxc = maps[i][2];
                    maps[i][2] = maps[i][1];
                    maps[i][1] = auxc;
                    auxc = maps[i][5];
                    maps[i][5] = maps[i][6];
                    maps[i][6] = auxc;
                    auxc = maps[i][3];
                    maps[i][3] = maps[i][4];
                    maps[i][4] = auxc;
                    break;
                default:
                    break;
            }
        }
        
        // test combination maps
        for (size_t i = 0; i < 8; i++)
        {
            badmap=0;
            for (size_t l = 0; l < 10; l++)
            {
                len = strlen(input[l]);
                if (len!=2 && len!=3 && len!=4 && len!=7)
                {
                    strcpy(test,input[l]);
                    for (size_t j = 0; j < len; j++)
                    {
                        for (size_t k = 0; k < 8; k++)
                        {
                            if (test[j]==maps[i][k])
                            {
                                test[j] = (char)(97+k);
                                break;
                            }
                        }
                    }
                    if(displayToDigit(test)==-1) badmap=1;
                }
                
            }

            if (!badmap) map_to_use=i;

        }

        out=0;
        for (size_t i = 0; i < 4; i++)
        {
            strcpy(test,output[i]);
            for (size_t j = 0; j < strlen(test); j++)
            {
                for (size_t k = 0; k < 8; k++)
                {
                    if (test[j]==maps[map_to_use][k])
                    {
                        test[j] = (char)(97+k);
                        break;
                    }
                }
            }
            out+=displayToDigit(test)*pow(10,3-i);
        }
        result+=out;
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
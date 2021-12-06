#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define FRAME_HEIGHT 5
#define FRAME_WIDTH 5

typedef struct 
{
    int numbers[FRAME_HEIGHT][FRAME_WIDTH];
    int marked_numbers[FRAME_HEIGHT][FRAME_WIDTH];
    int moves_to_win;
    int last_called;
} Frame;


void printBoard(int b[FRAME_HEIGHT][FRAME_WIDTH]){
    for (size_t i = 0; i < FRAME_HEIGHT; i++)
    {
        for (size_t j = 0; j < FRAME_WIDTH; j++)
        {
            printf("%d ", b[i][j]);
        }
        printf("\n");
        
    }
    
}


int isWinner(int marked[FRAME_HEIGHT][FRAME_WIDTH]){
    int count;
    for (size_t i = 0; i < FRAME_HEIGHT; i++)
    {
        count=0;
        for (size_t j = 0; j < FRAME_WIDTH; j++)
        {
            if(marked[i][j]){
                count++;
            }
        }
        if(count==FRAME_WIDTH) return 1;
    }

    for (size_t i = 0; i < FRAME_HEIGHT; i++)
    {
        count=0;
        for (size_t j = 0; j < FRAME_WIDTH; j++)
        {
            if(marked[j][i]){
                count++;
            }
        }
        if(count==FRAME_WIDTH) return 1;
    }

    return 0;
}

int getScore(Frame f){
    int sum=0;
    for (size_t i = 0; i < FRAME_HEIGHT; i++)
    {
        for (size_t j = 0; j < FRAME_WIDTH; j++)
        {
            if (f.marked_numbers[i][j]==0)
            {
                sum+=f.numbers[i][j];
            }
        }
        
    }

    return sum*f.last_called;
}

void part1()
{
    FILE *f;

    f = fopen("input.txt","r");

    char numbers[1024];
    char str[1];
    int num_frames=0;

    /// Count frames
    fgets(numbers,1024,f);
    fgets(str,1,f); // skip a line
    while (fgets(numbers,1024,f)!=NULL)
    {
        num_frames++;
    }
    num_frames = num_frames/6;
    //printf("Ammount of frames: %d\n",num_frames);
    ///


    Frame frame[num_frames];
    for (size_t i = 0; i < num_frames; i++)
    {
        frame[i].moves_to_win = 0;
        for (size_t n = 0; n < FRAME_WIDTH; n++)
        {
            for (size_t m = 0; m < FRAME_HEIGHT; m++)
            {
                frame[i].marked_numbers[n][m] = 0;
            }
        
        }
    }

    /// Store Frames
    rewind(f);
    fgets(numbers,1024,f);
    fgets(str,1,f); // skip a line
    for (size_t i = 0; i < num_frames; i++)
    {
        for (size_t j = 0; j < FRAME_WIDTH; j++)
        {
            fscanf(f,"%d %d %d %d %d",&frame[i].numbers[j][0],&frame[i].numbers[j][1],&frame[i].numbers[j][2],&frame[i].numbers[j][3],&frame[i].numbers[j][4]);
        }
    }
    fclose(f);
    ///

    char *token;
    int current_number;
    int win=0;
    int found=0;
    char auxstring[1024];
    for (size_t i = 0; i < num_frames; i++)
    {
        strcpy(auxstring,numbers);
        token = strtok(auxstring,",");
        while (token!=NULL)
        {
            current_number = atoi(token);
            found=0;
            for (size_t n = 0; n < FRAME_WIDTH; n++)
            {
                for (size_t m = 0; m < FRAME_HEIGHT; m++)
                {
                    if (isWinner(frame[i].marked_numbers))
                    {
                        win=1;
                        break;
                    }
                    else if (frame[i].numbers[n][m] == current_number)
                    {
                        frame[i].last_called=current_number;
                        frame[i].marked_numbers[n][m]=1;
                        found=1;
                        break;
                    }
                    
                }
                if(win || found) break;
                
            }
            
            if(win){
                win=0;
                break;
            }

            frame[i].moves_to_win++;
            
            token = strtok(NULL,",");
        }
        
    }
    
    int min=INT_MAX;
    int winning_frame;
    for (size_t i = 0; i < num_frames; i++)
    {
        
        if (frame[i].moves_to_win < min)
        {
            min=frame[i].moves_to_win;
            winning_frame = i;
        }
    }

    printf("Part 1: %d\n", getScore(frame[winning_frame]));
    
    return;
}

void part2()
{
    FILE *f;

    f = fopen("input.txt","r");

    char numbers[1024];
    char str[1];
    int num_frames=0;

    /// Count frames
    fgets(numbers,1024,f);
    fgets(str,1,f); // skip a line
    while (fgets(numbers,1024,f)!=NULL)
    {
        num_frames++;
    }
    num_frames = num_frames/6;
    ///


    Frame frame[num_frames];
    for (size_t i = 0; i < num_frames; i++)
    {
        frame[i].moves_to_win = 0;
        for (size_t n = 0; n < FRAME_WIDTH; n++)
        {
            for (size_t m = 0; m < FRAME_HEIGHT; m++)
            {
                frame[i].marked_numbers[n][m] = 0;
            }
        
        }
    }

    /// Store Frames
    rewind(f);
    fgets(numbers,1024,f);
    fgets(str,1,f); // skip a line
    for (size_t i = 0; i < num_frames; i++)
    {
        for (size_t j = 0; j < FRAME_WIDTH; j++)
        {
            fscanf(f,"%d %d %d %d %d",&frame[i].numbers[j][0],&frame[i].numbers[j][1],&frame[i].numbers[j][2],&frame[i].numbers[j][3],&frame[i].numbers[j][4]);
        }
    }
    fclose(f);
    ///

    char *token;
    int current_number;
    int win=0;
    int found=0;
    char auxstring[1024];
    for (size_t i = 0; i < num_frames; i++)
    {
        strcpy(auxstring,numbers);
        token = strtok(auxstring,",");
        while (token!=NULL)
        {
            current_number = atoi(token);
            found=0;
            for (size_t n = 0; n < FRAME_WIDTH; n++)
            {
                for (size_t m = 0; m < FRAME_HEIGHT; m++)
                {
                    if (isWinner(frame[i].marked_numbers))
                    {
                        win=1;
                        break;
                    }
                    else if (frame[i].numbers[n][m] == current_number)
                    {
                        
                        frame[i].last_called=current_number;
                        frame[i].marked_numbers[n][m]=1;
                        found=1;
                        break;
                    }
                    
                }
                if(win || found) break;
                
            }
            
            if(win){
                win=0;
                break;
            }

            frame[i].moves_to_win++;
            
            token = strtok(NULL,",");
        }
        
    }
    
    int max=0;
    int losing_frame;
    for (size_t i = 0; i < num_frames; i++)
    {
        if (frame[i].moves_to_win > max)
        {
            max=frame[i].moves_to_win;
            losing_frame = i;
        }
    }

    printf("Part 2: %d\n", getScore(frame[losing_frame]));
    
    return;
}

int main()
{
    part1();
    part2();
    return 0;
}
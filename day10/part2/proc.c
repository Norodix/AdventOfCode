#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define INPUTFILE "input.txt"
#define BUFFERSIZE 100

static char delim[] = " \t\r\n\v\f";
static int PC = 0; //program counter
static int reg_X = 1;
static int accumulator = 0;

#define SCREENWIDTH  40
#define SCREENHEIGHT  6

static char screen[SCREENHEIGHT][SCREENWIDTH];

void increment_PC(){
    int col = PC % SCREENWIDTH;
    char c = ' ';
    if(abs(col-reg_X) <= 1) {
        c = '#';
    }
    screen[PC/SCREENWIDTH][PC%SCREENWIDTH] = c;
    PC++;
}


int main(){
    FILE *f = fopen(INPUTFILE, "r");
    char line[BUFFERSIZE];


    while(!feof(f)){
        if (fgets(line, BUFFERSIZE, f)){
            char* instruction = strtok(line, delim);

            if(!strcmp(instruction, "addx")){
                printf("Add instruction\t");
                //get argument
                char* arg = strtok(NULL, delim);
                int addnum = atoi(arg);
                printf("%i\n", addnum);
                increment_PC();
                increment_PC();
                reg_X += addnum;
            }
            else if(!strcmp(instruction, "noop")){
                increment_PC();
                printf("No operation\n");
            }
            else {
                printf("Unknown instruction\n");
                return -1;
            }
        }

    }
    printf("Register X: %i\n", reg_X);
    printf("Accumulator: %i\n", accumulator);

    for(int i = 0; i<SCREENHEIGHT; i++){
        for(int j = 0; j<SCREENWIDTH; j++){
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}
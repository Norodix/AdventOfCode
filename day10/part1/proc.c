#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define INPUTFILE "testinput.txt"
#define BUFFERSIZE 100

static char delim[] = " \t\r\n\v\f";
static int PC = 0; //program counter
static int reg_X = 1;
static char screen[6][40] = {'.'};
static int accumulator = 0;

void increment_PC(){
    PC++;
    if (PC % 40 == 20){
        accumulator += PC * reg_X;
    }
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
}
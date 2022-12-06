#include <stdio.h>
#include <stdint.h>

#define INPUTFILE "input.txt"

//use 4 for part1 and 14 for part2
#define SEQUENCELENGTH (14)

int has_duplicate(char* buffer){
    for (int i = 0; i<SEQUENCELENGTH-1; i++){
        for (int j = i+1; j<SEQUENCELENGTH; j++){
            if (buffer[i] == buffer[j]) return 1;
        }
    }
    return 0;
}


int main(){
    char circularbuffer[SEQUENCELENGTH];

    FILE* f = fopen(INPUTFILE, "r");
    
    //initialize buffer with first chars
    for (int i = 0; i<SEQUENCELENGTH; i++){
        circularbuffer[i] = fgetc(f);
    }
    int index = SEQUENCELENGTH;

    
    while(!feof(f)){
        if (!has_duplicate(circularbuffer)) break;
        circularbuffer[index++ % SEQUENCELENGTH] = fgetc(f);
    }
    printf("%c%c%c%c at index: %i\n", circularbuffer[0],circularbuffer[1],circularbuffer[2],circularbuffer[3], index);
}

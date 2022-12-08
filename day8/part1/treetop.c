#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define INPUTFILE "input.txt"
#define BUFFERSIZE 1024

//number of rows, columns size, rc coordinate
int is_visible(int** forest, int rows, int cols, int r, int c){
    int visible = 0U;
    int v;
    
    //visible from left
    v = 1;
    for(int i=0; i<c; i++){
        if (forest[r][i] >= forest[r][c]) v = 0;
    }
    visible |= v;

    //visible from right
    v = 1;
    for(int i=c+1; i<cols; i++){
        if (forest[r][i] >= forest[r][c]) v = 0;
    }
    visible |= v;

    //visible from top
    v = 1;
    for(int i=0; i<r; i++){
        if (forest[i][c] >= forest[r][c]) v = 0;
    }
    visible |= v;

    //visible from bottom
    v = 1;
    for(int i=r+1; i<rows; i++){
        if (forest[i][c] >= forest[r][c]) v = 0;
    }
    visible |= v;

    return visible;
}


int main(){
    int rows = 0, cols = 0;
    FILE* f = fopen(INPUTFILE, "r");

    char line[BUFFERSIZE];

    while(!feof(f)){
        fgets(line, BUFFERSIZE, f);
        rows++;
    }
    printf("Rows: %i\n", rows);
    rewind(f);
    fgets(line, BUFFERSIZE, f);
    cols = strcspn(line, "\n"); //get number of bytes before newline
    printf("Cols: %i\n", cols);
    rewind(f);
    
    //allocate memory for rows and colums
    int** forest = (int**)malloc(rows * sizeof(int*));
    for(int r = 0; r<rows; r++){
        forest[r] = (int*)malloc(cols * sizeof(int));
    }

    //read the values to the 2D array forest
    int r = 0;
    while(!feof(f)){
        fgets(line, BUFFERSIZE, f);
        for(int c=0; c<cols; c++){
            forest[r][c] = line[c] - '0';
        }
        r++;
    }
    /* print the read 2d array
    for (int r = 0; r<rows; r++){
        for(int c=0; c<cols; c++){
            printf("%i ", forest[r][c]);
        }
        printf("\n");
    }
    */
    
    int visible_trees = 0;
    for (int r = 0; r<rows; r++){
        for(int c=0; c<cols; c++){
            if (is_visible(forest, rows, cols, r, c)){
                visible_trees++;
                printf("\033[0;32m%i", forest[r][c]);
            }
            else printf("\033[0;37m%i", forest[r][c]);
        }
        printf("\n");
    }
    
    printf("Visible trees: %i\n", visible_trees);

}
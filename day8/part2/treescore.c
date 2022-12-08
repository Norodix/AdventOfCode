#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define INPUTFILE "input.txt"
#define BUFFERSIZE 1024

int score_up(int** forest, int rows, int cols, int r, int c){
    int score = 0;
    for(int row = r-1; row >= 0; row--){
        score++;
        if (forest[row][c] >= forest[r][c]) break;
    }
    return score;
}

int score_down(int** forest, int rows, int cols, int r, int c){
    int score = 0;
    for(int row = r+1; row < rows; row++){
        score++;
        if (forest[row][c] >= forest[r][c]) break;
    }
    return score;
}

int score_left(int** forest, int rows, int cols, int r, int c){
    int score = 0;
    for(int col = c-1; col >= 0; col--){
        score++;
        if (forest[r][col] >= forest[r][c]) break;
    }
    return score;
}

int score_right(int** forest, int rows, int cols, int r, int c){
    int score = 0;
    for(int col = c+1; col < cols; col++){
        score++;
        if (forest[r][col] >= forest[r][c]) break;
    }
    return score;
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
    int maxscore = 0;
    for (int r = 0; r<rows; r++){
        for(int c=0; c<cols; c++){
            int score = score_up(forest, rows, cols, r, c)   * \
                        score_down(forest, rows, cols, r, c) * \
                        score_left(forest, rows, cols, r, c) * \
                        score_right(forest, rows, cols, r, c);
            maxscore = score > maxscore ? score : maxscore;
        }
    }

    printf("Maximum score for tree: %i\n", maxscore);
}
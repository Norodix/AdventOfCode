#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define INPUTFILE "input.txt"
#define BUFFERSIZE 1024

int rows = 0, cols = 0;

typedef struct square{
    int row, col;
    int height;
    int visited;
    int is_target;
    struct square* previous;
} square;

void print_grid(square** grid){
    /* print the read 2d array*/
    for (int r = 0; r<rows; r++){
        for(int c=0; c<cols; c++){
            if (grid[r][c].visited){
                printf(".");
            }
            else {
                printf("#");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int is_valid_step(square** grid, int row, int col, int h_from){
    // check if not visited already
    if (row <     0) return 0;
    if (row >= rows) return 0;
    if (col <     0) return 0;
    if (col >= cols) return 0;

    //check if not visited
    if (grid[row][col].visited) return 0;
    
    // check if can move there
    if (h_from+1 < grid[row][col].height) return 0;
    
    // if nothing prevents it its good
    return 1;    
}


int main(){

    // READ IN GRID FROM FILE
    FILE* f = fopen(INPUTFILE, "r");
    if(f == NULL){
        printf("Could not open file\n");
        exit(-1);
    }

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
    
    // CREATE TERRAIN
    square** mountain = (square**)malloc(rows * sizeof(square*));
    for(int r = 0; r<rows; r++){
        mountain[r] = (square*)malloc(cols * sizeof(square));
    }

    // create a queue
    square **queue = (square**)malloc(sizeof(square*) * rows * cols);
    int q_i = 0, q_end = 0;

    // read the values to the 2D array
    int r = 0;
    while(!feof(f)){
        fgets(line, BUFFERSIZE, f);
        for(int c=0; c<cols; c++){
            
            mountain[r][c].row = r;
            mountain[r][c].col = c;
            mountain[r][c].visited = 0;
            mountain[r][c].is_target = 0;
            mountain[r][c].previous = NULL;

            int h = 0;
            switch (line[c]){
            case 'S':
                // This is the start position
                h = 0;
                mountain[r][c].visited = 1;
                queue[0] = &mountain[r][c];
                break;
            case 'E':
                h = 'z' - 'a';
                mountain[r][c].is_target = 1;
                break;
            default:
                h = line[c] - 'a';
            }

            mountain[r][c].height = h;
        }
        r++;
    }

    /* print the read 2d array*/
    // for (int r = 0; r<rows; r++){
    //     for(int c=0; c<cols; c++){
    //         if(mountain[r][c].is_target) printf("%c", 'E');
    //         else if(mountain[r][c].visited) printf("%c", 'S');
    //         else printf("%c", 'a' + mountain[r][c].height);
    //     }
    //     printf("\n");
    // }



    // Breadth first search
    square* s;
    while (q_i <= rows*cols){
        // check neighbours are valid positions
        print_grid(mountain);
        //sleep(1);
        s = queue[q_i++];
        
        if (s->is_target) break;

        if (is_valid_step(mountain, s->row - 1, s->col, s->height)){
            // if all ok, move there, set visited, set previous and add to queue
            queue[++q_end] = &mountain[s->row - 1][s->col];
            queue[q_end]->visited = 1;
            queue[q_end]->previous = s;
        }
        if (is_valid_step(mountain, s->row + 1, s->col, s->height)){
            // if all ok, move there, set visited, set previous and add to queue
            queue[++q_end] = &mountain[s->row + 1][s->col];
            queue[q_end]->visited = 1;
            queue[q_end]->previous = s;
        }
        if (is_valid_step(mountain, s->row, s->col - 1, s->height)){
            // if all ok, move there, set visited, set previous and add to queue
            queue[++q_end] = &mountain[s->row][s->col - 1];
            queue[q_end]->visited = 1;
            queue[q_end]->previous = s;
        }
        if (is_valid_step(mountain, s->row, s->col + 1, s->height)){
            // if all ok, move there, set visited, set previous and add to queue
            queue[++q_end] = &mountain[s->row][s->col + 1];
            queue[q_end]->visited = 1;
            queue[q_end]->previous = s;
        }
    }

    int steps = 0;
    while(s->previous != NULL)
    {
        steps++;
        s = s->previous;
    }
    printf("Number of steps taken: %i\n", steps);
}
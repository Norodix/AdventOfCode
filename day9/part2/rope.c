#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUTFILE "input.txt"
#define BUFFERSIZE 10
#define SEGMENTS 10
#define LAST_SEGMENT (SEGMENTS - 1)

typedef struct point{
    int x;
    int y;
}point;

int sign(int x){
    if (x>0) return 1;
    if (x<0) return -1;
    return 0;
}

void follow(point head, point* tail){
    if (head.x == tail->x){
        //same column
        int delta = head.y - tail->y;
        if(abs(delta) >= 2){
            tail->y += sign(delta);
        }
    }
    else if (head.y == tail->y){
        //same row
        int delta = head.x - tail->x;
        if(abs(delta) >= 2){
            tail->x += sign(delta);
        }
    }
    else {
        //diagonal
        int deltay = head.y - tail->y;
        int deltax = head.x - tail->x;
        if (abs(deltay) + abs(deltax) > 2){
            tail->x += sign(deltax);
            tail->y += sign(deltay);
        }
    }
}

int count_unique_points(point* points, int len){
    int count = len;
    for(int i = 0; i<len; i++){
        for(int j = i+1; j<len; j++){
            if (points[i].x == points[j].x && points[i].y == points[j].y){
                count--;
                break;
            }
        }
    }
    return count;
}

int main(){
    FILE *f = fopen(INPUTFILE, "r");

    char line[BUFFERSIZE];
    int steps_num = 0;

    while(!feof(f)){
        fgets(line, BUFFERSIZE, f);
        steps_num += atoi(line + 1);
    }

    printf("Number of steps: %i\n", steps_num);
    rewind(f);

    point* steps = (point*) malloc((steps_num+1) * sizeof(point));
    int steps_index = 0;
    point segments[SEGMENTS];
    for (int i=0; i<SEGMENTS; i++){
        segments[i].x = 0;
        segments[i].y = 0;
    }

    

    while(!feof(f)){
        fgets(line, BUFFERSIZE, f);
        int num = atoi(line + 1);  //number of repeats
        point head_step = {0, 0};
        switch (line[0]){
            case 'L':
                head_step.x = - 1;
                break;
            case 'R':
                head_step.x =   1;
                break;
            case 'D':
                head_step.y = - 1;
                break;
            case 'U':
                head_step.y =   1;
                break;
        }

        for(int i = 0; i<num; i++){
            segments[0].x += head_step.x;
            segments[0].y += head_step.y;

            for (int j=0; j<SEGMENTS-1; j++){
                follow(segments[j], &segments[j + 1]);
            }
            steps[++steps_index] = segments[LAST_SEGMENT];
        }
    }
    for (int i = 0; i < steps_num+1; i++){
        //printf("Step %i: %i, %i\n", i+1, steps[i].x, steps[i].y);
    }

    printf("Number of places touched by tail is: %i\n", count_unique_points(steps, steps_num+1));
}
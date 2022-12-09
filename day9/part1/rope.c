#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUTFILE "input.txt"
#define BUFFERSIZE 10

typedef struct point{
    int x;
    int y;
}point;

void follow(point head, point* tail){
    if (abs(head.x - tail->x) >=2){
        tail->y = head.y;
        tail->x = ((head.x + tail->x) / 2.0);
    }
    else if (abs(head.y - tail->y) >=2){
        tail->x = head.x;
        tail->y = ((head.y + tail->y) / 2.0);
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
    point head = {0, 0}, tail = {0, 0};

    steps[0] = tail;

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
            head.x += head_step.x;
            head.y += head_step.y;
            follow(head, &tail);
            steps[++steps_index] = tail;
        }
    }
    for (int i = 0; i < steps_num+1; i++){
        //printf("Step %i: %i, %i\n", i+1, steps[i].x, steps[i].y);
    }

    printf("Number of places touched by tail is: %i\n", count_unique_points(steps, steps_num+1));
}
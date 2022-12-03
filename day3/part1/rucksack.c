#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

char fileName[] = "input.txt";

char printHelp[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define MAXBUFF 1024


void rucksack2flags(char* rucksack, uint64_t* left, uint64_t* right){
	int len = strlen(rucksack);
	*left = 0;
	*right = 0;
	for(int i = 0; i < len; i++){
		int priority = -1;
		if (rucksack[i] <= 'z' && rucksack[i] >= 'a'){
			priority = rucksack[i] - 'a';
		}
		else if (rucksack[i] <= 'Z' && rucksack[i] >= 'A'){
			priority = rucksack[i] - 'A' + 26;
		}
		else continue;

		if (i<len/2){
			*left |= 1UL<<priority;
		}
		else{
			*right |= 1UL<<priority;
		}
	}
}


int main(){
	FILE* inputFile = fopen(fileName, "r");
	char line[MAXBUFF+1];
	uint64_t left, right, sum = 0;
	while (fgets(line, MAXBUFF, inputFile)){
		rucksack2flags(line, &left, &right);	
		//printf("LEFT: %lx\t RIGHT: %lx\n", left, right);
		uint8_t index_1 = ffsll(left&right);
		if (index_1 > 0){
		//	printf("Same is: %c\n", printHelp[index-1]); 
			sum += index_1;
		}
		//return 0;
	}
	printf("Sum of priorities: %li\n", sum);
}

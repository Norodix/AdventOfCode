#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

char fileName[] = "input.txt";

char printHelp[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

#define MAXBUFF 1024


uint64_t rucksack2flag(char* rucksack){
	int len = strlen(rucksack);
	uint64_t flag = 0;
	for(int i = 0; i < len; i++){
		int priority = -1;
		if (rucksack[i] <= 'z' && rucksack[i] >= 'a'){
			priority = rucksack[i] - 'a';
		}
		else if (rucksack[i] <= 'Z' && rucksack[i] >= 'A'){
			priority = rucksack[i] - 'A' + 26;
		}
		else continue;

		flag |= 1UL<<priority;
	}
	return flag;
}


int main(){
	FILE* inputFile = fopen(fileName, "r");
	char line1[MAXBUFF+1];
	char line2[MAXBUFF+1];
	char line3[MAXBUFF+1];
	uint64_t sum = 0;

	while (1){
		if (fgets(line1, MAXBUFF, inputFile) == NULL) break;
		if (fgets(line2, MAXBUFF, inputFile) == NULL) break;
		if (fgets(line3, MAXBUFF, inputFile) == NULL) break;

		uint64_t ruck1 = rucksack2flag(line1);	
		uint64_t ruck2 = rucksack2flag(line2);	
		uint64_t ruck3 = rucksack2flag(line3);	
		uint8_t index_1 = ffsll(ruck1 & ruck2 & ruck3);
		if (index_1 > 0){
			sum += index_1;
		}
	}
	printf("Sum of priorities: %li\n", sum);
}

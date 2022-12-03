#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(){
	uint64_t sum = 0;
	uint64_t sum_max = 0;
	FILE *file = fopen("input.txt", "r");
	uint64_t num;
	char line[100];

	
	while(fgets(line, 100, file)){
		if (line[0] == '\n'){
			if (sum > sum_max) sum_max = sum;
			sum = 0;
		}
		else{
			sscanf(line, "%li\n", &num);
			sum += num;
		}
	}
	printf("Maximum: %li", sum_max);
		
	
}

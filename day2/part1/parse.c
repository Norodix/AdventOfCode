#include <stdio.h>
#include <stdint.h>

char fileName[] = "input.txt";

#define PLAYER_ROCK ('X')
#define ELF_ROCK ('A')


int main(){
	FILE* inputFile = fopen(fileName, "r");
	
	char elfMove;
	char playerMove;
	
	uint64_t score = 0;

	while (fscanf(inputFile, "%c %c\n", &elfMove, &playerMove) != EOF){
		int playScore = (int)(playerMove - PLAYER_ROCK) + 1;


		int diff = (playerMove - PLAYER_ROCK) - (elfMove - ELF_ROCK);
		diff += 3;
		diff %= 3;
		printf("PlayScore: %i\tDiff: %i\t", playScore, diff);
		if (diff == 0){
			playScore += 3;
		}
		if (diff == 1){
			playScore += 6;
		}
		
		
		printf("Play Score = %i\n", playScore);
		score += playScore;
	}
	printf("Total score: %lu\n", score);
}

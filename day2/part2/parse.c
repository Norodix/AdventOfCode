#include <stdio.h>
#include <stdint.h>

char fileName[] = "input.txt";

#define PLAYER_ROCK ('X')
#define DRAW ('Y')
#define ELF_ROCK ('A')


int main(){
	FILE* inputFile = fopen(fileName, "r");
	
	char elfMove;
	char result;
	
	uint64_t score = 0;

	while (fscanf(inputFile, "%c %c\n", &elfMove, &result) != EOF){
		// your move is opponent -1 if X, opponent if Y, opponent +1 if Z
		int elfMove_num = elfMove - ELF_ROCK ; //0-2 rock papaer scissor
		int playerMove_num = (elfMove_num + (result - DRAW) + 3) % 3;
		int playScore = playerMove_num + 1;


		int diff = playerMove_num - elfMove_num;
		diff += 3;
		diff %= 3;
		//printf("PlayScore: %i\tDiff: %i\t", playScore, diff);
		if (diff == 0){
			playScore += 3;
		}
		if (diff == 1){
			playScore += 6;
		}
		
		
		//printf("Play Score = %i\n", playScore);
		score += playScore;
	}
	printf("Total score: %lu\n", score);
}

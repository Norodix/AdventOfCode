#include <stdio.h> 
#include <stdint.h> 
 
char fileName[] = "input.txt"; 
 
typedef struct
{
	int left;
	int right;	
}ElfRange;

int is_contained(ElfRange range1, ElfRange range2){
	if((range1.left <= range2.left && range1.right >= range2.right) || 
	   (range2.left <= range1.left && range2.right >= range1.right))
		return 1;
	return 0;
}

int is_overlapping(ElfRange range1, ElfRange range2){
	if(range1.left > range2.right)
		return 0;
	if(range1.right < range2.left)
		return 0;
	return 1;
}
 
int main(){ 
        FILE* inputFile = fopen(fileName, "r"); 
        int fully_overlap_count = 0, overlap_count = 0; 
	ElfRange range1, range2;	
 
        while (fscanf(inputFile, "%i-%i,%i-%i\n", &range1.left, &range1.right, &range2.left, &range2.right) != EOF){ 
		if (is_contained(range1, range2)){
			fully_overlap_count++;
			//printf("Overlapping: %i-%i, %i-%i\n", range1.left, range1.right, range2.left, range2.right);
		}
		if (is_overlapping(range1, range2)){
			overlap_count++;
		}
        } 
        printf("Fully overlapped count:\t %i\n", fully_overlap_count); 
        printf("Partially overlapped count:\t %i\n", overlap_count); 
	return 0;
}

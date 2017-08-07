#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	struct gameState state;
	int card[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int game = initializeGame(2, card, 7, &state);

	printf("---Start Game Over Test---\n");

	int over = isGameOver(&state);
	assert(over == 0);
	printf("***Game over Test Passed***\n");

	return 0;
}
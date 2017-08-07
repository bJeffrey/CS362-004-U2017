#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	struct gameState state;
	int i;
	int turnnumber=0;
	int player=0;
	int card[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int game = initializeGame(2, card, 7, &state);

	printf("---Start Whose Turn Test---\n");

	for (i = 0; i < 10; i++) {
		state.whoseTurn = turnnumber;
		player = whoseTurn(&state);

		assert(player == turnnumber);
			printf("***Whose Turn Test Passed***\n");
		turnnumber++;
	}
	printf("---Ending Whose Turn Test---\n");

	return 0;
}
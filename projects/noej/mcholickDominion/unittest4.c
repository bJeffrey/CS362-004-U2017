#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	struct gameState state;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int game = initializeGame(2, k, 7, &state);

	printf("---Start buyCard Test---\n");
	int buy;
	state.numBuys = 0;
	state.coins = 10;
	printf("-Testing no buys left-\n");
	buy = buyCard(3, &state);
	assert(buy == -1);
	printf("Pass\n");

	state.numBuys = 2;
	state.coins = 0;
	printf("-Testing not enough coins-\n");
	buy = buyCard(3, &state);
	assert(buy == -1);
	printf("Pass\n");

	state.numBuys = 2;
	state.coins = 10;
	printf("-Testing with more than enough coins and buys-\n");
	buy = buyCard(2, &state);
	assert(buy == 0);
	printf("Pass\n");
	
	printf("---Ending buyCard Test---\n");

	return 0;
}
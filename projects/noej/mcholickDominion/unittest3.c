#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
	struct gameState G;

	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	int r = initializeGame(2, k, 7, &G);

	printf("---Start Get Cost Test---\n");
	assert(getCost(adventurer) == 6);
		printf("**Get Cost Test adventurer Successful**\n");
	assert(getCost(smithy) == 4);
		printf("**Get Cost Test smithy Successful**\n");
	assert(getCost(sea_hag) == 4);
		printf("**Get Cost Test sea_hag Successful**\n");
	assert(getCost(curse) == 0);
		printf("**Get Cost Test Curse Successful**\n");

	printf("---Ending Get Cost Test---\n");

	return 0;
}
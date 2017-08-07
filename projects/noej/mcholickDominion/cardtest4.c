/*#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(int argc, char** argv) {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, great_hall,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 5, &G);
	int actions = G.numActions; //player will get 1 action
	G.handCount[0]= 1;

	printf("---Start Great_hall card Test---\n");
	assert(cardEffect(great_hall, 0, 0, 0, &G, 0, NULL) == 0);
	assert(G.numActions == actions + 1);
	assert(G.handCount[0] == 1);
	printf("Pass\n");
	printf("---End Great_hall card Test---\n");
	return 0;
}
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void printTestResults(int test){
      if(test == 0)
            printf("Test Failed.\n");
      else if(test == 1)
            printf("Test Passed.\n");
      else
            printf("Function returned unexpected value.\n");
}


// This allows the purchase of a card up to 6 value higher instead of three for the mine card
int mineTest(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state, stateCopy;
      initializeGame(3,k,1,&state);

      int x, result;
      stateCopy = state;
      result = cardEffect(mine, 0, 2, 0, &state, 0, &x);
      if(result != 0)
            return 0;

      return 1;
}

int main(){

      printf("Testing the 'mine' function...\n");
      int testResults = mineTest();
      printTestResults(testResults);

      return 0;
}

/*#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(int argc, char** argv) {

	struct gameState G;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };

	initializeGame(2, k, 5, &G);
	G.handCount[whoseTurn(&G)] = 0;
	printf("---Start Smithy card Test---\n");
	assert(cardEffect(smithy, 0, 0, 0, &G, 0, NULL) == 0);
	assert(G.handCount[whoseTurn(&G) == 3]);
	printf("Pass\n");
	printf("---End Smithy card Test---\n");
	return 0;
}*/
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


int smithyRefactoredTest(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      initializeGame(3,k,1,&state);

      int beforeSmithy = numHandCards(&state);
      // Test if smithyRefactored() reaches the end nominally

	cardEffect(smithy, 0, 0, 0, &state, 0, NULL);

      int afterSmithy = numHandCards(&state);

      // difference should be 2 because Smithy picks up three cards, but the player still needs to discard 1 card
      if(afterSmithy - beforeSmithy !=2)
            return 0;
      return 1;

}

int main(){

      printf("Testing the 'smithyRefactoredTest' function...\n");
      int testResults = smithyRefactoredTest();
      printTestResults(testResults);

      return 0;
}

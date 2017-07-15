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
      if(smithyRefactored(0, 0, &state, 0) != 0)
            return 0;
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

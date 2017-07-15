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

// with a newly initialized game, 'numHandCards' should always return a 5
int numHandCardsTest(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      initializeGame(3,k,1,&state);

      int result = numHandCards(&state);
      if(result == 5)
            return 1;
      else
            return 0;
}

int main(){

      printf("Testing the 'numHandCards' function...\n");
      int testResults = numHandCardsTest();
      printTestResults(testResults);

      return 0;
}

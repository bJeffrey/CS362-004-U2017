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

// with a newly initialized game, 'whoseTurn should always return a 0'
int whoseTurnTest(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      initializeGame(3,k,1,&state);

      int result = whoseTurn(&state);

      if(result == 0)
            return 1;
      else
            return 0;
}

int main(){

      printf("Testing the 'whoseTurn' function...\n");
      int testResults = whoseTurnTest();
      printTestResults(testResults);

      return 0;
}

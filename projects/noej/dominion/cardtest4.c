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


// This allows the purchase of a card up to 6 value higher instead of three
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

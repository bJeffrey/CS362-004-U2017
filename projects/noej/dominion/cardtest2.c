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

// with a newly initialized game, we should have 5 treasure cards.
// adventurer would normally give us 2 additional treasure cards and we would have 7 treasure cards and 7 total cards
// an error will be anything except this result
int adventurerRefactoredTest(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      int temphand[MAX_HAND];// moved above the if statement
      int i, result, cardDrawn;
      int count = 0;
      initializeGame(3,k,1,&state);

      for (i = 0; i < state.handCount[0]; i++)
       {
             if (state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] || gold)
                   count++;
       }

      int x;
      result = cardEffect(adventurer, 0, 0, 0, &state, 0, &x);
      if(result != 0)
            return 0;

      count = 0;
      for (i = 0; i < state.handCount[0]; i++)
      {
            if (state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] || gold)
                  count++;
      }
      if(count != 7, state.handCount[0] != 7)
            return 0;
      return 1;

}

int main(){

      printf("Testing the 'adventurerRefactored' function...\n");
      int testResults = adventurerRefactoredTest();
      printTestResults(testResults);

      return 0;
}

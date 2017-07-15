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

// I should have 8 cards at the end of council room because council room picks up 4 and discards 1
// I should have one more buy than I started with
// Here, my player number is 1
int council_roomRefactoredTest(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state, stateCopy;
      initializeGame(3,k,1,&state);

      int x, i;
      stateCopy = state;
      // int result = cardEffect(council_room, 0, 0, 0, &state, 0, &x);
      int result = council_roomRefactored(x, 1, &state, 0);

      if(result != 0)
            return 0;

      if(stateCopy.handCount[1] +3 != state.handCount[1])
            return 0;


      if (stateCopy.numBuys + 1 != state.numBuys)
            return 0;

      for (i = 0; i < state.numPlayers; i++)
      {

            if ( i != 1 )
            {
                  if(stateCopy.handCount[i] + 1!= state.handCount[i])
                        return 0;
            }
      }


      return 1;
}

int main(){

      printf("Testing the 'council_roomRefactored' function...\n");
      int testResults = council_roomRefactoredTest();
      printTestResults(testResults);

      return 0;
}

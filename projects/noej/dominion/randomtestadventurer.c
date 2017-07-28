#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

void printTestResults(int test){
      if(test == 0)
            printf("Test Failed.\n");
      else if(test == 1)
            printf("Test Passed.\n");
      else
            printf("Function returned unexpected value.\n");
}

int generateRandNum(unsigned int min, unsigned int max){
      // random() is part of posix and not available on windows

      unsigned int randomNumber;

      unsigned int range = 1 + max - min;
      unsigned int buckets = RAND_MAX / range;
      unsigned int limit = buckets * range;

      do{
          randomNumber = random();
      //     randNum = rand();
}while(randomNumber >= limit);

      randomNumber = min + (randomNumber / buckets);

      return (int) randomNumber;
}

// with a newly initialized game, we should have 5 treasure cards.
// adventurer would normally give us 2 additional treasure cards and we would have 7 treasure cards and 7 total cards
// an error will be anything except this result
/*
Adventurer uses these values.  They'll need to be randomized:
      state->deckCount[currentPlayer]
      currentPlayer
      drawnTreasure
      cardDrawn
      state->hand[currentPlayer][state->handCount[currentPlayer]-1]
      state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]
*/

int adventurerRandomTestGenerator(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      int temphand[MAX_HAND];// moved above the if statement
      int i, result, cardDrawn;
      int count = 0;
      unsigned int randNum1 = random();
      unsigned int randNum2 = random();
      unsigned int randNum3 = random();
      unsigned int randNum4 = random();
      unsigned int randNum5 = random();


      while(randNum1 > INT_MAX || randNum2 > INT_MAX || randNum3 > INT_MAX || randNum4 > INT_MAX || randNum5 > INT_MAX){
            randNum1 = random();
            randNum2 = random();
            randNum3 = random();
            randNum4 = random();
            randNum5 = random();
      }


      initializeGame(3, k, 1, &state);//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)

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
      srand(time(NULL));
      int returnValue = adventurerRandomTestGenerator();

      printf("In randomtestadventurer\n");
      printTestResults(returnValue);
      return 0;
}

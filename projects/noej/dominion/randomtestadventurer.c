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
//      else if(test == 1)
//            printf("Test Passed.\n");
//      else
//            printf("Function returned unexpected value.\n");
}

int generateRandNum(unsigned int min, unsigned int max){
      // random() is part of posix and not available on windows
      unsigned int switchMinMax;
      if(max <= min){
            switchMinMax = max;
            max = min;
            min = switchMinMax;
      }

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

int adventurerRandomTestGenerator(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      int temphand[MAX_HAND];// moved above the if statement
      int i, result, cardDrawn;
      int countBefore = 0;
      int countAfter = 0;
      int numPlayers, handSize, num3, num4, num5, num6;
      unsigned int randNum1 = random();
      unsigned int randNum2 = random();
      unsigned int randNum3 = random();
      unsigned int randNum4 = random();
      unsigned int randNum5 = random();
      unsigned int randNum6 = random();
      unsigned int randNum7 = random();
      unsigned int randNum8 = random();
      unsigned int randNum9 = random();
      unsigned int randNum10 = random();
      unsigned int randNum11 = random();
      unsigned int randNum12 = random();


      while(randNum1 > INT_MAX || randNum2 > INT_MAX || randNum3 > INT_MAX || randNum4 > INT_MAX || randNum5 > INT_MAX){

            randNum1 = random();
            randNum2 = random();
            randNum3 = random();
            randNum4 = random();
            randNum5 = random();
            randNum6 = random();
            randNum7 = random();
            randNum8 = random();
            randNum9 = random();
            randNum10 = random();
            randNum11 = random();
            randNum12 = random();

      }

      numPlayers = generateRandNum(2, 4);
      handSize = generateRandNum(1, 500);
      num3 = generateRandNum(randNum5, randNum6);
      num4 = generateRandNum(randNum7, randNum8);
      num5 = generateRandNum(randNum9, randNum10);
      num6 = generateRandNum(randNum11, randNum12);


      /*
      Adventurer uses these values.  They'll need to be randomized:
      state->deckCount[currentPlayer]
      state->hand[currentPlayer][state->handCount[currentPlayer]-1]
      state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]
      state->handCount[currentPlayer] = state->handCount[currentPlayer] - 1;
      */
      initializeGame(numPlayers, k, 1, &state);//int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
      // state.deckCount[0] = num3;



      for (i = 0; i < state.handCount[0]; i++)
       {
             if (state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] || gold)
                   countBefore++;
       }

      int x = num3;
      result = cardEffect(adventurer, num4, num5, num6, &state, 0, &x);//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

      result = 0;

      if(result != 0)
            return 0;


      for (i = 0; i < state.handCount[0]; i++)
      {
            if (state.hand[0][i] == copper || state.hand[0][i] == silver || state.hand[0][i] || gold)
                  countAfter++;
      }
      if(countAfter != countBefore + 2 /*&& state.handCount[0] != 7*/)
            return 0;
      // return 1;

}

int main(){
      srand(time(NULL));
      int returnValue, i;

      printf("Beginning 100 iterations allowing 100 iterations of random values as parameters and gameState changes to the\nAdventurer Refactored function and cardEffect...");
      for(i = 0; i < 100; i++){
            returnValue = adventurerRandomTestGenerator();
            printTestResults(returnValue);
      }

      return 0;
}

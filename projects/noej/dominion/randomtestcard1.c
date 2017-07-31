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
/*      else if(test == 1)
            printf("Test Passed.\n");
      else
            printf("Function returned unexpected value.\n");
            
*/
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

int smithyRandomTestGenerator(){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state;
      int beforeSmithy;
      int afterSmithy;

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
      initializeGame(3,k,1,&state);

      beforeSmithy = numHandCards(&state);
      // Test if smithyRefactored() reaches the end nominally

      smithyRefactored(num3, 0, &state, 0);

      afterSmithy = numHandCards(&state);

      state.deckCount[0] = handSize;//This happens to be the same limit as the deck size
      state.discardCount[0] = num4;
      smithyRefactored(num5, 0, &state, 0);
      int x = random();
      cardEffect(smithy, num4, num5, num6, &state, 0, &x);

      // difference should be 2 because Smithy picks up three cards, but the player still needs to discard 1 card
      if(afterSmithy - beforeSmithy !=2)
            return 0;
      return 1;

}


int main(){

      printf("Beginning 100 iterations allowing 100 iterations of random values as parameters and gameState changes to the\nSmithy Refactored function and cardEffect...");
      int returnResult, i;

      for(i = 0; i < 100; i++){
            returnResult = smithyRandomTestGenerator();
            printTestResults(returnResult);

      }
      return 0;
}

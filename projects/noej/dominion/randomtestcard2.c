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
/*
      else if(test == 1)
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

int council_roomRandomTestGenerator(int numPlayers, int handSize, int num1, int num2){

      //Default cards, as defined in playDom
      // The following three lines are from player.c to initialize the game
      int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
      struct gameState state, stateCopy;
      initializeGame(3,k,1,&state);

      int x, i;

      state.numActions = num2;
      state.numBuys = num1;
      state.deckCount[0] = handSize;

      stateCopy = state;
      int result = cardEffect(council_room, num1, num2, handSize, &state, 0, &x);

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

      result = council_roomRefactored(x, 1, &state, 0);


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

      int i, numPlayers, handSize, num3, num4, num5, num6, printResults;
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
      num5 = generateRandNum(randNum9, randNum10);
      num6 = generateRandNum(randNum11, randNum12);

      printf("Beginning 100 iterations allowing 100 iterations of random values as parameters and gameState changes to the\nCouncil Room Refactored function and cardEffect...");
      for(i = 0; i < 100; i++){
            while(randNum1 > INT_MAX || randNum2 > INT_MAX || randNum3 > INT_MAX || randNum4 > INT_MAX){
                  randNum1 = random();
                  randNum2 = random();
                  randNum3 = random();
                  randNum4 = random();
            }

            numPlayers = generateRandNum(2, 4);
            handSize = generateRandNum(1, 500);
            num3 = generateRandNum(randNum1, randNum2);
            num4 = generateRandNum(randNum4, randNum3);

            if(i == 0)
                  printResults = council_roomRandomTestGenerator(numPlayers, handSize, i, num4);

            printResults = council_roomRandomTestGenerator(numPlayers, handSize, num3, num4);
            printTestResults(printResults);
      }


      return 0;
}

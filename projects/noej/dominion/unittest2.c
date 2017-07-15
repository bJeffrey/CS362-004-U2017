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

int newGameTest(){
      struct gameState* gameStateTest = newGame();
      if (gameStateTest)
            return 1;
      if (!gameStateTest)
            return 0;
      return -1;

}

int main(){

      printf("Testing the 'newGame' function...\n");
      int testResults = newGameTest();
      printTestResults(testResults);

      return 0;
}

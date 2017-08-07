/*
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define NUM_TESTS 200
#define MAX_DECK_COUNT 100

//TEST FOR SMITHY
// HAND + 3

int main(int argc, char** argv) {
	srand(time(NULL));
	struct gameState G;
	int passTest, failTest , i, j,randomCard,r,randomDeck,randomHand,randomDiscard, handCountSim, handCountTest;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };

	printf("---Start Random Smithy Card Testing---\n");
	passTest = 0;
	failTest = 0;

	//-------------------------Testing Loop-----------------------------
	for(i = 0; i< NUM_TESTS; i++){

		//---------------Set Up for initalization---------------------------
		int seed = rand();  //create and seed new game
		int playerCount = rand() % 3; 	//0-2
		playerCount = 4 - playerCount; 	//4-2 players
		int player = 0;

		initializeGame(playerCount, k, seed, &G);
		G.whoseTurn = 0;
 		//printf("deck\n");

		randomDeck = 10 + rand() % (MAX_DECK_COUNT- 9);   //deck: 10 to MAX_DECK_COUNT
		G.deckCount[player] = randomDeck;
		memset(G.deck[player], 0, sizeof(int) * G.deckCount[player]);
		//printf("hand\n");

		randomHand = 10 + rand() % (MAX_DECK_COUNT-9);   //hand: 10 to MAX_DECK_COUNT
		G.handCount[player] = randomHand;
		memset(G.hand[player], 0, sizeof(int) * G.handCount[player]);
		//printf("discard\n");

        randomDiscard = rand() % (MAX_DECK_COUNT);   //discard : 0 to MAX_DECK_COUNT
        G.discardCount[player] = randomDiscard;
        memset(G.discard[player], 0, sizeof(int) * G.discardCount[player]);

		//-----------------Fill player deck, discard and hand.-----------------
		//printf("Filling Decks\n");
        for(j=0;j<G.deckCount[player];j++){
        	randomCard = rand() % treasure_map;
        	G.deck[player][j] = randomCard;
        	//randomDeck[j] = randomCard;
        }
        for(j=0;j<G.discardCount[player];j++){
        	randomCard = rand() % treasure_map;
        	G.discard[player][j] = randomCard;
        	//randomDiscard[j] = randomCard;
        }
        G.hand[player][0] = adventurer;
        for(j=1;j<G.handCount[player];j++){
        	randomCard = rand() % treasure_map;
        	G.hand[player][j] = randomCard;
        	//randomHand[j] = randomCard;
        }
        //place smithy card in players hand at rand location
        int smithyIndex=rand() % G.handCount[player];
        G.hand[player][smithyIndex] = smithy;
        //printf("handCount is %d \n",numHandCards(&G));
        //save copy of init gameState
        struct gameState testG;
        memcpy (&testG, &G, sizeof(struct gameState));
       //-------------simulate smithy card--------------
            // HAND + 3
        for(j=0;j<3;j++){          //draw 3 cards
	        G.handCount[player]++; //draw card
	        G.hand[player][G.handCount[player]-1]=G.deck[player][G.deckCount[player]-1]; //add card of deck to player hand
	        G.deckCount[player]--; // card was removed from deck
	    }
	    discardCard(smithyIndex, player, &G, 0);

        //---------------------Run dominion.c Smithy Function-----------------------

        r= cardEffect(smithy,0,0,0,&testG,smithyIndex,NULL);

        //Check if running correctly
        //handcount +3
        assert(r==0);

        handCountTest = testG.handCount[player];
        handCountSim = G.handCount[player];

		int result = handCountTest - handCountSim;

		if(result == 0) //player should have 2 more treasures (both simulated and function should have equal hands)
		{
			passTest++;
		}
		else{
			failTest++;
			printf("Failed: HandCount difference of %d \n",result);
			printf("HandCount from Smithy function is : %d, HandCount should be : %d \n",handCountTest,handCountSim);
			printf("Player Count: %d, Deck:%d, Hand: %d, Discard: %d\n\n", playerCount, randomDeck,randomHand,randomDiscard);
		}
	}
	//---------------------------Out of testing Loop------------------------------------
	printf("---End Random Smithy card Testing---\n");
	printf("Random Smithy Test Passed: %d , Failed: %d \n",passTest,failTest);
	return 0;
*/
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
	int currentPlayer = whoseTurn(&state);

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
		printf("i: %d\n", i);
		printf("state.handCount[%d]: %d\n", i, state.handCount[i]);

            if ( i != 1 )
            {
                  if(stateCopy.handCount[i] + 1!= state.handCount[i]){
				printf("About to return 0\n");
				return 0;
			}
            }
      }
	printf("Here I am\n");

	result = Council_room(&state, 0);
      // result = council_roomRefactored(x, 1, &state, 0);


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

      printf("Beginning 100 iterations allowing 100 iterations of random values as parameters and gameState changes to the\nCouncil Room Refactored function and cardEffect...\n");
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

            // printResults = council_roomRandomTestGenerator(numPlayers, handSize, num3, num4);
            printTestResults(printResults);
      }
	printf("End of council_room test\n");


      return 0;
}

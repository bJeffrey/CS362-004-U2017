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

int main(int argc, char** argv) {

	srand(time(NULL));
	struct gameState G;
	int passTest, failTest , i, j,randomCard,r,randomDeck,randomHand,randomDiscard;
	int k[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy };

	printf("---Start Random Adventurer card Testing---\n");
	passTest = 0;
	failTest = 0;
	//-------------------------Testing Loop-----------------------------
	for(i = 0; i< NUM_TESTS; i++){

		//---------------Set Up for initalization---------------------------
		//printf("Initalization\n");

		int seed = rand();  //create and seed new game
		int playerCount = rand() % 3; 	//0-2
		playerCount = 4 - playerCount; 	//4-2 players
		int player = 0;

		initializeGame(playerCount, k, seed, &G);
		G.whoseTurn = 0;
		int treasureCount = 0;
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
        	if(randomCard == copper || randomCard == silver || randomCard == gold){
        		treasureCount++;
        	}
        }
        //printf("handCount is %d \n",numHandCards(&G));
        //save copy of init gameState
        struct gameState testG;
        memcpy (&testG, &G, sizeof(struct gameState));

        //-------------simulate Adventurer card--------------
        //printf("Simulating Adventurer Card\n");
        int treasureFound = 0;
        int currentCard = 0;
        int index = 0;

        while(treasureFound < 2){
        	currentCard = G.deck[player][index];
        	if(currentCard == copper || currentCard == silver || currentCard == gold){
        		treasureFound++;
        		treasureCount++;  //add treasure to treasure count
        		G.hand[player][G.handCount[player]] = currentCard; //add treasure to hand
        		G.handCount[player]++;
        		G.deckCount[player]--;
        	}
        	else
        		{index++;}
        }

        //---------------------Run dominion.c Adventurer Function-----------------------
        //r= cardEffect(adventurer,0,0,0,&testG,0,NULL);
        r =  Adventurer(&testG);
        //printf("hc adventurer %d",numHandCards(&testG));

        //Check if running correctly/handcount +2
        assert(r==0);
        int handCountTest = numHandCards(&testG);
        int handCountSim = numHandCards(&G);

        //printf("HandCount from Adventure function is : %d, HandCount should be : %d \n",handCountTest,handCountSim);
		int result = handCountTest - handCountSim;
		int treasureCountTest = 0; //treasureCount and treasureCountTest should be equal (checks that the new cards are treasure)
		for(j=0;j<testG.handCount[player];j++){
			currentCard = testG.hand[player][j];
			if(currentCard == copper || currentCard == silver || currentCard == gold){
        		treasureCountTest++;
        	}
		}
		int treasureCountResult = treasureCount - treasureCountTest;
		//printf("TreasureCount should be: %d treasureCount is: %d \n",treasureCount,treasureCountTest);
		if(result == 0) //player should have 2 more treasures (both simulated and function should have equal hands)
		{
			if(treasureCountResult == 0){
				passTest++;
			}
			else{
				failTest++;
				printf("Failed:TreasureCount difference of %d\n",treasureCountResult);
				printf("TreasureCount should be: %d treasureCount is: %d \n",treasureCount,treasureCountTest);
				printf("Player Count: %d, Deck:%d, Hand: %d, Discard: %d\n", playerCount, randomDeck,randomHand,randomDiscard);
			}
		}
		else{
			failTest++;
			printf("Failed: HandCount difference of %d \n",result);
			printf("HandCount from Adventure function is : %d, HandCount should be : %d \n",handCountTest,handCountSim);
			printf("TreasureCount should be: %d treasureCount is: %d \n",treasureCount,treasureCountTest);
			printf("Player Count: %d, Deck:%d, Hand: %d, Discard: %d\n", playerCount, randomDeck,randomHand,randomDiscard);
		}
	}
	//---------------------------Out of testing Loop------------------------------------
	printf("---End Random Adventurer card Testing---\n");
	printf("Random Adventurer Test Passed: %d , Failed: %d \n",passTest,failTest);
	return 0;
}
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
	// printf("Hello\n");
      result = cardEffect(adventurer, 0, 0, 0, &state, 0, NULL);//int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

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

      printf("Beginning 100 iterations allowing 100 iterations of random values as parameters and gameState changes to the\nAdventurer Refactored function and cardEffect...\n");
      for(i = 0; i < 100; i++){
            returnValue = adventurerRandomTestGenerator();
            printTestResults(returnValue);
      }
	printf("End of adventurer test\n");
      return 0;
}

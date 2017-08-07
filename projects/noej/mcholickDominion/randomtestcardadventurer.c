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




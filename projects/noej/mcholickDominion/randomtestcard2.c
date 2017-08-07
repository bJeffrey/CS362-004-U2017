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
}
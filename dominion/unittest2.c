#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>



int myAssert(int r, char* msg, int lineNum)
{
	
	static int failed = 0;
	if(r == 0)
	{
		printf("FAILED ASSERTION (line#%d): %s\n", lineNum, msg);
		failed = 1;
	}
	return failed;
}


//Testing endTurn
int main() {
	struct gameState g, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};

	int r = 0;
	int count;
	initializeGame(2, k, 1, &orig);
	//Trevor's suggestion, saving game state for testing purposes
	memcpy(&g, &orig, sizeof(struct gameState));	
	  
	//first hand of player 0 is {4 coppers, 1 estate}. 4 coins
	//Going to bypass this and setup something specific for the hand
	gainCard(smithy, &g, 2, 0);
	//Check the deck
	count = fullDeckCount(0, 1, &g);
	//play smithy (which puts it into playedCards)
	playCard(5, 0, 0, 0, &g);
	endTurn(&g);
	myAssert(count == fullDeckCount(0, 1, &g), "endTurn is missing cards?", __LINE__);
	myAssert(g.handCount[0] == 5, "Player 0 did not draw the correct number of cards", __LINE__);
	myAssert(whoseTurn(&g) == 1, "endTurn did not advance player", __LINE__);
	
	
	
	myAssert(r == 0, "No duplicates, 2 players, should succeed", __LINE__);

	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
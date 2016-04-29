#include "dominion.h"
#include <string.h>
#include <stdio.h>

int failed = 0;

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


//Testing 
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
	count = supplyCount(curse, &g);
	r = buyCard(-1, &g);
	myAssert(r == -1, "Bought a non-existant card", __LINE__);
	r = buyCard(council_room, &g);
	myAssert(r == -1, "Bought council room which is not in supply of card types", __LINE__);
	r = buyCard(copper, &g);
	myAssert(r == -1, "Bought more than one card on first turn", __LINE__);
	r = buyCard(embargo, &g);
	myAssert(r == 0, "Could not buy an embargo with 4 coins", __LINE__);
	
	
	
	myAssert(r == 0, "No duplicates, 2 players, should succeed", __LINE__);

	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}

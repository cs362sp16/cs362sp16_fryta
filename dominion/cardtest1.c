#include "dominion.h"
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


//Testing baron and default deal
int main() {
	struct gameState g, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};
	int i;
	int r = 0;
	//3 player game this time
	initializeGame(3, k, 1, &orig);
	//Trevor's suggestion, saving game state for testing purposes
	memcpy(&g, &orig, sizeof(struct gameState));	
	gainCard(baron, &orig, 2, 0);
	
	r = supplyCount(estate, &g);
	playCard(5, 1, 0, 0, &g);
	myAssert(r == supplyCount(estate, &g), "Baron gained estate, should have been discarding", __LINE__);
	myAssert(numHandCards(&g) == 4, "Wrong hand size, did not properly discard", __LINE__);
	for(i = 0; i < numHandCards(&g); ++i)
		myAssert(handCard(i, &g) == copper, "Should be copper, did not properly discard", __LINE__);
	//have 8 coins total
	r = buyCard(gold, &g);
	myAssert(r == 0, "Did not have 6 coins to buy gold", __LINE__);
	r = buyCard(silver, &g);
	myAssert(r == -1, "Bought silver, had more than 8 coins", __LINE__);
	r = buyCard(estate, &g);
	myAssert(r == 0, "Did not have 8 coins or 2 buys for estate", __LINE__);
	r = buyCard(copper, &g);
	myAssert(r == -1, "Got more than +1 buy from baron", __LINE__);
	
	
	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
	
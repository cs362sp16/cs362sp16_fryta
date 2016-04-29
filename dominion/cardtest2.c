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


//Testing abasssador and default deal
int main() {
	struct gameState g, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};
	int count, supply;
	int r = 0;
	//3 player game this time
	initializeGame(3, k, 1, &orig);
	//Trevor's suggestion, saving game state for testing purposes
	memcpy(&g, &orig, sizeof(struct gameState));	
	
	gainCard(ambassador, &g, 2, 0);
	//play ambassador, reveal 1 estate, try to return 2 cards, but should only have 1
	r = playCard(5, 6, 0, 0, &g);
	myAssert(r == -1, "Revealed invalid handPos", __LINE__);
	r = playCard(5, 4, 3, 0, &g);
	myAssert(r == -1, "Choice2 cannot be > 2", __LINE__);
	r = playCard(5, 4, 5, 0, &g);
	myAssert(r == -1, "Played ambassador with itself???", __LINE__);
	count = fullDeckCount(1, 1, &g);
	supply = supplyCount(estate, &g);
	r = playCard(5, 4, 2, 0, &g);
	myAssert(r == 0, "Vaild execution of ambassador failed", __LINE__);
	myAssert(numHandCards(&g) == 4, "Did not remove correct amount", __LINE__);
	
	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
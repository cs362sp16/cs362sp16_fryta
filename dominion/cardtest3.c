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


//Testing smithy and default deal
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
	
	gainCard(smithy, &g, 2, 0);
	//play smithy, should get three new cards
	r = playCard(5, 6, 0, 0, &g);
	myAssert(r == -1, "Revealed invalid handPos", __LINE__);
	
	count = fullDeckCount(1, 1, &g);
	supply = supplyCount(estate, &g);
	r = playCard(5, 4, 2, 0, &g);
	myAssert(r == 0, "Vaild execution of smithy failed", __LINE__);
	myAssert(numHandCards(&g) == 4, "Did not add correct amount", __LINE__);
	
	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
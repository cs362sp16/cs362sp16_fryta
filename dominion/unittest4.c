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


//Testing initializeGame and default deal
int main() {
	struct gameState g, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};

	int r = 0;
	//3 player game this time
	initializeGame(3, k, 1, &orig);
	//Trevor's suggestion, saving game state for testing purposes
	memcpy(&g, &orig, sizeof(struct gameState));	
	
	//first hand of player 0 is {4 coppers, 1 estate}. 4 coins
	buyCard(gardens, &g); //player 0 buys a garden
	endTurn(&g);
	buyCard(curse, &g); //player 1 buys a curse
	endTurn(&g);
	//Not doing anything on player 3 turn
	endTurn(&g);
	
	r = scoreFor(3, &g);
	myAssert(r == -9999, "Player should not exist but did", __LINE__);
	r = scoreFor(0, &g);
	myAssert(r == 5, "Player should have a base 5 points", __LINE__);
	
	
	
	

	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
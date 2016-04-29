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


//Testing endGame
int main() {
	struct gameState g, orig;
	
	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};
	int p[3]; //should be set in dominion.c
	int r = 0;
	int i;
	int count;
	//3 player game this time
	initializeGame(3, k, 1, &orig);
	//Trevor's suggestion, saving game state for testing purposes
	memcpy(&g, &orig, sizeof(struct gameState));	
	
	//buy an estate to gain victory points and "win"
	buyCard(estate, &g);
	//get to player 2's turn and end
	//Loop until end
	for(i = 0; i < 2; ++i){
		endTurn(&g);
	}
	getWinners(p, &g);
	myAssert(p[1] == 0 && p[2] == 0, "Player 1 and 2 should have lost but did not", __LINE__);
	myAssert(p[3] == -9999, "Player 4 should not exist but did", __LINE__);
	myAssert(p[0] == 1, "Player 0 did not win", __LINE__);
	
	
	
	

	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
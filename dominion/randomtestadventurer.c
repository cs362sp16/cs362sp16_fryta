#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "dominion.h"
#include "dominion_helpers.h"

/*
 * Testing Adventurer
 */
int failed = 0;
int numSuccess = 0, numFail = 0, checkRuns = 0;

void assert_fail(int ans) {
	if (ans == -1) {
		printf("TEST FAILED\n");
		failed = 1;
	}
}

void assert_pass() {
	if (!failed) {
		printf("TEST PASSED\n");
	}
}

int genPlayer() {
        int number = rand() % 10;
        return number;
}

int checkAdventurer(int z, int currentPlayer, struct gameState *state, int drawntreasure, int cardDrawn) {
	int r;

	r = adventurerCard(z, currentPlayer, state, drawntreasure, cardDrawn);
	if (r == 0){
        checkRuns++;
        numSuccess++;
		return;
    }
    else{
        checkRuns++;
        numFail++;
        return;
    }
}

int main(int argc, char **argv) {
	printf("Starting Test for Adventurer\n");
	srand(time(NULL));
    int result, seed, i;
	struct gameState s, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,village};
	
        if (argc == 2) {
                seed = atoi(argv[1]);
        } else {
                seed = rand() % 200 + 1;
                printf("seed: %d\n", seed);
        }
       
        for (i = 0; i < 10000; i++) {
			
                initializeGame(genPlayer(), k, seed, &s);
                cardEffect(1, 1, 2, 3, &s, 3, 0);
				checkAdventurer(0, rand() % 3, &s, rand() % 3, rand() % 3);
        }

	return 0;
}
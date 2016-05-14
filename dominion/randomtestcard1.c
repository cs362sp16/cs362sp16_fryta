#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "dominion.h"
#include "dominion_helpers.h"

/*
 * Implementation to Test the Village card
 * 
 ******Note: Card seems unstable, lots of segfaults
 */
int failed = 0;

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

int main(int argc, char **argv) {
	printf("Starting Test - Means Village didn't segfault \n");
	srand(time(NULL));
    int result, seed, i, n;
	int r = 0;
	int count;
	struct gameState g, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,village};

        for (i = 0; i < 1; i++) {
                initializeGame(genPlayer(), k, 42, &g);
                result = cardEffect(village, 1, 1, 1, &g, 3, 0);
                assert_fail(result);
        }
        assert_pass(result);

	return 0;
}
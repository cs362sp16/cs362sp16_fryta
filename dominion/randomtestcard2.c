#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "dominion.h"
#include "dominion_helpers.h"

/*
 * Testing Mine
 */
int failed = 0;

int genPlayer() {
        int number = rand() % 10;
        return number;
}

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



int main(int argc, char **argv) {
	printf("Starting Test for Mine\n");
	srand(time(NULL));
    int result, seed, i, n;
	int r = 0;
	int count;
	struct gameState s, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};
        for (i = 0; i < 1; i++) {
                initializeGame(genPlayer(), k, 42, &s);
                gainCard(mine, &orig, 2, 0);
				assert_fail(result);
        }
	assert_pass(result);
	return 0;
}
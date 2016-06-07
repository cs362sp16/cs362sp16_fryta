#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dominion.h"
#include "interface.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include "interface.c"

#define NUM_TOTAL_K_CARDS (treasure_map + 1)
#define STRING_LEN 32

/********************
Tanner Fry
CS 362 
Homework 4
*********************/


//Pre declations

//creating game var
struct gameState init_Game(long seed);
void playGame(long seed);

//card functions
int cardComparison(enum CARD *cards, enum CARD c, int max);
void randomCardGen(enum CARD *cards);
int playCardFunc(struct gameState *g);
int cardBuy(struct gameState *g);
int assignKingdomCards(enum CARD *cards, int length);
int assignKingdomCards_index(struct gameState *g);

//Player function decs
void player_action(struct gameState *g);
int playerBuy(struct gameState *g);


int main(int argc, char **argv)
{
	//Ints for function
	long seed;
	int t;
	
	if(argc != 2){
		printf("Pass in: FUNCTION_NAME SEED\n");
		return 0;
	} else{
		seed = atoi(argv[1]);
		t = atoi(argv[1]);
	}
	srand((unsigned)t);
	playGame(seed);
	return 0;	
}

//Random card gen function
void randomCardGen(enum CARD *cards)
{
	int i;
	for(i = 0; i < 10; i++){
		cards[i] = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
		
		while(cardComparison(cards, cards[i], i-1)){
			cards[i] = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
		}
	}
}

//Creating game state
struct gameState init_Game(long seed)
{
	int num_players;
	struct gameState g;
	enum CARD cards[10];
	
	SelectStream(1);
	PutSeed(seed);
	
	randomCardGen(cards);
	num_players = rand() %3 + 1;
	num_players++;
	
	initializeGame(num_players, (int *)cards, (int)seed, &g);
		
	return g;
}

//Card comparison function
int cardComparison(enum CARD *cards, enum CARD c, int max)
{
	int i;
	for(i = 0; i < max; i++){
		if(cards[i] == c){
			return 1;
		}
	}
	return 0;
}

//Play card order function
//Reports the card to be played
int playCardFunc(struct gameState *g)
{
	int index, r, tmp_num;
	char cardName[STRING_LEN];
	enum CARD c;
	index = assignKingdomCards_index(g);
	c = g->hand[g->whoseTurn][index];
	r = playCard(index, 0, 0, 0, &g);
	tmp_num = c;
	cardNumToName(tmp_num, cardName);
	//Reporting card
	printf("CARD: Playing [%s]\n", cardName);
	return r;	
}

//Generating kingdom cards
int assignKingdomCards(enum CARD *cards, int length)
{
	int i;
	
	for(i = 0; i < length; i++){
		if(cards[i] >= adventurer && cards[i] <= treasure_map){
			return 1;
		}
	}
	return 0;
}

void player_action(struct gameState *g)
{
	int r;
	
	r = 1;
	
	while(r && g->numActions != 0 && assignKingdomCards(g->hand[g->whoseTurn], g->handCount[g->whoseTurn])){
		r = playCardFunc(g) == -1 ? 0 : 1;
	}
}

//Indexing for the above function
int assignKingdomCards_index(struct gameState *g)
{
	int count, index;
	enum CARD *hand;
	count = g->handCount[g->whoseTurn];
	//may need *hand
	hand = g->hand[g->whoseTurn];
	if(!assignKingdomCards(hand, count)){
		return -1;
	}
	index = (int)floor(Random() * count);
	while(!(hand[index] >= adventurer && hand[index] <= treasure_map)){
		index = (int)floor(Random() * count);
	}
	return index;
}


//W
int cardBuy(struct gameState *g)
{
	enum CARD c;
	int tmp_num;
	char cardName[STRING_LEN];
	if(g->coins == 0 || g->numBuys == 0){
		printf("CARD: Invalid Buy\n");
		return -1;
	}
	c = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
	while(getCost(c) > g->coins || c == curse || g->supplyCount[c] == 0){
		c = (enum CARD)(int)floor(Random() * NUM_TOTAL_K_CARDS);
	}
	tmp_num = c;
	cardNumToName(tmp_num, cardName);
	
	
	buyCard(c, g);
	//Reporting card buy 
	printf("CARD: Buying [%s] Success!\n", cardName);
	
	return 0;
}



int playerBuy(struct gameState *g)
{
	updateCoins(g->whoseTurn, g, 0);
	while(g->coins > 0 && g->numBuys > 0){
		cardBuy(g);
	}
}


//Play Function:
//Trevor's code example here
void playGame(long seed)
{
	int i, players;
	int w[4];
	struct gameState g;
	
	g = init_Game(seed);
	
	players = g.numPlayers;
	
	printf("GAME: Starting\n");
	printf("GAME: Players [%d]\n", players);
	
	printf("\n########################\n\n");
	
	while(!isGameOver(&g)){
		printf("\n ************ \n");
		printf("PLAYER: Turn [%d]\n", g.whoseTurn);
		player_action(&g);
		playerBuy(&g);
		printf("PLAYER: End Turn\n");
		endTurn(&g);
	}
	
	printf("\n########################\n\n");
	
	printf("GAME: Over\n");
	
	for(i = 0; i < players; i++){
		printf("STATS: Player[%d] Score [%d]\n", i, scoreFor(i, &g));
	}
	
	getWinners(w, &g);
	for(i = 0; i< players; i++){
		if(w[i]){
			printf("STAT: Player [%d] Wins\n", i);
		}
	}
}

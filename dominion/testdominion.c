#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
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
=======
#include "rngs.h"
#include "dominion.h"
#include "assert.h"
#include "dominion_helpers.h"
#include "math.h"
#include <time.h>

#define TEST_NUM 1000


//Fry - CS 362

/*****************************************************
NEED TO ADD COMMENTS TO THIS


******************************************************/

void random_kingdom_card(int *selected_kingdom_card){
	int i;
	selected_kingdom_card[0]=rand()%(treasure_map - 7 + 1) + 7;
	for(i=1; i<10; i++){
		do{
			selected_kingdom_card[i]=rand()%(treasure_map - 7 + 1) + 7; 
		}
		while(check_cardset(selected_kingdom_card, i));
	}
}


int check_num_action(struct gameState *g){
	int i, num=0, whose;
	whose = g->whoseTurn;

	for(i=0; i<numHandCards(g); i++)
		if(g->hand[whose][i] >= adventurer && g->hand[whose][i] <= treasure_map)
				num++;

	return num;
}  

int check_coins(struct gameState *g){
	int i, money=0;
	for(i = 0; i < numHandCards(g); i++){			
    	if(handCard(i, g)==copper)
   	 		money++;
   	   	else if(handCard(i, g)==silver)
    		money += 2;
    	else if(handCard(i, g)==gold)
    		money += 3;
    	else
   	 		money += 0;
   	}
   	return money;
}

int check_cardset(int *selected_kingdom_card, int i){
	int j;
	for(j=0; j<i; j++){
		 if(selected_kingdom_card[i]==selected_kingdom_card[j])
				return 1;
	}
	return 0;
}

void gen_player_choice(struct gameState *g, int card, int* choice1, int* choice2, int* choice3){
	if(card==mine || card==remodel){
		*choice1 = rand()%(numHandCards(g));
		*choice2 = rand()%(numHandCards(g));
		*choice3 = -1;
	}
	else if(card==feast){
		*choice1 = rand()%27;
		*choice2 = -1;
		*choice3 = -1;		
	}
	else if(card==baron){
		*choice1 = rand()%2;
		*choice2 = -1;	
		*choice3 = -1;
	}
	else if(card==minion){
		*choice1 = rand()%2;
		if(*choice1==1)
			*choice2 = 0;
		else
			*choice2 = 1;
		 *choice3 = -1;
	}
	else if(card==steward){
		*choice1 = rand()%3;
		*choice2 = 0;
		*choice3 = 0;
	}
	else if(card==embargo){
		*choice1 = rand()%10;
		*choice2 = 1;
		*choice3 = 0;
	}
	else if(card==cutpurse){
		*choice1 = rand()%27;
		*choice2 = -1;
		*choice3 = -1;
	}
	else if(card==salvager){
		*choice1 = rand()%2;
		*choice2 = -1;
		*choice3 = -1;
	}
	else{
		*choice1 = -1;
		*choice2 = -1;
		*choice3 = -1;
	}
}



void print_game_information(struct gameState *g, int *kingdom_cards, int seed){
    int i;
    
	printf("\n******Information of Game********\n");
	
	printf("The seed is %d\n", seed);
    printf("Number of Player: %d\n", g->numPlayers);
    printf("Kingdom Cards: \n");
    for(i=0; i<5; i++)
        printf("%d ", kingdom_cards[i]);
    printf("\n");
    for(i=5; i<10; i++)
        printf("%d ", kingdom_cards[i]);
	printf("\n");
	
	printf("*********Game Begins**********\n");
}

void random_initialize(int seed, struct gameState *g){
	int r_num_player, selected_kingdom_card[10];

	SelectStream(1);
	PutSeed(seed);

	r_num_player = rand()%2+2;
	random_kingdom_card(selected_kingdom_card);
	
	initializeGame(r_num_player, selected_kingdom_card, (int)seed, g);
	print_game_information(g, selected_kingdom_card, seed);
}


void perform_actions(struct gameState *g){
	int handPos=0, gainCard, result=1;
	int handCount = numHandCards(g);
	int choice1, choice2, choice3;
	
	if(check_num_action(g)>0){
		do{
			handPos = rand()%handCount;
			gainCard = g->hand[g->whoseTurn][handPos];
			if(gainCard >= adventurer && gainCard <= treasure_map) 
				result = 0;
		}while(result==1);
	

		gen_player_choice(g, gainCard, &choice1, &choice2, &choice3);		
		playCard(handPos, choice1, choice2, choice3, g);
		printf("Player %d: played %d\n", g->whoseTurn+1, gainCard);
	}

	else
		printf("Player %d: skip play phase\n", g->whoseTurn+1);
}

void perform_buys(struct gameState *g){
	int gainCard, i, index, size=0, money=check_coins(g);
	int remain_supply[treasure_map+1];

	
	for(i=0; i<treasure_map+1; i++){
		if(money >= getCost(i) && supplyCount(i, g)>0){
			remain_supply[size] = i;
			size++;
		}
	}

	if(size>0){
		index = rand()%size;
		gainCard = remain_supply[index];

		if(buyCard(gainCard, g)==0)
			printf("Player %d: bought %d\n", g->whoseTurn+1, gainCard);
	}
}

void end_turn(struct gameState *g){
	printf("Player %d: end turn\n", g->whoseTurn+1);
	endTurn(g);
}

void print_result(struct gameState *g){
	int i, players[g->numPlayers];

	printf("\n********Game Over**********\n");

	for(i=0; i<g->numPlayers; i++)
		printf("Player %d: %d\n", i+1, scoreFor(i, g));
	
	getWinners(players, g);
	
	for(i=0; i<g->numPlayers; i++)
		if(players[i]==1)
			printf("Player %d is the winner\n", i+1);
}

void random_game(int seed){
	struct gameState g;

	random_initialize(seed, &g);	
	while(!isGameOver(&g)){
		perform_actions(&g);
		perform_buys(&g);
		end_turn(&g);
	}
	print_result(&g);
}

int main(int argc, char* argv[]){
	int i, seed;
	int secondsLeft = 5;
	
	srand(atoi(argv[1]));
	if(argv[1]!=NULL)
		seed = atoi(argv[1]);
	else
		seed = rand()%10 + 1;
	clock_t start = clock();
	for(i=0; i<TEST_NUM; i++){
		clock_t total_time = (clock() - start) / CLOCKS_PER_SEC;
		if(total_time >= secondsLeft) break;
		random_game(seed);
	}
	printf("Game finished yo \n");
	return 0;
}
>>>>>>> 88cbd9e1e41208911f92d4351f2667fa59e29e55

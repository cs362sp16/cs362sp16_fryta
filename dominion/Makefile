CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
unittest1: unittest1.c dominion.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS) 
	
unittest2: unittest2.c dominion.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS) 

unittest3: unittest3.c dominion.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS) 	
	
unittest4: unittest4.c dominion.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS) 
	
cardtest1: cardtest1.c dominion.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS) 
	
cardtest2: cardtest2.c dominion.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS) 
	
cardtest3: cardtest3.c dominion.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS) 
	
cardtest4: cardtest4.c dominion.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS) 
	
alltests: unittest1 unittest2 unittest3 unittest4 
	gcc -o alltests -g dominion.o rngs.o $(CFLAGS)

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 playdom
	./unittest1 >> unittestresults.out
	echo "GCOV AFTER 1 UNITTEST" >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "GCOV AFTER 2 UNITTEST" >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "GCOV AFTER 3 UNITTEST" >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "GCOV AFTER 4 UNITTEST" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	echo "GCOV AFTER 1 CARDTEST" >> unittestresults.out
	./cardtest2 >> unittestresults.out
	echo "GCOV AFTER 2 CARDTEST" >> unittestresults.out
	./cardtest3 >> unittestresults.out
	echo "GCOV AFTER 3 CARDTEST" >> unittestresults.out
	./cardtest4 >> unittestresults.out
	echo "GCOV AFTER 4 CARDTEST" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	./playdom 3 >> unittestresults.out
	echo "GCOV AFTER PLAYING A GAME" >> unittestresults.out
	gcov dominion.c >> unittestresults.out	
	
	
all: playdom player

clean:
	rm -f *.o unittestresults.out playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM

CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

#randomtestcardadventurer: randomtestcardadventurer.c dominion.o
#	gcc -o randomtestcardadventurer -g  randomtestcardadventurer.c dominion.o rngs.o $(CFLAGS)

#randomtestcard1: randomtestcard1.c dominion.o
#	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

#randomtestcard2: randomtestcard2.c dominion.o
#	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

cardTest1: dominion.o playdom.c
	gcc -o cardTest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardTest2: dominion.o playdom.c
	gcc -o cardTest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardTest3: dominion.o playdom.c
	gcc -o cardTest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardTest4: dominion.o playdom.c
	gcc -o cardTest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o playdom.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o playdom.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer: dominion.o playdom.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)


t1: cardTest1
	cardTest1 >> TeammateBugs.out
	cardTest2 >> TeammateBugs.out
	cardTest3 >> TeammateBugs.out
	cardTest4 >> TeammateBugs.out
	randomtestcard1 >> TeammateBugs.out
	randomtestcard2 >> TeammateBugs.out
	randomtestadventurer >> TeammateBugs.out

runRandomTests: randomtestcardadventurer randomtestcard1 randomtestcard2 cardTest1
	./randomtestcardadventurer &> randomtestcardadventurer.out
	gcov -b -f dominion.c >> randomtestcardadventurer.out
	./randomtestcard1 &> randomtestcard1.out
	gcov -b -f dominion.c >> randomtestcard1.out
	./randomtestcard2 &> randomtestcard2.out
	gcov -b -f dominion.c >> randomtestcard2.out
	cardTest1 >> unittestresults.out
#	cat dominion.c.gcov >> randomtestcardadventurer.out
#	cat dominion.c.gcov >> randomtestcard1.out
#	cat dominion.c.gcov >> randomtestcard2.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom cardTest1 cardTest2 cardTest3 cardTest4 randomtestcard1 randomtestcard2 randomtestadventurer
	cardTest1 >> TeammateBugs.out
	cardTest2 >> TeammateBugs.out
	cardTest3 >> TeammateBugs.out
	cardTest4 >> TeammateBugs.out
	randomtestcard1 >> TeammateBugs.out
	randomtestcard2 >> TeammateBugs.out
	randomtestadventurer >> TeammateBugs.out

clean:
	rm -f *.o randomtestcardadventurer randomtestcard1 randomtestcard2 playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out

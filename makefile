P2.out : Project2.o Game.o
	g++ Project2.o Game.o -o P2.out

Project2.o : Project2.cpp Game.h
	g++ -c -g Project2.cpp

Game.o : Game.cpp Game.h 
	g++ -c -g Game.cpp

P2C.out : Proj2Comp.o Game.o Game1.o Game2.o
	g++ Proj2Comp.o Game.o Game1.o Game2.o -o P2C.out

Game1.o : Game.cpp Game.h seds1
	sed -f seds1 Game.h > Game1.h
	sed -f seds1 Game.cpp > Game1.cpp
	g++ -c -g Game1.cpp

Game2.o : Game.cpp Game.h seds2
	sed -f seds2 Game.h > Game2.h
	sed -f seds2 Game.cpp > Game2.cpp
	g++ -c -g Game2.cpp


clean :
	rm Game.o
	rm Project2.o

run :
	./P2.out

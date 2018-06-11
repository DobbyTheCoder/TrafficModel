output:	mainAI.o trai.o dead.o
	g++ mainAI.o trai.o dead.o -o output

dead.o: dead.cpp
	g++ -c dead.cpp

mainAI.o: mainAI.cpp
	g++ -c mainAI.cpp

trai.o: trai.cpp trai.h
	g++ -c trai.cpp

clean:
	rm *.o output
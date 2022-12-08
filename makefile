HashDict: HashDict.o main.o
	g++ HashDict.o main.o -o HashDict

HashDict.o: Node.h TimeInterval.h  HashDict.h HashDict.cpp
	g++ -c HashDict.cpp

main.o: main.cpp HashDict.h
	g++ -c main.cpp

clean:
	rm -f *.o
	rm HashDict
run: HashDict
	./HashDict
valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./HashDict

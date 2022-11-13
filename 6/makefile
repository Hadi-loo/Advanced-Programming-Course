CC = g++ --std=c++11
EXE_FILE = permitMaker.out

$(EXE_FILE): main.o organization.o document.o
	$(CC) main.o organization.o document.o -o $(EXE_FILE)
main.o: main.cpp organization.hpp document.hpp main.hpp
	$(CC) -c main.cpp -o main.o
organization.o: organization.cpp organization.hpp main.hpp
	$(CC) -c organization.cpp -o organization.o
document.o: document.cpp document.hpp organization.hpp main.hpp
	$(CC) -c document.cpp -o document.o 
clean:
	rm *.o

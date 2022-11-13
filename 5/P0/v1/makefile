CC = g++ --std=c++11
EXE_FILE = billiards.out

$(EXE_FILE): main.o table.o ball.o
	$(CC) table.o ball.o main.o -o $(EXE_FILE)

main.o: main.cpp table.hpp ball.hpp
	$(CC) -c main.cpp -o main.o

table.o: table.cpp table.hpp
	$(CC) -c table.cpp -o table.o

ball.o: ball.cpp ball.hpp table.hpp
	$(CC) -c ball.cpp -o ball.o

clean:
	rm *.o *.out
PROG = GraphTester
CC = g++
OBJS = Graph.o graphTester.o Player.o
CPPFLAGS = -Wall -std=c++11

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)
Graph.o: Graph.h
	$(CC) $(CPPFLAGS) -c Graph.cpp
Player.o: Player.h
	$(CC) $(CPPFLAGS) -c Player.cpp
graphTester.o:
	$(CC) $(CPPFLAGS) -c graphTester.cpp
clean:
	$(RM) $(PROG) $(OBJS)

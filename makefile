PROG = expGame
CC = g++
OBJS = main.o Graph.o
CPPFLAGS = -Wall -std=c++11
LINK =  -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi  -lXcursor -lXinerama

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LINK)
Graph.o: Graph.h
	$(CC) $(CPPFLAGS) -c Graph.cpp
main.o:
	$(CC) $(CPPFLAGS) -c main.cpp
clean:
	$(RM) $(PROG) $(OBJS)

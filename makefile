PROG = expGame
CC = g++
OBJS = main.o Graph.o Player.o
CPPFLAGS = -Wall -std=c++11
LINK =  -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -L/usr/lib64 -lGLEW -lXcursor -lXinerama

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LINK)
Graph.o: Graph.h
	$(CC) $(CPPFLAGS) -c Graph.cpp
Player.o: Player.h
	$(CC) $(CPPFLAGS) -c Player.cpp
main.o:
	$(CC) $(CPPFLAGS) -c main.cpp
clean:
	$(RM) $(PROG) $(OBJS)

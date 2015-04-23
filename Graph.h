#ifndef GRAPH_H
#define GRAPH_H
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

struct adjvertex;
struct vertex
{
	int xpos;
	int ypos;
	int id; // Numbered in order when add to graph
	int distance;
	std::vector<adjvertex> adj;
	bool visited;
	vertex* pVertex;
	vertex();
	vertex(int inXpos, int inYpos,int inId, bool inVisited)
	{
	    if(inXpos >= 0 && inYpos >=0)
        {
            xpos = inXpos;
            ypos = inYpos;
            visited = inVisited;
            id = inId;
            distance = -1;
            pVertex = NULL;
        }
	}
};
struct adjvertex
{
	vertex *v;
	int weight;
	int location;
	adjvertex();
	adjvertex(vertex * inV, int inWeight)
	{
        v = inV;
        weight = inWeight;
	}
};

class Graph
{
    public:
        Graph();
        virtual ~Graph();

        //Setters
        void addVertex(int inXpos, int inYpos, int inId, bool inVisited);
        void setXpos(int vertexIndex, int inXpos);
        void setYpos(int vertexIndex, int inYpos);
        //Getters
        int getYpos(int vertexIndex);
        int getXpos(int vertexIndex);
        int getId(int vertexIndex);
        bool getVisited(int vertexIndex);
        //Checkers
        bool isInVertices(unsigned index);
        //Map Creation
        void createMap(std::string mapFileName);
        // Draw
        void drawMap();
        // Input Functions
        vertex * getClickedNode(int mouseX, int mouseY, int height, int width); // returns NULL if nothing is found
    protected:
    private:
        const int MAP_ROWS = 8; // Map size in vertices
        const int MAP_COLS = 12;
        static const int MAP_SIZE = 96;
        std::vector<vertex> vertices;

        // Computer and Human Players
        vertex * ply;
        vertex * comp1;
        vertex * comp2;

        // Path Finding
        vertex * shortestPath(int startIndex, int endIndex);
        vertex * getNextMove(vertex * terminalVer);
        //int path[MAP_SIZE];
        //Map Creation Helpers
        bool createMapHelper(std::string mapFileName);
        void setMapSize(std::string line);
        int getNumCommas(std::string line);
        int findLocation(unsigned verIndex, unsigned adjVerIndex);
        std::string getCommaSeparatedWord(std::string *_line);

        //Other
        int findVertex(int inId);
        // Draw Helpers
        double getGlx(vertex * ver);
        double getGly(vertex * ver);
        void drawLine(vertex * ver1, vertex * ver2, double thickness);
        void drawNodes(vertex * ver, double _size);

};

#endif // GRAPH_H

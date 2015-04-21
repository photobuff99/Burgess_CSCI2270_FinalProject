#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <fstream>

struct adjvertex;
struct vertex
{
	int xpos;
	int ypos;
	int id; // Numbered in order when add to graph
	std::vector<adjvertex*> adj;
	bool visited;
	vertex();
	vertex(int inXpos, int inYpos,int inId, bool inVisited)
	{
	    if(inXpos >= 0 && inYpos >=0)
        {
            xpos = inXpos;
            ypos = inYpos;
            visited = inVisited;
            id = inId;
        }
	}
};
struct adjvertex
{
	vertex *v;
	int weight;
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
        bool getVisited(int vertexIndex);
        //Checkers
        bool isInVertices(int index);
        //Map Creation
        void createMap(std::string mapFileName);
    protected:
    private:
        std::vector<vertex> vertices;
        const int MAP_ROWS = 8; // Map size in vertices
        const int MAP_COLS = 12;

        //Map Creation Helpers
        bool createMapHelper(std::string mapFileName);
        void setMapSize(std::string line);
        int getNumCommas(std::string line);
        std::string getCommaSeparatedWord(std::string *_line);
};

#endif // GRAPH_H

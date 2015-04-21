#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>

struct adjvertex;
struct vertex
{
	int xpos;
	int ypos;
	std::vector<adjvertex*> adj;
	bool visited;
	vertex();
	vertex(int inXpos, int inYpos, bool inVisited)
	{
	    if(inXpos >= 0 && inYpos >=0)
        {
            xpos = inXpos;
            ypos = inYpos;
            visited = inVisited;
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
        void addVertex(int inXpos, int inYpos, bool inVisited);
        void setXpos(int vertexIndex, int inXpos);
        void setYpos(int vertexIndex, int inYpos);
        //Getters
        int getYpos(int vertexIndex);
        int getXpos(int vertexIndex);
        bool getVisited(int vertexIndex);

        //Checkers
        bool isInVertices(int index);

    protected:
    private:
        std::vector<vertex> vertices;
};

#endif // GRAPH_H

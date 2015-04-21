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
        void setXpos(int vertexIndex, int inXpos);
        void setYpos(int vertexIndex, int inYpos);

    protected:
    private:
        std::vector<vertex> vertices;
};

#endif // GRAPH_H

#ifndef GRAPH_H
#define GRAPH_H

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
    protected:
private:
	std::vector<vertex> vertices;
};

#endif // GRAPH_H

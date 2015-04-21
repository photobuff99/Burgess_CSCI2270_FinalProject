#include "Graph.h"


Graph::Graph()
{
}

Graph::~Graph()
{
    //dtor
}

//Setters

// Sets the xpos of the vertex at the give index
void Graph::setXpos(int vertexIndex, int inXpos)
{
    // Check that the index is positive
    if(vertexIndex >= 0)
    {
        vertices[vertexIndex].xpos = inXpos;
    }
    else
    {
        std::cout << "Please choose a positive index" << std::endl;
    }
}
// Sets the ypos of the vertex at the give index
void Graph::setYpos(int vertexIndex, int inYpos)
{
    // Check that the index is positive
    if(vertexIndex >= 0)
    {
        vertices[vertexIndex].ypos = inYpos;
    }
    else
    {
        std::cout << "Please choose a positive index" << std::endl;
    }
}

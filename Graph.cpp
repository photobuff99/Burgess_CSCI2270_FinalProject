#include "Graph.h"

// Error Checking Messages
const std::string INDEX_NOT_VALID = "Please choose a valid index";
const std::string FILE_OPEN_ERROR = "File did not open, map not populated";

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
    if(vertexIndex >= 0 && isInVertices(vertexIndex))
    {
        vertices[vertexIndex].xpos = inXpos;
    }
    else
    {
        std::cout << INDEX_NOT_VALID << std::endl;
    }
}
// Sets the ypos of the vertex at the give index
void Graph::setYpos(int vertexIndex, int inYpos)
{
    // Check that the index is positive
    if(vertexIndex >= 0 && isInVertices(vertexIndex))
    {
        vertices[vertexIndex].ypos = inYpos;
    }
    else
    {
        std::cout << INDEX_NOT_VALID << std::endl;
    }
}
/* Adds a vertex to the graph. Takes an x and y position and weather or not
   the vertex has be visited */
void Graph::addVertex(int inXpos, int inYpos, int inId, bool inVisited)
{
    vertex temp(inXpos,inYpos,inId,inVisited);
    vertices.push_back(temp);
}

//Getters
// For most getters returning -1 means they failed
int Graph::getYpos(int vertexIndex)
{
    if(vertexIndex >= 0 && isInVertices(vertexIndex))
    {
        return vertices[vertexIndex].ypos;
    }
    else
    {
        std::cout << INDEX_NOT_VALID << std::endl;
        return -1;
    }
}
int Graph::getXpos(int vertexIndex)
{
    if(vertexIndex >= 0 && isInVertices(vertexIndex))
    {
        return vertices[vertexIndex].xpos;
    }
    else
    {
        std::cout << INDEX_NOT_VALID << std::endl;
        return -1;
    }
}
bool Graph::getVisited(int vertexIndex)
{
    if(vertexIndex >= 0 && isInVertices(vertexIndex))
    {
        return vertices[vertexIndex].visited;
    }
    else
    {
        std::cout << INDEX_NOT_VALID << std::endl;
        return false;
    }
}

// Checkers
// Given an index in the Vertices vector it checks if it is within the vector
bool Graph::isInVertices(int index)
{
    if (index < vertices.size())
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Map Methods

// Takes the name of the map file and populates the graph with the nodes used and edges
// needs full documentation
void Graph::createMap(std::string mapFileName)
{
    //open file
    createMapHelper(mapFileName);

}
// needs full documentation
bool Graph::createMapHelper(std::string mapFileName)
{
    //open file
    std::ifstream mapFile;
    mapFile.open(mapFileName);

    if(mapFile.is_open())
    {
        int row = 0;
        int col = 0;
        int numEntry = 0;
        std::string line;
        std::string token;
        std::vector<std::string> lines;

        getline(mapFile,line); // first line contains other information
        while(getline(mapFile,line))
        {
            lines.push_back(line);
        }
        for(int i = 0;i < lines.size();i++)
        {
            line = lines[i];
            token = getCommaSeparatedWord(&line);
            token = getCommaSeparatedWord(&line);
            if(stoi(token) != -1)
            {
                vertex temp(0,0,numEntry,false);
                vertices.push_back(temp);
                std::cout << numEntry << std::endl;
            }
            numEntry++;
        }

        // need to add adj vers.
    }
    else
    {
        std::cout << FILE_OPEN_ERROR << std::endl;
        return false;
    }
}
//
int Graph::getNumCommas(std::string line)
{
    int numCommas = 0;
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] == ',')
        {
            numCommas++;
        }
    }
    return numCommas;
}

std::string Graph::getCommaSeparatedWord(std::string *_line)
{
    int i = 0;
    std::string word = "NONE";
    while(_line->at(i)!= ',')
    {
        i++;
    }
    word = _line->substr(0,i);
    *_line = _line->substr(i+1,std::string::npos);
    return word;
}

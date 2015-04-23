#include "Graph.h"
#include <queue>
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
// Adds a vertex to the graph. Takes an x and y position and weather or not
// the vertex has be visited
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
int Graph::getId(int vertexIndex)
{
    if(vertexIndex >= 0 && isInVertices(vertexIndex))
    {
        return vertices[vertexIndex].id;
    }
    else
    {
        std::cout << INDEX_NOT_VALID << std::endl;
        return -1;
    }
}

// Checkers
// Given an index in the Vertices vector it checks if it is within the vector
bool Graph::isInVertices(unsigned index)
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
        std::string line;
        std::string token;
        std::vector<std::vector<int> > mapVec {{-1}};
        mapVec.pop_back();

        // int numEntry = 0;
        int commas = 0;
        int tempID = 0;
        getline(mapFile,line); // first line contains other information
        while(getline(mapFile,line)) // make map vector
        {
            commas = getNumCommas(line);
            std::vector<int> tempVec; // vector to hold each line is pushed into map
            for(int i = 0; i < commas;i++)
            {
                token = getCommaSeparatedWord(&line);

                tempID = stoi(token);
                tempVec.push_back(tempID);
            }
            mapVec.push_back(tempVec);
        }

        int row = 0;
        int col = 0;
        for(unsigned i = 0; i < mapVec.size(); i++)
        {
            if(mapVec[i][1] != -1) // If vertex is used
            {   row = mapVec[i][0] % MAP_ROWS; col = mapVec[i][0] / MAP_ROWS;
                vertex temp(col,row,mapVec[i][0],false);// Put vertex in verticies with id
                vertices.push_back(temp);
                std::cout << "Adding: " << mapVec[i][0] << " Row: "<< row << " Col: "<< col << std::endl;
            }
            else
            {
                mapVec.erase(mapVec.begin()+i);
                i--;
            }
        }
        int vertexIndex;
        for(unsigned i = 0; i < vertices.size(); i++)
        {
            //std::cout << vertices[i].id << " "<< col << " " << row << std::endl;
            for(unsigned j = 1; j < mapVec[i].size();j++)
            {
                vertexIndex = findVertex(mapVec[i][j]); // given the id of the vertex link adj vert.
                adjvertex temp(&vertices[vertexIndex],1);
                vertices[i].adj.push_back(temp);
            }
        }
        for(unsigned i = 0; i < vertices.size(); i++)
        {
            for(unsigned j = 0; j < vertices[i].adj.size();j++)
                {

                    vertices[i].adj[j].location = findLocation(i,j);
                }
        }
        for (unsigned i = 0; i < vertices.size(); i++)
        {
            std::cout << "Id: " << vertices[i].id << std::endl;
            for(unsigned j = 0; j < vertices[i].adj.size();j++)
                {
                   std::cout << " |Adj: " << vertices[i].adj[j].v->id << " Loc: " << vertices[i].adj[j].location << " |";
                }
            std::cout << std::endl;
        }
    }
    else
    {
        std::cout << FILE_OPEN_ERROR << std::endl;
        return false;
    }
    mapFile.close();
    return true;
}
// Given the index of a vertex and one of its adjcent vertices finds the location od adj vertex.
int Graph::findLocation(unsigned verIndex, unsigned adjVerIndex)
{
    int xVer, yVer, xAdj, yAdj;
    xVer = vertices[verIndex].xpos;
    yVer = vertices[verIndex].ypos;
    xAdj = vertices[verIndex].adj[adjVerIndex].v->xpos;
    yAdj = vertices[verIndex].adj[adjVerIndex].v->ypos;
    //std::cout << vertices[verIndex].adj[adjVerIndex].v->id << " X: " << xAdj << " Y: " << yAdj << std::endl;
    if(xVer-1 == xAdj && yVer-1 == yAdj)
    {
        return 0;
    }
    else if(xVer == xAdj && yVer-1 == yAdj)
    {
        return 1;
    }
    else if(xVer+1 == xAdj && yVer-1 == yAdj)
    {
        return 2;
    }
    else if(xVer+1 == xAdj && yVer == yAdj)
    {
        return 3;
    }
    else if(xVer+1 == xAdj && yVer+1 == yAdj)
    {
        return 4;
    }
    else if(xVer == xAdj && yVer+1 == yAdj)
    {
        return 5;
    }
    else if(xVer-1 == xAdj && yVer+1 == yAdj)
    {
        return 6;
    }
    else if(xVer-1 == xAdj && yVer == yAdj)
    {
        return 7;
    }
    else
    {
        return -1;
    }

}
int Graph::getNumCommas(std::string line)
{
    int numCommas = 0;
    for(unsigned i = 0; i < line.size(); i++)
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

// Others
int Graph::findVertex(int inId)
{
    unsigned i = 0;
    bool found = false;
    while(i < vertices.size() && !found)
    {
        if(vertices[i].id == inId)
        {
           found = true;
        }
        i++;
    }
    if(found)
        return i -1;
    else
        return -1;
}
// PathFinding
vertex* Graph::shortestPath(int startIndex, int endIndex)
{
    std::queue<vertex*> Q;
    vertex * u;
    vertex * w;
    vertex * start = &vertices[startIndex];
    vertex * ending = &vertices[endIndex];
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
    }
    start->visited = true;
    start->distance = 0;
    Q.push(start);
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        for(unsigned i = 0; i < u->adj.size(); i++)
        {
            w = u->adj[i].v;
            if(w->visited == false)
            {
                w->pVertex = u;
                w->distance = u->distance + 1;
                if(w == ending)
                {
                    return w;
                }
                else
                {
                    w->visited = true;
                    Q.push(w);
                }
            }
        }
    }
    return NULL;
}
vertex* Graph::getNextMove(vertex * terminalVer)
{
    vertex * u;
    vertex * j;
    vertex * w;
    u = terminalVer;
    while( u != NULL)
    {
        w = j;
        j = u;
        u = u->pVertex;
    }
    return w;
}
// Drawing
double Graph::getGlx(vertex * ver)
{
    int xTempPos = ver->xpos;
    double y;
    y = ((double)xTempPos)/6.0 - 11.0/12.0;
    return y;
}
double Graph::getGly(vertex * ver)
{
    int yTempPos = ver->ypos;
    double y;
    y = (-(double)yTempPos)/(4.0) + (7.0/8.0);
    return y;
}
void Graph::drawMap()
{

    for (unsigned i = 0; i < vertices.size(); i++)
    {
        for (unsigned j = 0; j < vertices[i].adj.size(); j++)
        {
            drawLine(&vertices[i], vertices[i].adj[j].v, 0.01);
        }
    }
    drawLine(&vertices[0], &vertices[1], .01);
}
void Graph::drawLine(vertex * ver1, vertex * ver2, double thickness)
{
    double cenx1,ceny1,cenx2,ceny2;
    cenx1 = getGlx(ver1);
    ceny1 = getGly(ver1);
    cenx2 = getGlx(ver2);
    ceny2 = getGly(ver2);
    std::cout << cenx1 << " " << cenx2 << std::endl;
    // search for index in ver1's adj list for ver2 id
    int adjLocation = -1;
    // bool found = false;

    for(unsigned i = 0; i < ver1->adj.size(); i++)
    {

        if(ver2 == ver1->adj[i].v)
        {
            //std::cout << "DDDDDDDDDDD" << std::endl;
            adjLocation = ver1->adj[i].location;
            // found = true;
        }


    }


        if (adjLocation == 0)
        {
        glColor3b(58, 67, 70);
        glBegin(GL_QUADS);
        glVertex2f(cenx2 + thickness/sqrt(2), ceny2 + thickness/sqrt(2));
        glVertex2f(cenx2 - thickness/sqrt(2), ceny2 - thickness/sqrt(2));
        glVertex2f(cenx1 - thickness/sqrt(2), ceny1 - thickness/sqrt(2));
        glVertex2f(cenx1 + thickness/sqrt(2), ceny1 + thickness/sqrt(2));
        glEnd();
        }

        else if (adjLocation == 4)
        {
        glColor3b(58, 67, 70);
        glBegin(GL_QUADS);
        glVertex2f(cenx1 + thickness/sqrt(2), ceny1 + thickness/sqrt(2));
        glVertex2f(cenx1 - thickness/sqrt(2), ceny1 - thickness/sqrt(2));
        glVertex2f(cenx2 - thickness/sqrt(2), ceny2 - thickness/sqrt(2));
        glVertex2f(cenx2 + thickness/sqrt(2), ceny2 + thickness/sqrt(2));
        glEnd();
        }

        else if (adjLocation == 6)
        {
        glColor3b(58, 67, 70);
        glBegin(GL_QUADS);
        glVertex2f(cenx1 + thickness/sqrt(2), ceny1 - thickness/sqrt(2));
        glVertex2f(cenx1 - thickness/sqrt(2), ceny1 + thickness/sqrt(2));
        glVertex2f(cenx2 - thickness/sqrt(2), ceny2 + thickness/sqrt(2));
        glVertex2f(cenx2 + thickness/sqrt(2), ceny2 - thickness/sqrt(2));
        glEnd();
        }

        else if (adjLocation == 2)
        {
            glColor3b(58, 67, 70);
            glBegin(GL_QUADS);
            glVertex2f(cenx1 - thickness/sqrt(2), ceny1 + thickness/sqrt(2));
            glVertex2f(cenx1 + thickness/sqrt(2), ceny1 - thickness/sqrt(2));
            glVertex2f(cenx2 + thickness/sqrt(2), ceny2 - thickness/sqrt(2));
            glVertex2f(cenx2 - thickness/sqrt(2), ceny2 + thickness/sqrt(2));
            glEnd();
        }

        else if (adjLocation == 1)
        {
            glColor3b(58, 67, 70);
            glBegin(GL_QUADS);
            glVertex2f(cenx1 - thickness, ceny2);
            glVertex2f(cenx1 - thickness, ceny1);
            glVertex2f(cenx1 + thickness, ceny1);
            glVertex2f(cenx1 + thickness, ceny2);
            glEnd();
        }

        else if (adjLocation == 5)
        {
            glColor3b(58, 67, 70);
            glBegin(GL_QUADS);
            glVertex2f(cenx1 - thickness, ceny1);
            glVertex2f(cenx1 - thickness, ceny2);
            glVertex2f(cenx1 + thickness, ceny2);
            glVertex2f(cenx1 + thickness, ceny1);
            glEnd();
        }

        else if (adjLocation == 3)
        {
            glColor3b(58, 67, 70);
            glBegin(GL_QUADS);
            glVertex2f(cenx1 , ceny1 + thickness);
            glVertex2f(cenx1, ceny1 - thickness);
            glVertex2f(cenx2, ceny1 - thickness);
            glVertex2f(cenx2, ceny1 + thickness);
            glEnd();
        }

        else if (adjLocation == 7)
        {
            glColor3b(58, 67, 70);
            glBegin(GL_QUADS);
            glVertex2f(cenx2 , ceny1 + thickness);
            glVertex2f(cenx2, ceny1 - thickness);
            glVertex2f(cenx1, ceny1 - thickness);
            glVertex2f(cenx1, ceny1 + thickness);
            glEnd();
        }


}

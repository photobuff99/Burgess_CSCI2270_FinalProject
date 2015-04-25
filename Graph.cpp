#include "Graph.h"
#include <queue>
#include <stack>
// Error Checking Messages
const std::string INDEX_NOT_VALID = "Please choose a valid index";
const std::string FILE_OPEN_ERROR = "File did not open, map not populated";
const std::string DRAW_ERROR = "Something that did not draw...";
const std::string NULL_ERROR = "Something was NULL";

//Descriptions are before the function.

Graph::Graph()
{

}

Graph::Graph(std::string fileName)
{
    createMapHelper(fileName);
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


int Graph::getId(int vertexIndex) //getter that gets ID
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
/*
 Description: Given an index in the Vertices vector it checks if it is within the vector
 Proto: void drawLine(vertex *,vertex *, double)
 Example Call:
 Pre:
 Post:
 */
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

//Map Methods
/*
 Takes the name of the map file and populates the graph with the nodes, edges and location information
 Proto: void createMap(string)

 Example Call:

 Pre: graph file must be formated in the correct way

 Post: vertices is populated and all edge and adjacency information is held is vector of adjVertex
 */
void Graph::createMap(std::string mapFileName)
{
    //open file
    createMapHelper(mapFileName);
}
/*
 Takes the name of the map file and populates the graph with the nodes, edges and location information
 Proto: void createMap(string)

 Example Call:

 Pre: graph file must be formated in the correct way

 Post: vertices is populated and all edge and adjacency information is held is vector of adjVertex
 */
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
        int counter = 0;
        for(unsigned i = 0; i < mapVec.size(); i++)
        {
            if(mapVec[i][1] != -1) // If vertex is used
            {   row = mapVec[i][0] % MAP_ROWS; col = mapVec[i][0] / MAP_ROWS;
                vertex temp(col,row,mapVec[i][0],false);// Put vertex in verticies with id
                vertices.push_back(temp);
                std::cout << "Index: " << counter++ << " Adding: " << mapVec[i][0] << " Row: "<< row << " Col: "<< col << std::endl;
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
        /*for (unsigned i = 0; i < vertices.size(); i++)
        {
            std::cout << "Id: " << vertices[i].id << std::endl;
            for(unsigned j = 0; j < vertices[i].adj.size();j++)
                {
                   std::cout << " |Adj: " << vertices[i].adj[j].v->id << " Loc: " << vertices[i].adj[j].location << " |";
                }
            std::cout << std::endl;
        }*/
    }
    else
    {
        std::cout << FILE_OPEN_ERROR << std::endl;
        return false;
    }
    mapFile.close();
    comp1 = &vertices[0];
    player = &vertices[50];
    win = &vertices[19];
    return true;
}
/*
 Given the index of a vertex and one of its adjcent vertices, finds the location of the adj vertex
 denoted by an int 0-7. The adjacent spaces to a vertex are labed for the top-left corner(0) moving
 clock-wise until you reach the space before the one you started at (7). This function is called
 by createMapHelper.
 Proto: int findLocation(unsigned,unsigned)
 Pre: vertices must be populated
 Post: adjvertex varible loction is set to the found value
 */
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
/*
 Given a string this function gives back the number of commas. This function is called by createMapHelper.
 Proto: int getNumCommas(string)
 Pre: nothing
 Post: nothing
 */
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
/*
 Given a string it returns a substring of everything before the first comma it encounters and then removes that substring
 from the line it has been given.
 Proto: string getCommaSeparatedWord(string *)
 Pre: string it is given should have a comma in it
 Post: string given is now substring with first comma separated value removed
 */
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
/*
 Given a vertex's id findVertex returns the index in the vector vertices of that vertex
 Proto: int getNumCommas(int)
 Example Call:
 Pre: nothing
 Post: nothing
 */
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
/*
 Description: Given pionters to the start and end vertex's the function finds the shortest path between them and returns
 the ending vertex's address.

 Proto: vertex* shortestPath(vertex *,vertex *)
 Example Call:

 Pre: the vertices vector must be populated

 Post: each vertex's pVertex varible is set to the address of the perivous vertex, the path can be extracted by starting
 at the terminal index and moving back through pVertex's until you get to the starting vertex.

 */
vertex* Graph::shortestPath(vertex * start, vertex * ending)
{
    if (start == ending)
    {
        return NULL;
    }
    std::queue<vertex*> Q;
    vertex * u;
    vertex * w;
    //vertex * start = &vertices[startIndex];
    //vertex * ending = &vertices[endIndex];
    for(unsigned i = 0; i < vertices.size(); i++)
    {
        vertices[i].visited = false;
        vertices[i].pVertex = NULL;
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
/*
 Finds the next move that the computer player should take towards the location of the human player,
 takes the vertex of the human player and returns the vertex of where the computer should move next.
 Proto: vertex*  getNextMove(vertex *)
 Pre: shortestPath must be call first, with the arugments of start = computer's vertex and ending = player's vertex
 Post: nothing
 */
vertex* Graph::getNextMove(vertex * terminalVer)
{
    vertex *u;
    std::stack<vertex*> S;
    u = terminalVer;
    while( u != NULL)
    {
        std::cout << " S: " << u->id;
        S.push(u);
        u = u->pVertex;
    }
    std::cout << std::endl;
    S.pop();
    return S.top();
}
// Drawing
/*
 Given a vertex the getGlx method converts its xpos to a gl distance between -1 and 1 and returns it
 Proto: double Graph::getGlx(vertex *)
 Pre: the vertices vector must be populated, so each vertex has an xpos
 Post: nothing
 */
double Graph::getGlx(vertex * ver)
{
    int xTempPos = ver->xpos;
    double y;
    y = ((double)xTempPos)/6.0 - 11.0/12.0;
    return y;
}
/*
 same a getGlx but for y
 */
double Graph::getGly(vertex * ver)
{
    int yTempPos = ver->ypos;
    double y;
    y = (-(double)yTempPos)/(4.0) + (7.0/8.0);
    return y;
}
//Map Drawing
/*
 Description:
 Proto: void drawMap()
 Example Call:
 Pre:
 Post:
 */

void Graph::drawMap()
{

    for (unsigned i = 0; i < vertices.size(); i++)
    {

        for (unsigned j = 0; j < vertices[i].adj.size(); j++)
        {
            drawLine(&vertices[i], vertices[i].adj[j].v, 0.01);
        }
        glColor3b(207, 52, 0); // Connection colors
        drawNode(&vertices[i], .04);
    }
    glColor3b(127, 117, 118); // Node colors
    for (unsigned i = 0; i < vertices.size(); i++)
    {
        drawNode(&vertices[i], .04);
    }
    //drawLine(&vertices[0], &vertices[1], .01);
}

//Drawing Connecting Lines (drawing the paths of the graph with OpenGL)
/*
Description:
Proto: void drawLine(vertex *,vertex *, double)
Example Call:
Pre:
Post:
*/

void Graph::drawLine(vertex * ver1, vertex * ver2, double thickness)
{
    if( ver1 != NULL && ver2 != NULL)
    {
        double cenx1,ceny1,cenx2,ceny2;
        cenx1 = getGlx(ver1);
        ceny1 = getGly(ver1);
        cenx2 = getGlx(ver2);
        ceny2 = getGly(ver2);
        // std::cout << cenx1 << " " << cenx2 << std::endl;
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
}
void Graph::drawNode(vertex* ver, double _size) // can handle a null pointer
{
    double inXpos = getGlx(ver);
    double inYpos = getGly(ver);
    if(ver != NULL)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2d(inXpos,inYpos);
        for(int i =0; i <= 6; i++)
        {
            double angle = 2 * 3.14159 * i / 6;
            double x = cos(angle);
            double y = sin(angle);
            glVertex2d(x*_size + inXpos,y*(_size*1.3) + inYpos); //1.3 close to 1.5 which is 600/400
            //we can eventually pass in width and height into drawNodes to make it dependent
            //on screen size
        }
        glEnd();
    }
    else
    {
        std::cout << DRAW_ERROR << std::endl;
    }
}
vertex * Graph::getClickedNode(int mouseX, int mouseY, int height, int width)
{
   int xBin = width/12;
   int yBin = height/8;
   int inxPos = mouseX/xBin;
   int inyPos = mouseY/yBin;
   //std::cout << inxPos << " M " << inyPos << std::endl;
   unsigned i = 0;
   while(i < vertices.size())
   {
        if( vertices[i].xpos == inxPos && vertices[i].ypos == inyPos)
        {
            //std::cout << vertices[i].id << std::endl;
            return &vertices[i];
        }
        i++;
   }
   return NULL;
}
//Game Play
/*
 Description:
.

 Proto: void drawPlayer(vertex *, int, int, int, float, int int)

 Example Call: drawPlayer(vertex1, -128, -128, 127,  )
 Pre: The graph has to be populated; CreateGraph() would have to have been called.

 Post:

 */
void Graph::drawPlayer(vertex* ver, int R, int G, int B , float _size, int width, int height)
{
    if( ver != NULL)
    {
    double inXpos = getGlx(ver);
    double inYpos = getGly(ver);
    glBegin(GL_TRIANGLE_FAN);
    glColor3b(R,G,B);
    glVertex2d(inXpos,inYpos);
        for(int i =0; i <= 100; i++)
        {
            double angle = 2 * 3.14159 * i / 100;
            double x = cos(angle);
            double y = sin(angle);
            glVertex2d(x*_size + inXpos,y*_size*1.3 + inYpos);
            //technically an ellipse
            //1.3 close to 1.5 which is 600/400
            //ellipse dependent on width and height
        }
        glEnd();
    }
}


//is the vertex adjacent to player

/*
 Description:
 checks if the vertex is a valid adjacent vertex of player.
 This function uses player without passing it as an argument.

 Proto: bool isMoveAdj(vertex *)

 Example Call: isMoveAdj(mouseClickMove) If mouseClickMove was the corresponding node where the mouse was clicked.

 Pre: The graph has to be populated; CreateGraph() would have to have been called.

 Post:

 */


bool Graph::isMoveAdj(vertex * ver)


{
    if( ver != NULL)
    {
    for(int i = 0; i < player->adj.size();i++)
    {
        if( ver == player->adj[i].v )
        {
            return true;
        }
    }
    }
    else
    {
        std::cout << NULL_ERROR << std::endl;
    }
    return false;
}
void Graph::advGamestate(int mouseX, int mouseY,int height,int width) // assumes start pos set
{
    vertex * playerMove;
    vertex * temp;
    std::cout << comp1->id << std::endl;

    playerMove = getClickedNode(mouseX,mouseY,height,width);
    //puts node that corresponds with where mouse was clicked, into the temp vertex playerMove


    // std::cout << playerMove->id << std::cout;
    if(isMoveAdj(playerMove))
    {
        player = playerMove;
        drawPlayer(player,41,44,91,.07, width, height);
        if(isWin())
        {
             //glfwDestroyWindow(window);
             std::cout << "You Won :)" << std::endl;
             glfwTerminate();
             exit(EXIT_SUCCESS);
        }
        std::cout << "Player: " << player->id << std::endl;
        std::cout << "Comp: " << comp1->id << std::endl;
        temp = shortestPath(comp1,player);
        std::cout << temp ->id << std::endl;
        comp1 = getNextMove(temp);
        drawPlayer(comp1,70,45,45,.07, width, height); //blink color

        if(isLoss())
        {
             //glfwDestroyWindow(window);
             std::cout << "You Lost :(" << std::endl;
             glfwTerminate();
             exit(EXIT_SUCCESS);

        }

    }
}
void Graph::setup(int width, int height)
{
    glColor3b(121,112,88); // win node color
    drawNode(win,.04);
    glColor3b(41,44,91);
    drawPlayer(player,41, 44,91,.07, width, height); //stagnant color
    glColor3b(70,45,45);
    drawPlayer(comp1,70,45,45,.07, width, height); //stagnant color

}
bool Graph::isWin()
{
    if(player == win)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool Graph::isLoss()
{
    if(player == comp1)
    {
        return true;
    }
    else
    {
        return false;
    }
}


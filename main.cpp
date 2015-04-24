// Used the code from Getting Started With GLFW as the frame work
//http://www.glfw.org/docs/latest/quick.html
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include "Graph.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void currentDrawState(double X, double Y, int width, int height)
{
    glVertex2f(0.f +  X/(width/2) -1, .0f - Y/(height/2) + 1);
    glVertex2f(0.f + X/(width/2) -1, .5f - Y/(height/2) + 1);
    glVertex2f(.5f + X/(width/2) -1, .5f - Y/(height/2) + 1);

}
void drawBackground();

int main(int argc, char * argv[])
{
    int width = 1000;
    int height = 1000;
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(width, height, "Exp_Game", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    double X = 0;
    double Y = 0;
    double A = 0;
    double B = 0;
    int state = 0;
    Graph G;
    G.createMap("map.txt");
    int squareState = -1; //-1 so it's never equal to a node at first
    while (!glfwWindowShouldClose(window))
    {
        //float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        //ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        drawBackground();
        G.drawMap();

        glEnd();

        glfwGetCursorPos(window, &X, &Y);
        glfwGetWindowSize(window, &width, &height); //get windows current size

        //glBegin(GL_TRIANGLES)
        G.setup();
        if (state == GLFW_PRESS)
        {
            currentDrawState(X, Y, width, height);
            A = X;
            B = Y;
            G.advGamestate(A,B,height,width);
        }

                  /*  vertex * gar = G.getClickedNode(A,B,height,width);
            if( gar != NULL && gar->id != squareState)
            {
            std::cout << gar->id << std::endl;
            squareState = gar->id;
            } // this can
            G.drawPlayer(gar,100,50,90,.06);*/
        currentDrawState(A, B, width, height);

        state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void drawBackground()
{
    bool color = false;
        for (int i = 0; i < 8; i++)
        {

            if (color)
            {
                glColor3b(112, 109, 125);
                color = !color;
            }

            else
            {
                glColor3b(105, 100, 99);
                color = !color;
            }

            for(int j = 0; j<12;j++)
            {
                if (color)
                {
                    glColor3b(112, 109, 125);
                    color = !color;
                }

                else
                {
                    glColor3b(105, 100, 99);
                    color = !color;
                }
                glBegin(GL_TRIANGLE_STRIP);
                glVertex2f(-1+j/6.0,1 - i/4.0);
                glVertex2f(-1+j/6.0,0.75 - i/4.0);
                glVertex2f(-(5.0/6.0)+j/6.0, 1 - i/4.0);
                glVertex2f(-(5.0/6.0)+j/6.0, 0.75 - i/4.0);
                glEnd();
            }

        }
}


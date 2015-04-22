
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
    double X, Y;
    
    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        glfwGetCursorPos(window, &X, &Y);
        glColor3b(20, 90, 50);
        glBegin(GL_TRIANGLES);
        glVertex2f(0.f +  X/320 -1, .0f - Y/240 + 1);
        glVertex2f(0.f + X/320 -1, .5f - Y/240 + 1);
        glVertex2f(.5f + X/320 -1, .5f - Y/240 + 1);
        glEnd();
        
        glColor3b(40, 10, 50);
        glBegin(GL_TRIANGLE_FAN);
        for(int i =0; i <= 300; i++){
            double angle = 2 * 3.14159 * i / 300;
            double x = cos(angle);
            double y = sin(angle);
            glVertex2d(x,y);
        }
        glEnd();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


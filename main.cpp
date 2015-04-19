//#include <iostream>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <string>
//#include <fstream>




/*
std::string LoadFileToString(const char* filepath)
{
    std::string fileData;
    std::ifstream stream(filepath, std::ios::in);
    
    if (stream.is_open())
    {
        std::string line = "";
        
        while (getline(stream, line))
        {
            fileData += "\n" + line;
        }
        
        stream.close();
    }
    
    return fileData;
}

GLuint LoadShaders(const char* vertShaderPath, const char* fragShaderPath)
{
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::string vertShaderSource = LoadFileToString(vertShaderPath);
    std::string fragShaderSource = LoadFileToString(fragShaderPath);
    
    const char* rawVertShaderSource = vertShaderSource.c_str();
    const char* rawFragShaderSource = fragShaderSource.c_str();
    
    glShaderSource(vertShader, 1, &rawVertShaderSource, NULL);
    glShaderSource(fragShader, 1, &rawFragShaderSource, NULL);
    
    glCompileShader(vertShader);
    glCompileShader(fragShader);
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    
    glLinkProgram(program);
    
    return program;
}

int main()
{
    if (glfwInit() == false) //did not succeed
    {
        fprintf(stderr, "GLFW failed to initialize.");
        return -1;
    }
    
    //glfwWindowHint(GLFW_SAMPLES, 4);
 
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //use version 3.3
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_OPENGL_PROFILE);
 
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    
    
    
    GLFWwindow* window;
    window = glfwCreateWindow(640, 480, "My OpenGL", NULL, NULL);
    
    if (!window) // if window wasn't created
    {
        fprintf(stderr, "Window failed to create");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); // the window OPENGL will be applied to
    glewExperimental = true;
    
    if (glewInit() != GLEW_OK) // if glew initialization is not okay
    {
        fprintf(stderr, "GLEW failed to initialize.");
        glfwTerminate();
        return -1;
    }
    
    if (!GLEW_VERSION_3_2)
    {
        throw std::runtime_error("OpenGL 3.2 API is not available.");
    }
    
    //generate vertex array object
    GLuint vaoID; //gluint is what opengl uses for IDs
    glGenVertexArrays(1, &vaoID); //
    fprintf(stdout, "%d", vaoID);
    
    glBindVertexArray(vaoID); //we are going to use this kind of vao
    
    
    
    static const GLfloat verts[] = {
        //x, y, z
        -1.0, -1.0f, 0.0f,
        1.0, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };
    
    GLuint program = LoadShaders("shader.vertshader", "shader.fragshader");
    
    
    //Generate VBO
    GLuint vboID;
    
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID); //bind buffer, we are using this id
    glBufferData(GL_ARRAY_BUFFER, 7*sizeof(verts), verts, GL_STATIC_DRAW);
    
    fprintf(stdout, "%d", glGetError());
    

    do
    {
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(0); //shaders
        
        glBindBuffer(GL_ARRAY_BUFFER, vboID); //bind buffer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        
        
        glUseProgram(program);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } while (glfwWindowShouldClose(window) == false);
    
    return 0;
}


*/

#include "/usr/local/include/GL/glew.h"
#define GLFW_DLL
#include "/usr/local/include/GLFW/glfw3.h"
#include <iostream>

using namespace std;

int main( void )
{
    
    double x = 0;
    double y = 0;
    
    
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        return 1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
    if (!window) {
        fprintf(stderr, "ERROR: could not open window with GLFW3\n");
        glfwTerminate();
        return 1;
    }
    
    
    
    
    glfwMakeContextCurrent (window);
    
    glewExperimental = GL_TRUE;
    glewInit ();
    
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    float points[] = {
        
        //0.0f,  0.5f,  0.0f,
        //0.5f, -0.5f,  0.0f,
        //-0.5f, -0.5f,  0.0f,
        
        /*
        -0.1f,  0.1f, 0.0f,// Top-left
        
        
        0.1f, -0.1f, 0.0f,// Bottom-right
        
        -0.1f, -0.1f, 0.0f,  // Bottom-left
        
        0.1f,  0.1f, 0.0f// Top-right
        */
        
        0.0f,  0.0f, 0.0f, // center
        
        0.05f, -0.1f, 0.0f,// Bottom-right
        
        -0.05f, -0.1f, 0.0f,  // Bottom-left
        
        
        
        0.0f,  0.0f, 0.0f, // center
        
        0.05f, 0.1f, 0.0f,// top-right
        
        -0.05f, 0.1f, 0.0f,  // top-left
        
        
        
        0.0f,  0.0f, 0.0f, // center
        
        -0.05f, -0.1f, 0.0f, //
        
        -0.05f, 0.1f, 0.0f,  //
        
        
        -0.09f,  0.0f, 0.0f, //
        
        -0.05f, -0.1f, 0.0f, //
        
        -0.05f, 0.1f, 0.0f,  //
        
        
        0.0f,  0.0f, 0.0f, // center
        
        0.05f, -0.1f, 0.0f, //
        
        0.05f, 0.1f, 0.0f,  //
        
        
        0.09f,  0.0f, 0.0f, //
        
        0.05f, -0.1f, 0.0f, //
        
        0.05f, 0.1f, 0.0f,  //
        
        
        
        
        
        
    
    };
    
   
    
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 64 * sizeof(float), points, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    //glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); //number of indices in second param
    
    const char* vertex_shader =
    "#version 400\n"
    "in vec3 vp;"
    "uniform float Xposition;"
    "uniform float Yposition;"
    "void main () {"
    "  gl_Position = vec4 (vp.x + Xposition, vp.y - Yposition, vp.z, 1.0);"
    "}";
    
    const char* fragment_shader =
    "#version 400\n"
    "uniform vec3 triangleColour;"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (triangleColour, 1.0);"
    "}";
    

    
    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);
    
    /*
    GLuint elements[] = {
        0, 1, 2,
        1, 2, 3
    };
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    
    */
    
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);;
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, vs);
    glAttachShader(shader_programme, fs);
    glLinkProgram(shader_programme);
    
   
    
    GLint uniColor = glGetUniformLocation(shader_programme, "triangleColour");//take out color from
    //shader to modify
    GLint XPos = glGetUniformLocation(shader_programme, "Xposition");
    GLint YPos = glGetUniformLocation(shader_programme, "Yposition");
    
    
    
    
    
    
    
    
    
    
    
    float points2[] = {
        
        //0.0f,  0.5f,  0.0f,
        //0.5f, -0.5f,  0.0f,
        //-0.5f, -0.5f,  0.0f,
        
        /*
         -0.1f,  0.1f, 0.0f,// Top-left
         
         
         0.1f, -0.1f, 0.0f,// Bottom-right
         
         -0.1f, -0.1f, 0.0f,  // Bottom-left
         
         0.1f,  0.1f, 0.0f// Top-right
         */
        
        0.3f,  0.3f, 0.0f,// Top-left
        
        
        0.3f, 0.4f, 0.0f,// Bottom-right
        
        0.4f, 0.3f, 0.0f // Bottom-left
        
        
        
    };
    
    
    
    GLuint vbo2 = 0;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points2, GL_STATIC_DRAW);
    
    GLuint vao2 = 0;
    glGenVertexArrays(1, &vao2);
    //glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArray(vao2);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); //number of indices in second param
    
    
    const char* vertex_shader2 =
    "#version 400\n"
    "in vec3 vp;"
    "uniform float Xposition2;"
    "uniform float Yposition2;"
    "void main () {"
    "  gl_Position = vec4 (vp.x + Xposition2, vp.y + Yposition2, vp.z, 1.0);"
    "}";
    
    const char* fragment_shader2 =
    "#version 400\n"
    "uniform vec3 triangleColour;"
    "out vec4 frag_colour;"
    "void main () {"
    "  frag_colour = vec4 (triangleColour, 1.0);"
    "}";
    
    
    
    // Create an element array
    //GLuint ebo2;
    //glGenBuffers(1, &ebo2);
    
    /*
     GLuint elements2[] = {
     0, 1, 2,
     1, 2, 3
     };
     
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
     
     */
    
    GLuint vs2 = glCreateShader(GL_VERTEX_SHADER);;
    glShaderSource(vs2, 1, &vertex_shader2, NULL);
    glCompileShader(vs2);
    
    GLuint fs2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs2, 1, &fragment_shader2, NULL);
    glCompileShader(fs2);
    
    GLuint shader_programme2 = glCreateProgram();
    glAttachShader(shader_programme2, vs2);
    glAttachShader(shader_programme2, fs2);
    glLinkProgram(shader_programme2);
    
    
    GLint uniColor2 = glGetUniformLocation(shader_programme2, "triangleColour");//take out color from
    //shader to modify
    GLint XPos2 = glGetUniformLocation(shader_programme2, "Xposition2");
    GLint YPos2 = glGetUniformLocation(shader_programme2, "Yposition2");
    

    
    
    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shader_programme);

        glBindVertexArray(vao);
        
        glUniform1f(XPos, (x/320) - 1.0);
        glUniform1f(YPos, (y/250) - 1.0);
        glUniform3f(uniColor, (y/630) -0.1 , (x/240), (x/640) -0.4); //take out color from shader to modify
        
        
        
        
        
        
        glfwGetCursorPos(window, &x,&y);
        cout << "x:" << x << endl;
        cout << "y:" << y << endl;
        
        //glBindVertexArrayAPPLE(vao);
        glDrawArrays(GL_TRIANGLES, 0, 18);
        //glDrawArrays(GL_TRIANGLES, 6, 9);
        // Draw a rectangle from the 2 triangles using 6 indices
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glUseProgram(shader_programme2);
        
        glBindVertexArray(vao2);
        
        
        
        glUniform1f(XPos2, 0.5);
        glUniform1f(YPos2, 0.5);
        glUniform3f(uniColor2, (y/640), (x/512) + 0.12, (x/640) -0.5);
        
        
        
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}
# Burgess_CSCI2270_FinalProject
<h2>Project Summary</h2>
<p> In this project we are creating a game involving graphs. There will be a board displayed on screen with various positons connected by paths. The player will start somewhere on the map, the goal will be to get to the end position. The computer will try to stop the player by moving its piece along the paths towards the player.  If the computer moves in to the same positon as the player the player loses. </p>
<h2>How to Run</h2>
<p> Lunix: g++ text.o -o main.a -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -L/usr/lib64 -lGLEW -lXcursor -lXinerama
 </p>
<h2>Dependencies</h2>
<p> This game requires GLFW and GLEW, OpenGL libraries. The user will be required to download the libraries. GLFW is required to create the window, context, and renderer of the game. GLEW is for additional OpenGL functionality. The game takes advantage of OpenGL's shader language by way of these libraries. g++ main.cpp -I/usr/local/include/GL -L/usr/local/lib -lGLEW -I/usr/local/include/GLFW -L/usr/local/lib -lGLFW -L/system/Library/Frameworks -framework OpenGL 
g++ -o main main.cpp -I/home/user/Libs/glew-1.12.0/include/GL -L/usr/local/lib/ -lGLEW -I/home/user/Libs/glfw-3.1.1/include/GLFW -L/usr/local/lib -lglfw3 -L/usr/lib/x86_64-linux-gnu/mesa/ -lGL -lX11 -lXxf86vm -lpthread -lXi -lXrandr -lXcursor -lXinerama
</p>
<h2>System Requirements</h2>
<p> Mac OSX or Lunix </p>
<h2>Group Members</h2>
<p> Jacob Burgess and Jose Canizares </p>
<h2>Contributors</h2>
<h2>Open Issues/Bugs</h2>

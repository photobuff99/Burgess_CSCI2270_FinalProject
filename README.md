# Burgess_CSCI2270_FinalProject
<h2>Project Summary</h2>
<p> In this project we are creating a game involving graphs. It is called expGame. There will be a board displayed on screen with various positons connected by paths. The player will start somewhere on the map, the goal will be to get to the end position. The computer will try to stop the player by moving its piece along the paths towards the player.  If the computer moves in to the same positon as the player the player loses. </p>
<h2>How to Run</h2>
<h3> Linux </h3>
<p>Run the makefile</p>
<h3> MAC OSX </h3>
<p> Download GLFW from the GLFW website. Open the zip file. Type and enter "make" in the directory of where you have this GLFW library. Then make sure libglfw.3.1.dylib and glfw3.h exist and make sure you know where they are. In the steps below, it is assumed the libglfw.3.1.dylib is under /usr/local/lib and glfw3.h is under /usr/local/include/GLFW. Then make sure you have the OpenGL framework "OpenGL.framework" in /system/Library/Frameworks. Now follow these steps:</p>
1.g++ -std=c++11 -c main.cpp
2.g++ -std=c++11 - c Graph.cpp
3.g++ -o expGame main.o Graph.o -L/usr/local/lib -I/usr/local/include/GLFW -L/usr/local/lib -lGLFW         -L/system/Library/Frameworks -framework OpenGL 
<h2>Dependencies</h2>
<p> This game requires GLFW, OpenGL library. The user will be required to download the library. GLFW is required to create the window, context, and renderer of the game. The game takes advantage of OpenGL's shader language by way of these libraries. See GLFW site for install instructions: http://www.glfw.org/. This stackoverflow post helped me install glfw on Ubuntu http://stackoverflow.com/questions/17768008/how-to-build-install-glfw-3-and-use-it-in-a-linux-project . Also before installing the dependencies for GLFW in the VM run the command 'sudo apt-get update'.
</p>
<h2>System Requirements</h2>
<p> Mac OSX or Lunix </p>
<h2>Group Members</h2>
<p> Jacob Burgess and Jose Canizares </p>
<h2>Contributors</h2>
<h2>Open Issues/Bugs</h2>
<p> If the player attempts to eat the computer, the program will seg fault. We suppose this has something to do with the shortest path algorithm. </p>
TODO
<p>Comment/explain methods and main programe</p>


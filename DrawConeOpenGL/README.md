# Drawing cone using openGL GLUT

![alt text](https://www.codemiles.com/download/file.php?id=1486)

In this example we draw a cone using opengGl/GLU and also we using idle function for animation. glutSolidCone function is used.

We also add an FPS counter in the window title. you can use a fps limiter funciont or without a limiter function

## Step by step how to use GLUT with Code::Blocks IDE:

-First get glut ZIP
![alt text](0 get glut zip.PNG)

-Copy glut32.dll to Windows/System32 folder
![alt text](1 copy glut32.dll to system32.PNG)

-Copy glut.h to Code::Blocks MinGW/include/GL folder
![alt text](2 copy gluth to mingw gl includes.PNG)

-Copy glut32.lib to Code::Blocks MinGW/lib/ folder
![alt text](3 copy glut32.lib to mingw libs.PNG)

-Add  library and options (-lopengl32 and -lglu32) to project build options
![alt text](4 add  library and options to project build options.PNG)

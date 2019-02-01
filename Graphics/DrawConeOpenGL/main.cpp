/**
https://www.codemiles.com/c-opengl-examples/drawing-cone-using-opengl-t9013.html
https://www.khronos.org/opengl/wiki/MinGW
https://blog.martincruz.me/2012/09/opengl-instalar-glut-en-codeblocks.html
https://www.opengl.org/resources/libraries/glut/glut_downloads.php
https://www.youtube.com/watch?reload=9&v=bd0o4l519J8
https://www.youtube.com/watch?v=CYDFQ1oJJdI
https://stackoverflow.com/questions/31058604/limiting-fps-in-glut
https://www.techiedelight.com/convert-std-string-const-char-cpp/

In this example we draw a cone using opengGl/GLU and also we using idle function for animation. glutSolidCone function is used.
we also add an FPS counter in the window title. you can use a fps limiter funciont or without a limiter function
*/

#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <time.h> // to fps counter
#include <string> // to manipulate window title

// limit fps
#define FPS 60
// cone rotation speed
#define ROTATE_SPEED 0.01
// window size WxH
#define WIDTH 600
#define HEIGHT 400
// cone colors
#define RED 0.8
#define GREEN 0.2
#define BLUE 0.1
// cone xyz position
#define X_POSITION 0.0
#define Y_POSITION 0.0
#define Z_POSITION -4.5
// angle of view in degrees
#define ANGLE_OF_VIEW 40.0
// near clipping plane distance
#define NEAR_CLIPPING_PLANE_DISTANCE 0.5
// far clipping plane distance
#define FAR_CLIPPING_PLANE_DISTANCE 20.0

using namespace std;

static GLfloat xRotated = 30, yRotated = 30, zRotated = 30;
// cone properties
static GLdouble base = 1, height = 1.5;
static GLint slices = 25, stacks = 25;

// fps
static int initialTime = time(NULL), finalTime, frameCount = 0;
static string Title = "Cone Rotating Animation. FPS: ";
static const GLfloat milliseconds = 1000 / FPS;

void showFps()
{
    frameCount++;
    finalTime = time(NULL);
    const int diff = finalTime - initialTime;
    if (diff > 0)
    {
        const string result = Title + std::to_string(frameCount / diff);
        glutSetWindowTitle(result.c_str()); // string to const char*
        frameCount = 0;
        initialTime = finalTime;
    }
}

// the main render function used as callback, called every frame
void displayCone()
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // note this when you decrease z like -8 the drawing will looks far or smaller
    glTranslatef(X_POSITION, Y_POSITION, Z_POSITION);
    // red color used to draw
    glColor3f(RED, GREEN, BLUE);
    // changing in transformation matrix.
    // rotation about x axis
    glRotatef(xRotated, 1.0f, 0.0f, 0.0f);
    // rotation about y axis
    glRotatef(yRotated, 0.0f, 1.0f, 0.0f);
    // rotation about z axis
    glRotatef(zRotated, 0.0f, 0.0f, 1.0f);
    // scaling transformation
    glScalef(1.0f, 1.0f, 1.0f);

    // built-in (glut library) function, draw you a cone
    glutSolidCone(base, height, slices, stacks);

    // flush buffers to screen
    glFlush();

    // swap buffers called because we are using double buffering
    glutSwapBuffers();
}

void reshapeCone(const int x, const int y)
{
    if(y == 0 || x == 0)
    {
        // nothing is visible then, so return
        return;
    }

    // set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // angle of view 40 degrees
    // near clipping plane distance 0.5
    // far clipping plane distance 20.0
    gluPerspective(ANGLE_OF_VIEW, static_cast<GLdouble>(x) / static_cast<GLdouble>(y), NEAR_CLIPPING_PLANE_DISTANCE, FAR_CLIPPING_PLANE_DISTANCE);

    // use the whole window for rendering
    glViewport(0, 0, x, y);
}

void idleCone()
{
    // you can use xRotated, yRotated or zRotated to rotate on the axis you want
    //xRotated += ROTATE_SPEED;
    yRotated += ROTATE_SPEED;
    //zRotated += ROTATE_SPEED;

    displayCone();

    // calculae fps logic now
    showFps();
}

void idleCone(int)
{
    // you can use xRotated, yRotated or zRotated to rotate on the axis you want
    //xRotated += milliseconds * ROTATE_SPEED;
    yRotated += milliseconds * ROTATE_SPEED;
    //zRotated += milliseconds * ROTATE_SPEED;

    glutPostRedisplay();
    glutTimerFunc(milliseconds, idleCone, 0);

    // calculae fps logic now
    showFps();
}

int main(int argc, char **argv)
{
    // initialize GLUT
    glutInit(&argc, argv);

    // double buffering used to avoid flickering problem in animation
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // window size
    glutInitWindowSize(WIDTH, HEIGHT);

    // create the window
    glutCreateWindow(Title.c_str());

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // assign the function used in events
    glutDisplayFunc(displayCone);
    glutReshapeFunc(reshapeCone);

    // use an unlimited fps function
    //glutIdleFunc(idleCone);
    // use a limited fps function. only register and call once.
    glutTimerFunc(milliseconds, idleCone, 0); // 1000 milliseconds = 1sec

    // let start glut loop
    glutMainLoop();
    return 0;
}

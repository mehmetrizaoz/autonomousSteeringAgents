#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h>

using namespace std;

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
            exit(0);
    }
}

//Initializes 3D rendering
void initRendering() {
    //Makes 3D drawing work when something is in front of something else
    glEnable(GL_DEPTH_TEST);
}

//Called when the window is resized
void handleResize(int w, int h) {
    //Tell OpenGL how to convert from coordinates to pixel values
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
    
    //Set the camera perspective
    glLoadIdentity(); //Reset the camera
    gluPerspective(45.0,                  //The camera angle
                   (double)w / (double)h, //The width-to-height ratio
                   1.0,                   //The near z clipping coordinate
                   200.0);                //The far z clipping coordinate
}

float _angle = 30.0f;

//Draws the 3D scene
void drawScene() {
    //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    
    glTranslatef(0.0f, 0.0f, -5.0f); //Move to the center of the triangle    
    
    glPushMatrix();
    glRotatef(_angle, 1.0f, 0.0f, 0.0f); //Rotate around x axes    
    glBegin(GL_TRIANGLES);    
    glVertex3f(0.0f, -0.25f, 0.0f);
    glVertex3f(-0.25f, 0.25f, 0.0f);
    glVertex3f(-1.00f, -0.25f, 0.0f);
    glEnd();
    glPopMatrix(); 
    
    glPushMatrix();
    glRotatef(_angle, 0.0f, 1.0f, 0.0f); //Rotate around y axes     
    glBegin(GL_TRIANGLES);    
    glVertex3f(1.5f, -0.25f, 0.0f);
    glVertex3f(1.0f, 0.25f, 0.0f);
    glVertex3f(-0.0f, -0.25f, 0.0f);
    glEnd();
    glPopMatrix();    
        
    glutSwapBuffers();
}

void update(int value) {
    _angle += 2.0f;
    if (_angle > 360) {
        _angle -= 360;
    }
    
    glutPostRedisplay(); //Tell GLUT that the display has changed
    
    //Tell GLUT to call update again in 25 milliseconds
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
    //Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    
    //Create the window
    glutCreateWindow("Transformations and Timers - videotutorialsrock.com");
    initRendering();
    
    //Set handler functions
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    
    glutTimerFunc(25, update, 0); //Add a timer
    
    glutMainLoop();
    return 0;
}










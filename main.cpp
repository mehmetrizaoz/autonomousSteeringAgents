#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

float angle = 30.0f;

float randomNegate(float num){
    if(rand() % 2 == 0)
       num *= -1;
    return num;
}

void createAgent(float c_x, float c_y){ 
    glPushMatrix();
    //glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);    
    glVertex3f( c_x - 0.29,  c_y - 0.50f, 0.00f);
    glVertex3f( c_x - 0.29f, c_y + 0.50f, 0.00f);
    glVertex3f( c_x + 0.57f, c_y, 0.00f);
    glEnd();
    glPopMatrix();
   
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
            exit(0);
    }
}

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

void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
    glLoadIdentity(); //Reset the drawing perspective
    
    glTranslatef(0.0f, 0.0f, -15.0f); //Move to the center of the triangle    

//agent origin array will be created at init
   float tx = float(rand() % 51) / 50.0;
   tx = randomNegate(tx);
   float ty = float(rand() % 51) / 50.0;
   ty = randomNegate(ty);   
      
    createAgent(tx, ty);
    createAgent(1,0);
    createAgent(-1,-1);    
    
    glutSwapBuffers();
}

void update(int value) {
    angle += 2.0f;
    if (angle > 360) {
        angle -= 360;
    }
    
    glutPostRedisplay(); //Tell GLUT that the display has changed
    glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    
    glutCreateWindow("Transformations and Timers - videotutorialsrock.com");
    glEnable(GL_DEPTH_TEST);
    
    glutDisplayFunc(drawScene);
    glutKeyboardFunc(handleKeypress);
    glutReshapeFunc(handleResize);
    
    glutTimerFunc(25, update, 0);
    
    glutMainLoop();
    return 0;
}










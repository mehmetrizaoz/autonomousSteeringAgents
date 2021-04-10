#include <iostream>
#include <stdlib.h> 
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>

using namespace std;

float angle = 30.0f;
int numberOfAgents = 23;    

class center{
public:
  float x;
  float y;
  center(float _x, float _y):x(_x),y(_y){};
};

vector<center *> agentCenters;


float randomNegate(float num){
    if(rand() % 2 == 0)
       num *= -1;
    return num;
}

void createAgent(center *c){ 
    glPushMatrix();
    //glRotatef(angle, 1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);    
    glVertex3f( c->x - 0.29,  c->y - 0.50f, 0.00f);
    glVertex3f( c->x - 0.29f, c->y + 0.50f, 0.00f);
    glVertex3f( c->x + 0.57f, c->y, 0.00f);
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
    
    glTranslatef(0.0f, 0.0f, -85.0f); //Move to the center of the triangle    

    
    for(auto it = agentCenters.begin(); it < agentCenters.end(); it++){
       createAgent(*it);
       
    }
   
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
    float x, y;
    srand (time(NULL));

    for(int i=0; i<numberOfAgents; i++){
       x = float(rand() % 5); 
       x = randomNegate(x);
       
       y = float(rand() % 5);
       y= randomNegate(y);       
       //aynısı çıkıyor!!!
       //cout << x << " " << y << endl;
       agentCenters.push_back(new center(x, y));
    }
    
    
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










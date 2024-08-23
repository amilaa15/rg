#include <GL/glut.h>
#include <iostream>

int windowWidth = 900;
int windowHeight = 900;

int scal=0;
float scalArg=1;
int inerAngle=0;

int posX=0;
int posY=0;

void init() {
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2,
             windowHeight / 2);
  glMatrixMode(GL_MODELVIEW);
}

void drawOuterPolygon() {
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(2, 0x1C47);
  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(40, 40);
  glVertex2f(-40, 40);
  glVertex2f(-40, -40);
  glVertex2f(40, -40);
  glEnd();
  glDisable(GL_LINE_STIPPLE);
}

void drawInnerPolygon() {
  glDisable(GL_LINE_STIPPLE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex2f(-20, 20);
  glColor3f(1.0, 0.0, 0.0);
  glVertex2f(-20, -20);
  glColor3f(0.0, 1.0, 0.0);
  glVertex2f(20, -20);
  glColor3f(0.0, 0.0, 1.0);
  glVertex2f(20, 20);
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(inerAngle, 0, 0,1);
  glTranslatef(posX, posY, 0);
  glScalef(scalArg, scalArg, 1);
  drawInnerPolygon();

  glLoadIdentity();
  glTranslatef(posX, posY, 0);
  glScalef(scalArg, scalArg, 1);
  drawOuterPolygon();
  glFlush();
}

// void mouse(int button, int state, int x, int y) {
//   if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
//     posY=posY+y;
//     posX=posX+x;
//     glutPostRedisplay();
//
//   }



//}

void keyboard(unsigned char key, int x, int y) {
  if(key=='s'){
    ++scal;
    scalArg*=2;
   // glScalef(2, 2, 1);
    glutPostRedisplay();
  }
  else if(key=='S'){
    if(scal>0){
      --scal;
      scalArg*=0.5;
      //glScalef(0.5,0.5,1);
      glutPostRedisplay();
    }
  }
  else if(key=='r'){
    inerAngle+=1;
    //glRotatef(inerAngle, 0, 0, 1);
    glutPostRedisplay();
  }
  else if(key=='R'){
    inerAngle-=1;
    //glRotatef(inerAngle,0,0,1);
    glutPostRedisplay();
  }
  glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
  switch(key){
    case GLUT_KEY_UP:
      if(posY+5<70){
        ++posY;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_DOWN:
      if(posY-5>-70){
        --posY;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_LEFT:
      if(posX-5>-70){
        --posX;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_RIGHT:
      if(posX+5<70){
        ++posX;
        glutPostRedisplay();
      }
      break;
    default:
      break;

  }
  glutPostRedisplay();

}


void reshape(int width, int height) {
  windowWidth = width;
  windowHeight = height;
  glViewport(0, 0, windowWidth, windowHeight);

  glMatrixMode(GL_PROJECTION);
  /*The glLoadIdentity command is included in the
  reshape function so that any previous values for the projection parameters
  will not affect the new projection settings.*/
  glLoadIdentity();
  gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2,
             windowHeight / 2);
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(400, 100);
  glutInitWindowSize(900, 900);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutCreateWindow("Provjera1");

  init();
  glutSpecialFunc(specialKeys);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutReshapeFunc(reshape);
  glClearColor(0.9, 0.9, 0.9, 0.0);
  glutMainLoop();

  return 0;
}

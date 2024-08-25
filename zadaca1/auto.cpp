#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <GL/glu.h>

int angle=0;
int carPosition=0;
bool day=true;
//bool hill=false;

int carColorR=1;
int carColorG=0;
int carColorB=0;

int lineWidth = 3;

void drawCar(){
  glColor3f(carColorR, carColorG, carColorB);
  glBegin(GL_POLYGON);
  glVertex2f(-24,5);
  glVertex2f(24,5);
  glVertex2f(24,15);
  glVertex2f(-24, 15);
  glEnd();

  glBegin(GL_POLYGON); // begin new polygon
  glVertex2f(-16,15);
  glVertex2f(16,15);
  glVertex2f(16,22);
  glVertex2f(-16,22);
  glEnd(); // end new polygon


  glColor3f(0.5, 0.5, 0.5);
  GLUquadricObj* quadric = gluNewQuadric();
  glTranslatef(12, 4, 0);
  gluDisk(quadric, 0, 5, 32, 3);
  //glTranslatef(-12, 3, 0);
  //gluDisk(quadric, 0, 4, 32, 3);
  glTranslatef(-12, 4, 0);
 //gluDeleteQuadric(quadric);
  glTranslatef(-12, -4, 0);
  gluDisk(quadric, 0, 5, 32, 3);
  glTranslatef(12, 4, 0);


}

void drawRoad(){
  glColor3f(0.5, 0.5, 0.5);
  glLineWidth(lineWidth);

 // glPushMatrix();

  glBegin(GL_LINES);
  glVertex2f(-100, 0);
  glVertex2f(100,0);
  glEnd();

  //glPopMatrix();
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  //glLoadIdentity();
  //glColor3f(carColorR, carColorG, carColorB);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glRotatef(angle, 0, 0, 1);
  glTranslatef(carPosition, 0, 0);
  // glRotatef(angle, 0, 0, 1);
  drawCar();

  glLoadIdentity();
  glTranslatef(0, 0, 0);
  glRotatef(angle, 0, 0, 1);
  drawRoad();

  glFlush();
}

void keyboard(unsigned char key, int x, int y){
  std::cout << "Keyboard callback" << std::endl;
  switch (key){
    case 27:
      exit(0);
        break;
      case 'r':
        if(angle>-60){
          angle-=1;
        //hill=true;
          glutPostRedisplay();
        }
        break;
      case 'R':
        if(angle <60){
          angle+=1;
        //hill=true;
          glutPostRedisplay();
        }
      break;
    default:
      break;
  }
// glutPostRedisplay();
}

void specialKeys(int key, int x, int y){
  std::cout << "Special keyboard callback" << std::endl;
  switch (key){
    case GLUT_KEY_LEFT:
      if(carPosition-1>=-80){
        carPosition-=1;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_RIGHT:
      if(carPosition+1<=80){
        carPosition+=1;
        glutPostRedisplay();
      }
      break;
    default:
      break;
    }
  glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
    if(carColorR==1 && carColorG==0 && carColorB==0){
    //glColor3f(0.0, 0.0, 1.0);
      carColorR=0;
      carColorG=0;
      carColorB=1; //setuj na plavu
      glutPostRedisplay();
    }
    else if(carColorR==0 && carColorG==0 && carColorB==1){
      carColorR=0;
      carColorG=1;  //setuj na zelenu
      carColorB=0;
      glutPostRedisplay();
    }
    else {
      carColorR=1;  //setuj na crvenu koja je bila na pocetku
      carColorB=0;
      carColorG=0;
    }
    glutPostRedisplay();
  }
  else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN){
    day=!day;
    if(day){
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }
    else{
      glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    glutPostRedisplay();
  }
}

void init(){
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(-100, 100, -100, 100);
  if (day){
    glClearColor(1.0, 1.0, 1.0, 1.0);
  }
  else{
    glClearColor(0.0, 0.0, 0.0, 1.0);
  }
  glLineWidth(2.0);
}






int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitWindowPosition(100, 200);
  glutInitWindowSize(500, 500);
  glutCreateWindow("User input");
  init();
  //glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(specialKeys);
  //glutPassiveMotionFunc(mouseMotion);
  glutMouseFunc(mouse);
  glutMainLoop();
}

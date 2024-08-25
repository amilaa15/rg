#include <GL/glut.h>

float camX=0.0;
float camY=0.0;
float camZ=10;
float camShift=1;

float sphereTranslation=0;
float sphereRotation=0;
float sphereRotationSpeed=0.1;
float sphereTranslationSpeed=0.007;

bool isOrthogonal=false;


void init(){
  glClearColor(0,0,0,0);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,800,800);
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
 // glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();


  if (isOrthogonal) {
    glOrtho(-5, 5, -5, 5, 1.0, 100.0);
  }
  else {
    gluPerspective(45.0, 1.0, 1.0, 100.0);
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);

  glPushMatrix();
  glTranslatef(0, sphereTranslation, 0);
  glRotatef(sphereRotation, 0, 1, 0);
  glColor3f(0,0,1);
  glutWireSphere(0.7, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,-2,0);
  glColor3f(0,1,0);
  glutWireCube(1.5);
  glPopMatrix();

  glFlush();
}


void specialKeys(int key, int x, int y){
  switch(key){
    case GLUT_KEY_UP:
      camY+=camShift;
      glutPostRedisplay();
      break;
    case GLUT_KEY_DOWN:
      camY-=camShift;
      glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT:
      camX-=camShift;
      glutPostRedisplay();
      break;
    case GLUT_KEY_RIGHT:
      camX+=camShift;
      glutPostRedisplay();
      break;
    default:
      break;
  }
}


void animation(){
  sphereTranslation+=sphereTranslationSpeed;
  if(sphereTranslation>3 || sphereTranslation<0)
    sphereTranslationSpeed=-sphereTranslationSpeed;

  sphereRotation+=sphereRotationSpeed;
  if(sphereRotation>360)
    sphereRotation-=360;
  
  glutPostRedisplay();
  //glutTimerFunc(16, animation, 0);
}


void keyboard(unsigned char key, int x, int y){
  switch(key){
    case 27:
      exit(0);
      break;
    case 'o':
      isOrthogonal=true;
      break;
    case 'p':
      isOrthogonal=false;
      break;
    case 'O':
      isOrthogonal=true;
      break;
    case 'P':
      isOrthogonal=false;

    default:
      break;
  }
  glutPostRedisplay();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(500, 500);
  glutCreateWindow("Provjera 2");
  init();
  glutDisplayFunc(display);
  //glutTimerFunc(0, animation, 0);
  glutReshapeFunc(reshape); 
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(keyboard);
  glutIdleFunc(animation);
  glutMainLoop();
  return 0;
}


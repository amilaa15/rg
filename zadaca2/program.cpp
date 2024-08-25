#include <GL/glut.h>

float camX=0.0;
float camY=0.0;
float camZ=10;
float camShift=1;

float torusRadius=0.7;
float torusTubeRadius=0.3;
float torusRotation=0.0;
float torusTranslation=0.0;
float torusSpeed=0.02;
float torusRotationSpeed=1;


float sphereRadius=0.9;
float sphereScale=0.5;
float sphereScaleSpeed=0.005;
bool sphereGrowing=true;

bool isOrthogonal=false;


void init(){
  glClearColor(0,0,0,0);
  glEnable(GL_DEPTH_TEST);
  glViewport(0,0,800,800);
}


void switchToOrtho(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5,5,-5,5,-10,10);
}

void switchToFrustum(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-2,2,-2,2,3.0, 10);
}


void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if(!isOrthogonal){
    gluPerspective(50, 1, 1, 70);
    //gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);
  }
  else{
    glOrtho(-5, 5, -5, 5, 1, 20);
    //gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);
  }

  gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);

  glPushMatrix();
  glTranslatef(-1, 0.0, torusTranslation);
  glRotatef(torusRotation, 0.0, 1.0, 0.0);
  glColor3f(0,1,1);
  glutWireTorus(torusTubeRadius, torusRadius, 10, 10);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1,0,0);
  glScalef(sphereScale, sphereScale, sphereScale);
  glColor3f(1,1,0);
  glutWireSphere(sphereRadius, 13, 13);
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


void animation(int value){
  torusTranslation+=torusSpeed;
  if(torusTranslation>5 || torusTranslation<-5)
    torusSpeed=-torusSpeed;
  torusRotation+=torusRotationSpeed;
  if(torusRotation>360)
    torusRotation-=360;


  if(sphereGrowing){
    sphereScale+=sphereScaleSpeed;
    if(sphereScale>=1)
      sphereGrowing=false;
  }
  else{
    sphereScale-=sphereScaleSpeed;
    if(sphereScale<=0.5) 
      sphereGrowing=true;
  }

  glutPostRedisplay();
  glutTimerFunc(16, animation, 0);
}

//radi esc
void keyboard(unsigned char key, int x, int y){
  switch(key){
    case 27:
      exit(0);
      break;
    case 'o':
      //switchToOrtho();
      isOrthogonal=true;
      break;
    case 'p':
      //switchToFrustum();
      isOrthogonal=false;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}
//
// void reshape(GLint w, GLint h) { 
//   glViewport(0, 0, w, h); 
// }


// void keyboard(unsigned char key, int x, int y){
//   switch(key){
//     case 'o':
//     case 'O':
//       isOrthogonal=true;
//       glMatrixMode(GL_PROJECTION);
//       glLoadIdentity();
//       gluOrtho2D(-1, 1, -1, 1);
//       glutPostRedisplay();
//       break;
//     case 'p':
//     case 'P':
//       isOrthogonal=false;
//       glMatrixMode(GL_PROJECTION);
//       glLoadIdentity();
//       gluPerspective(60, 1, 1, 20);
//       glutPostRedisplay();
//       break;
//   }
//   glutPostRedisplay();
// }

// 
//
//ovdje sa O nestanu sfera i torus a sa P se vrate 
// void keyboard(unsigned char key, int x, int y){
//   switch(key){
//     case 'o':
//     case 'O':
//       isOrthogonal=true;
//       glutPostRedisplay();
//       break;
//     case 'p':
//     case 'P':
//       isOrthogonal=true;
//       glutPostRedisplay();
//       break;
//   }
//   glutPostRedisplay();
// }


// void reshape(int w, int h){
//   glViewport(0,0,(GLint)w,(GLint)h);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   // if(isOrthogonal){
//   //   glOrtho(-5, 5, -5, 5, 1, 20);
//   // }
//   // else
//   gluPerspective(45, (GLfloat)w/(GLfloat)h, 5, 25);
//   glMatrixMode(GL_MODELVIEW);
//   glLoadIdentity();
//   gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
// }
//
// void reshape(int w, int h){
//   glViewport(0, 0, w, h);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   gluPerspective(45, (float)w/(float)h, 1, 100);
// }
//
// void idle(){
//   glutPostRedisplay();
// }
//


int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(900, 900);
  glutInitWindowPosition(500, 500);
  glutCreateWindow("Provjera 2");
  init();
  glutDisplayFunc(display);
  glutTimerFunc(0, animation, 0);
  //glutReshapeFunc(reshape);  // sa reshape nestane slika skroz
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(keyboard);
  //glutIdleFunc(idle);
  glutMainLoop();
  return 0;
}


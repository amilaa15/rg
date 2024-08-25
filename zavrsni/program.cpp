#include <GL/freeglut_std.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

float camX=0;
float camY=0;
float camZ=3;
float camShift=1;

int lastMouseX=-1;
int lastMouseY=-1;

float rotateAngle=0;
float translateTorusZ=0;
float translateTorusSpeed=0.005;
float sphereScale=1;
float teapot2Scale=0.5;
float sphereScaleSpeed=0.001;
bool growing=true;
float rotateSpeed=0.1;

bool light0=true;
bool light1=true;

bool textureTeapotEnable=false;
bool textureTorusEnable=false;
bool textureCubeEnable=false;


GLuint textureTeapot;
GLuint textureTeapot2;



void setFirstLight() {
  GLfloat light_position[] = {1.0, 3.0, 1.0, 0.0};
  GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat no_light[] = {0.0, 0.0, 0.0, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
  if (light0)
    glEnable(GL_LIGHT0);
  else
    glDisable(GL_LIGHT0);
}

void setSecondLight() {
  GLfloat light_position[] = {1.0, -3.0, 1.0, 0.0};
  GLfloat white_light[] = {0.7, 0.7, 0.7, 1.0};
  GLfloat yellow_light[] = {1.0, 1.0, 0.0, 1.0};
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, yellow_light);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);
  if (light1)
    glEnable(GL_LIGHT1);
  else
    glDisable(GL_LIGHT1);
}


void setFirstMaterial() {
    GLfloat mat_ambient[] = {0.2, 0.0, 0.0, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.8, 0.0, 1.0};
    GLfloat mat_specular[] = {0.5, 0.0, 0.0, 1.0};
    GLfloat mat_shininess[] = {110.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void setSecondMaterial() {
    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat mat_diffuse[] = {0.8, 0.0, 0.8, 1.0};
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_shininess[] = {5.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}



void loadTexture(const char* filename, GLuint &texture){
    FILE *file = fopen(filename, "rb");
    if(!file){
        printf("Ne moze ucitati teksturu\n");
        exit(1);
    }

    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54){
        printf("Nevalidan format fajla\n");
        fclose(file);
        exit(1);
    }

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int channels = 3; // Pretpostavljamo da je slika bez alfa kanala
    int imageSize = channels * width * height;
    unsigned char *data = (unsigned char *)malloc(imageSize);

    if (fread(data, 1, imageSize, file) != imageSize){
        printf("Greska pri citanju slike\n");
        fclose(file);
        exit(1);
    }

    fclose(file);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    //GLenum internalFormat = (channels == 4) ? GL_RGBA8 : GL_RGB8;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
}




void drawCube(){
  if(textureCubeEnable){
    setFirstMaterial();
  }
  else{
    GLfloat material_diffuse[] = {0, 1, 0.1, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
  // glColor3f(0,1,1);
  }
  glutSolidCube(1.0);
 }

void drawSphere(){
  //glBindTexture(GL_TEXTURE_2D, textureTeapot);
  //glEnable(GL_TEXTURE_2D);

  GLfloat material_diffuse[] = {1, 0, 0.5, 1};  
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
  // glColor3f(1,0,0.5);
  //glDisable(GL_TEXTURE_2D);
  glutSolidSphere(0.5, 30, 30); 
  //glDisable(GL_TEXTURE_2D);
}

void drawTorus(){
  if(textureTorusEnable){
    setSecondMaterial();
  }
  else{
    //glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);  // Reset teksture
    GLfloat material_diffuse[] = {0, 1, 1, 1};     
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
  // glColor3f(0,1,1);
  }
  glutSolidTorus(0.2, 0.5, 25, 25);
  glBindTexture(GL_TEXTURE_2D, 0);  // Reset teksture
 // glDisable(GL_TEXTURE_2D);
}

void drawCone(){
  GLfloat material_diffuse[] = {1, 1, 1, 1}; 
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
  // glColor3f(1,1,1);
  glutWireCone(0.5, 1, 10, 10);
}

void drawTeapot1(){
  glBindTexture(GL_TEXTURE_2D, textureTeapot);
  glEnable(GL_TEXTURE_2D);
  glutSolidTeapot(0.7);
  glDisable(GL_TEXTURE_2D);
}

void drawTeapot2(){
  glBindTexture(GL_TEXTURE_2D, textureTeapot2);
  glEnable(GL_TEXTURE_2D);
  glutSolidTeapot(0.9);
  glDisable(GL_TEXTURE_2D);
}


void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setFirstLight();
  setSecondLight();
 
  gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 0.1, 0);

  //glEnable(GL_TEXTURE_2D);

  //kocka
  //glPushMatrix();
  glTranslatef(0, 0, 0);
  glPushMatrix();
  glRotatef(rotateAngle, 1, 1, 1);
  drawCube();
  glPopMatrix();

  //sfera
  glPushMatrix();
  glTranslatef(1,3,-1);
  //glPushMatrix();
  glScalef(sphereScale, sphereScale, sphereScale);
  drawSphere();
  glPopMatrix();

  //torus
  glPushMatrix();
  glTranslatef(-3,0,-1);
  //glPushMatrix();
  glTranslatef(translateTorusZ,0,0);
  drawTorus();
  glPopMatrix();
  //glDisable(GL_TEXTURE_2D);

  //korent
  glPushMatrix();
  glTranslatef(0,-3,-1);
  //glPushMatrix();
  glRotatef(rotateAngle, 0, 1, 0);
  drawCone();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(3,0,-1);
  glRotatef(rotateAngle, 0, 0, 1);
  drawTeapot1();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-3,3,-2);
 // glRotatef(rotateAngle, 0, 0, 1);
  glScalef(teapot2Scale, teapot2Scale, teapot2Scale);
  drawTeapot2();
  glPopMatrix();

  //glDisable(GL_TEXTURE_2D);
  glFlush();
}


void init(){
  glEnable(GL_DEPTH_TEST);
  GLfloat lmodel_ambient[] = {0.3, 0.3, 0.3, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glEnable(GL_LIGHTING);


  glColor3f(0.4, 0, 1);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5, 5, -5, 5, -10, 10);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_TEXTURE_2D);
  loadTexture("teapot_texture.bmp", textureTeapot);
  loadTexture("torus_texture.bmp", textureTeapot2);


}


void animation(){
  rotateAngle+=rotateSpeed;
  if(rotateAngle>360)
    rotateAngle-=360;

  translateTorusZ+=translateTorusSpeed;
  if(translateTorusZ>1.5 || translateTorusZ<-1)
    translateTorusSpeed=-translateTorusSpeed;

  if(growing){
    sphereScale+=sphereScaleSpeed;
    if(sphereScale>=2)
      growing=false;
  }
  else{
    sphereScale-=sphereScaleSpeed;
    if(sphereScale<=1)
      growing=true;
  }


  if(growing){
    teapot2Scale+=sphereScaleSpeed;
    if(sphereScale>=1.6)
      growing=false;
  }
  else{
    teapot2Scale-=sphereScaleSpeed;
    if(sphereScale<=0.4)
      growing=true;
  }


  glutPostRedisplay();
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


void mouse(int button, int state, int x, int y){
  if(state==GLUT_DOWN){
    lastMouseX=x;
    lastMouseY=y;

    switch(button){
      case GLUT_LEFT_BUTTON:
        rotateSpeed=0.1;
        break;
      case GLUT_MIDDLE_BUTTON:
        translateTorusSpeed=0.005;
        break;
      case GLUT_RIGHT_BUTTON:
        sphereScaleSpeed=0.001;
        break;
    }
  }
  else if(state==GLUT_UP){
    switch(button){
      case GLUT_LEFT_BUTTON:
        rotateSpeed=0;
        break;
      case GLUT_MIDDLE_BUTTON:
        translateTorusSpeed=0;
        break;
      case GLUT_RIGHT_BUTTON:
        sphereScaleSpeed=0;
        break;
      }
    }
  }


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
          exit(0);
        case '0': 
          light0 = !light0;
          glutPostRedisplay();
          break;
        case '1': 
          light1 = !light1;
          glutPostRedisplay();
          break;
        case '2':
          textureTorusEnable = !textureTorusEnable;
          //glutPostRedisplay();
          break;
        // case '4': 
        //   textureTeapotEnable = !textureTeapotEnable;
        //   //glutPostRedisplay();
        //   break;
        case '3': 
          textureCubeEnable = !textureCubeEnable;
          //glutPostRedisplay();
          break;
        default: break;
    }
    glutPostRedisplay();
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120, (double)w / (double)h, 1.0, 250);
    glMatrixMode(GL_MODELVIEW);
}




int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("3D Scene");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutIdleFunc(animation);

    glutMainLoop();
    return 0;
}










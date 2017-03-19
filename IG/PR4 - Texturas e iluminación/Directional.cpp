#include "Directional.h"

Directional::Directional(){
    alpha=0;
    beta=0;

    const float
    caf[4] = { 0.0, 0.0, 0.0, 1.0 },          // color ambiental de la fuente
    cdf[4] = { 1.0, 1.0, 1.0, 1.0 },         // color difuso de la fuente
    csf[4] = { 1.0, 1.0, 1.0, 1.0 };           // color especular de la fuente
    glLightfv( GL_LIGHT1, GL_AMBIENT, caf );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, cdf );
    glLightfv( GL_LIGHT1, GL_SPECULAR, csf );

    const GLfloat dirf[4] = { -50, 10, 100, 0.0 } ; // (x,y,z,w)
    glLightfv( GL_LIGHT1, GL_POSITION, dirf );
}

void Directional::enable(){
    glEnable(GL_LIGHTING);
    GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
    GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glRotatef( alpha, 0.0, 1.0, 0.0 ) ;
    glRotatef( beta, -1.0, 0.0, 0.0 ) ;
    glEnable(GL_LIGHT1);
}

void Directional::setRedLight(int disco){
  glEnable(GL_LIGHTING);
  GLfloat light1_ambient[] = { 0.5, 0.0, 0.0, 1.0 };
  GLfloat light1_diffuse[] = { 1.0, 0.0, 0.0, 0.0 };
  GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
  GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
  const GLfloat dirf[4] = { -5000+(float)(disco*10), 5000, 0, 0.0 } ; // (x,y,z,w)

  glLightfv( GL_LIGHT1, GL_POSITION, dirf );
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
  glEnable(GL_LIGHT1);
}

void Directional::setBlueLight(int disco){
  glEnable(GL_LIGHTING);
  GLfloat light1_ambient[] = { 0.0, 0.0, 0.5, 1.0 };
  GLfloat light1_diffuse[] = { 0.0, 0.0, 1.0, 0.0 };
  GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
  GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
  const GLfloat dirf[4] = { (float)disco+0, 5000, 0, 0.0 } ; // (x,y,z,w)

  glLightfv( GL_LIGHT2, GL_POSITION, dirf );
  glLightfv(GL_LIGHT2, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT2, GL_SPECULAR, light1_specular);
  glEnable(GL_LIGHT2);
}

void Directional::setGreenLight(int disco){
  glEnable(GL_LIGHTING);
  GLfloat light1_ambient[] = { 0.0, 0.5, 0.0, 1.0 };
  GLfloat light1_diffuse[] = { 0.0, 1.0, 0.0, 0.0 };
  GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat light1_position[] = { -2.0, 2.0, 1.0, 1.0 };
  GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
  const GLfloat dirf[4] = { (float)(disco*10)+5000, 15000, -1000, 0.0 } ; // (x,y,z,w)

  glLightfv( GL_LIGHT3, GL_POSITION, dirf );
  glLightfv(GL_LIGHT3, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT3, GL_SPECULAR, light1_specular);
  glEnable(GL_LIGHT3);
}

void Directional::disable(){
  glDisable(GL_LIGHT1);
}

void Directional::move_light(float position){
  GLfloat light_position[] = { position*2/3, 100.0, 0.0, 0.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, light_position);
  const GLfloat posf1[4] = {position-1000,20,500,0};
	const GLfloat posf2[4] = {position,20,500,0};
	const GLfloat posf3[4] = {position+1000,20,500,0};
  glDisable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_POSITION, posf1);
	glLightfv(GL_LIGHT2, GL_POSITION, posf2);
	glLightfv(GL_LIGHT3, GL_POSITION, posf3);
}

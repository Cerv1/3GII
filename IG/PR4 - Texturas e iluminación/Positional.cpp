#include "Positional.h"

Positional::Positional(){
  site.assign(3,0.0);
}

void Positional::set_up(){
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
}

void Positional::move_light(float position){
  site[0]=position;
  site[1]=350;
  site[2]=500;

  const GLfloat posf[4] = { position, 350, 500, 1.0 } ; // (x,y,z,w)
  glLightfv( GL_LIGHT0, GL_POSITION, posf );
}

void Positional::disable(){
  glDisable(GL_LIGHT0);
}

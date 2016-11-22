#include "Mechanic.h"
#include "Ply.h"
#include <vector>
#include <cmath>


Mechanic::Mechanic(){
  base = new RevolutionObject("base.ply");
  base->changeSides(10);
  base->generateUpperCap();
  base->generateLowerCap();
  _file_ply reader;
  maquina = new Ply();
  maquina->readPLY("f16.ply");
}

void Mechanic::draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int desp, float ver){
  glPushMatrix();
    glTranslatef(0,20,0);
    glPushMatrix();
      rail_draw(shape, mode, pos_via, pos_grip,desp,ver);
    glPopMatrix();
    base_draw(shape,mode);
  glPopMatrix();
}

void Mechanic::base_draw(unsigned char shape, unsigned char mode){
    glTranslatef(-100,-600,300);
    glRotatef(-180,0,1,0);
    glRotatef(-90,1,0,0);
    glRotatef(-90,0,0,1);
    glTranslatef(0,-100,0);
    glScalef(400,400,400);
    maquina->draw(shape,mode);
}

void Mechanic::rail_draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int desp, float ver){
  glPushMatrix();
    glTranslatef(0,85,0);
    connector_draw(shape,mode,pos_via,pos_grip,desp,ver);
  glPopMatrix();
}

void Mechanic::claw_draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip){
  glPushMatrix();
    glRotatef(0+pos_grip,0,1,0);
    gripper_draw(shape,mode,pos_via);
  glPopMatrix();

  glPushMatrix();
    glRotatef(120+pos_grip,0,1,0);
    gripper_draw(shape,mode,pos_via);
  glPopMatrix();

  glPushMatrix();
    glRotatef(240+pos_grip,0,1,0);
    gripper_draw(shape,mode,pos_via);
  glPopMatrix();
}

void Mechanic::gripper_draw(unsigned char shape, unsigned char mode, int pos_grip){
  glPushMatrix();
    glRotatef(pos_grip,0,0,1);
    glPushMatrix();
        glTranslatef(-49,-45.5,0);
        glRotatef(pos_grip+10,0,0,1);
        glTranslatef(0,-75/2,0);
        glScalef(15,75,15);
        base->draw(shape,mode);
    glPopMatrix();

    glRotatef(-45,0,0,1);
    glTranslatef(0,-75/2,0);
    glScalef(15,75,15);
    base->draw(shape,mode);
    glPopMatrix();
}

void Mechanic::connector_draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int des,float ver){
    int longitud=100;
    cout << ver << endl;
    glPushMatrix();
        glTranslatef(des,0,0);
        glPushMatrix();
            glTranslatef(0,-(ver-1)*longitud,0);
            claw_draw(shape,mode,pos_grip,pos_via);
        glPopMatrix();
        glTranslatef(0,longitud,0);
        glScalef(1,ver,1);
        glTranslatef(0,-longitud/2,0);
        glScalef(20,longitud,20);
        base->draw(shape,mode);
    glPopMatrix();
}

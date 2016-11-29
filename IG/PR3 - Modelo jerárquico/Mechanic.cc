#include "Mechanic.h"
#include "Ply.h"
#include <vector>
#include <cmath>


Mechanic::Mechanic(){
  base = new RevolutionObject("base.ply");
  base->changeSides(10);
  base->generateUpperCap();
  base->generateLowerCap();

  maquina = new Ply();
  rat = new Ply();
  cow = new Ply();
  big_porsche = new Ply();

  maquina->readPLY("machine.ply");
  rat->readPLY("rat.ply");
  cow->readPLY("cow.ply");
  big_porsche->readPLY("big_porsche.ply");

}

void Mechanic::draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int desp, float ver, int vertical_movement){
  glPushMatrix();
    glTranslatef(0,200,0);
    glPushMatrix();
      rail_draw(shape, mode, pos_via, pos_grip,desp,ver,vertical_movement);
    glPopMatrix();
    base_draw(shape,mode);
  glPopMatrix();
}

void Mechanic::base_draw(unsigned char shape, unsigned char mode){
  glPushMatrix();
    //Cow creation
    glPushMatrix();
      glTranslatef(-25,-430,-95);
      glRotatef(-65,0,1,0);
      glScalef(30,30,30);
      cow->draw(shape,mode);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(120,-430,150);
      glRotatef(-120,0,1,0);
      glScalef(30,30,30);
      cow->draw(shape,mode);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(150,-430,-50);
      glRotatef(-190,0,1,0);
      glScalef(30,30,30);
      cow->draw(shape,mode);
    glPopMatrix();

    //Porsche creation
    glPushMatrix();
      glTranslatef(5,-400,-350);
      glRotatef(-50,0,1,0);
      glScalef(15,15,15);
      big_porsche->draw(shape,mode);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-50,-400,80);
      glRotatef(50,0,1,0);
      glScalef(15,15,15);
      big_porsche->draw(shape,mode);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-150,-400,-100);
      glRotatef(-125,0,1,0);
      glScalef(15,15,15);
      big_porsche->draw(shape,mode);
    glPopMatrix();

    //Rat creation
    glPushMatrix();
      glTranslatef(250,-310,-200);
      glRotatef(-30,1,0,0);
      glScalef(20,20,20);
      rat->draw(shape,mode);
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-50,-310,-300);
      glRotatef(-30,1,0,0);
      glScalef(20,20,20);
      rat->draw(shape,mode);
    glPopMatrix();

    glTranslatef(-100,-700,300);
    glRotatef(-180,0,1,0);
    glRotatef(-90,1,0,0);
    glRotatef(-90,0,0,1);
    glTranslatef(0,-100,0);
    glScalef(400,400,400);
    maquina->draw(shape,mode);
  glPopMatrix();
}

void Mechanic::rail_draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int desp, float ver, int vertical_movement){
  glPushMatrix();
    glTranslatef(0,85,0);
    connector_draw(shape,mode,pos_via,pos_grip,desp,ver,vertical_movement);
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

void Mechanic::connector_draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int des,float ver, int vertical_movement){
    int longitud=100;
    glPushMatrix();
        glTranslatef(des,-100,vertical_movement);

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

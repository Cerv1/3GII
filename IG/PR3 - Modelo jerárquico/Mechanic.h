#ifndef _MECHANIC_H
#define _MECHANIC_H

#include "Ply.h"
#include "Cube.h"
#include "RevolutionObject.h"
#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>


class Mechanic : public Object3d{
  private:
    RevolutionObject *cube;
    RevolutionObject *sphere;
    RevolutionObject *base;
    Ply *maquina;
  public:
    Mechanic();
    void draw(unsigned char shape, unsigned char mode, int pos_via,int pos_grip, int desp, float ver,int vertical_displacement);
    void gripper_draw(unsigned char shape, unsigned char mode, int pos_grip);
    void claw_draw(unsigned char shape, unsigned char mode, int pos_grip, int pos_via);
    void connector_draw(unsigned char shape, unsigned char mode, int pos_via, int pos_grip, int desp, float ver, int vertical_displacement);
    void base_draw(unsigned char shape, unsigned char mode);
    void rail_draw(unsigned char shape, unsigned char mode, int pos_via,int pos_grip, int desp, float ver,int vertical_displacement);
};

#endif

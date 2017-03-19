#ifndef _DIRECTIONAL_H
#define _DIRECTIONAL_H

#include "Light.h"
#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

class Directional : public Light{
    private:
        float alpha;
        float beta;

    public:
        Directional();
        void enable();
        void disable();
        void move_light(float);
        void setRedLight(int);
        void setBlueLight(int);
        void setGreenLight(int);
};

#endif

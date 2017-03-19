#ifndef _POSITIONAL_H
#define  _POSITIONAL_H

#include "Light.h"
#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

class Positional : public Light{
    private:
        vector<float> site;
    public:
        Positional();
        void disable();
        void set_up();
        void move_light(float pos);
};

#endif

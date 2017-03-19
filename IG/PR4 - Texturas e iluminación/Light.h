#ifndef _LIGHT_H
#define _LIGHT_H

#include <vector>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;

class Light{
    protected:
        vector<float> color;
    public:
        Light();
        void enable();
        void disable();
};


#endif

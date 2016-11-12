#ifndef _CUBE_H
#define _CUBE_H

#include "Object3d.h"
#include<vector>

using namespace std;

class Cube : public Object3d{
    private:
        float size;

    public:
        Cube();
        int getSize();             
        int getVertex();
        int getTriangles();
};


#endif

#ifndef _OBJECT3D_H
#define _OBJECT3D_H

#include <vector>
#include <cmath>


using namespace std;

struct Point{
  float x_;
  float y_;
  float z_;
};

class Object3d{
    protected:
        vector<float> vertex;
        vector<int> triangles;
        Point min;
        Point max;

    public:
        Object3d();
        void draw(unsigned char draw_mode, unsigned char ob);            // Dibuja el Objeto3d en el modo draw_mode
        void draw_chess();// Dibuja el Objeto3d en modo ajdedrez
        void drawSolidAndLines();
        Point getCenter();
        float module(Point point);
        float getSizeBox();
        void getBoundingBox();
        void translate();
        void scale();
};




#endif

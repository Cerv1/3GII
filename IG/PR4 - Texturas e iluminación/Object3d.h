#ifndef _OBJECT3D_H
#define _OBJECT3D_H
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
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
        vector<float> normalVertex;
        vector<float> normalTri;
        vector<float> tex_coord;
        unsigned char *texture;
        float coefs_s[4];
        float coefs_t[4];
        Point min;
        Point max;

    public:
        GLuint idTex;

        Object3d();
        void draw(unsigned char draw_mode, unsigned char ob);            // Dibuja el Objeto3d en el modo draw_mode
        void draw_chess();// Dibuja el Objeto3d en modo ajdedrez
        void drawSolidAndLines();
        Point getCenter();
        float module(Point point);
        float getSizeBox();
        void getBoundingBox();
        void calculateNormalArray();
        void set_white_material();
        void set_shiny_material();
        void set_black_material();
        void no_material();
        void translate();
        void scale();
};




#endif

#ifndef _OBJECT3D_H
#define _OBJECT3D_H

#include <vector>

using namespace std;


class Object3d{
    protected:
        vector<float> vertex;
        vector<int> triangles;
        bool elem=false;

    public:
        Object3d();
        void draw(unsigned char draw_mode);            // Dibuja el Objeto3d en el modo draw_mode
        void draw_chess();                                                  // Dibuja el Objeto3d en modo ajdedrez
        void changeSize(float size);                                // Cambia el tamaño del Objeto3d multiplicando sus vertices por size
        void changeElem();
        bool getElem();
};




#endif

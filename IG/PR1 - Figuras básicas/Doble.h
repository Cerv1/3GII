#ifndef _DOBLE_H
#define _DOBLE_H

#include "Object3d.h"
#include<vector>

using namespace std;

class Doble : public Object3d{
    private:
        bool superior;

    public:
        Doble();
        void draw(GLenum mode, int m);
        void draw_chess(int m);
};


#endif

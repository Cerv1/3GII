#ifndef _REVOLUTIONOBJECT_H
#define _REVOLUTIONOBJECT_H

#include "Object3d.h"
#include "Ply.h"
#include <vector>
#include <cmath>

class RevolutionObject : public Object3d{
    private:
        bool caps=true;
        vector<float> perfilInicial;
        int nSides;

    public:
        RevolutionObject(vector<float> perfil, int N);
        RevolutionObject(char* file_name);
        void generateRevolution(int N);
        void generateLowerCap();
        void generateUpperCap();
        void generateOutline();
        void eraseCaps();
        void changeSides(int N);
        int getSides();
};


#endif

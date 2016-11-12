#ifndef _PLY_H
#define _PLY_H

#include "Object3d.h"
#include "file_ply_stl.h"
#include <vector>

using namespace std;

class Ply : public Object3d{
    private:
      _file_ply reader;

    public:
        Ply();
        void readPLY(char* file_name);
};


#endif

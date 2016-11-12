#ifdef _WIN32
#include <windows.h>
#endif

#include <cstdio>

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Tetrahedron.h"


Tetrahedron::Tetrahedron(){
    this->size=0;
    this->vertex= {0.0,100.0,0.0,      // V0
                  0.0,0.0,-40.0,     // V1
                  -40.0,0.0,40.0,  // V2
                  40.0,0.0,40.0};  // V3



    this->triangles= {0,2,3,
                                     0,3,1,
                                     2,0,1,
                                     1,3,2};

    getBoundingBox();
}

#ifdef _WIN32
#include <windows.h>
#endif

#include <cstdio>

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Cube.h"


Cube::Cube(){
    this->size=50;
    this->vertex= {0.0,0.0,50.0,        // V0
                                50.0,0.0,50.0,     // V1
                                0.0,50.0,50.0,    //  V2
                                50.0,50.0,50.0,   // V3
                                0.0,50.0,0.0,        // V4
                                50.0,50.0,0.0,       // V5
                                50.0,0.0,0.0,       // V6
                                0.0,0.0,0.0};       // V7

    this->triangles= {0,3,2,
                                     0,1,3,
                                     1,5,3,
                                     1,6,5,
                                     2,5,4,
                                     2,3,5,
                                     2,4,0,
                                     0,4,7,
                                     4,5,7,
                                     5,6,7,
                                     7,6,0,
                                     0,6,1};
}


int Cube::getSize(){
    return this->size;
}

int Cube::getVertex(){
    for(int i=0; i<vertex.size(); i++)
        cout << vertex[i] << " ";
}

int Cube::getTriangles(){
    for(int i=0; i<triangles.size(); i++)
        cout << triangles[i] << " ";
}

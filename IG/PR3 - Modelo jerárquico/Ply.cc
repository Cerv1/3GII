#ifdef _WIN32
#include <windows.h>
#endif

#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Ply.h"



Ply::Ply(){
  vertex.clear();
  triangles.clear();
}

void Ply::readPLY(char* file_name){
  reader.open(file_name);
  triangles.clear();
  vertex.clear();
  reader.read(vertex,triangles);
  // getBoundingBox();
}

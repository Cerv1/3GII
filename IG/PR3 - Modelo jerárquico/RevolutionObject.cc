#ifdef _WIN32
#include <windows.h>
#endif
#define _USE_MATH_DEFINES
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "RevolutionObject.h"


void RevolutionObject::generateRevolution(int N){
    int nvPerfil = perfilInicial.size();
    float angle = M_PI*2.0 / N;
    float seno = sin(angle);
    float coseno = cos(angle);
    int desPerfil = 0;

    for(int nPerfil = 0; nPerfil < N; nPerfil++){
        for(desPerfil = nPerfil*nvPerfil; desPerfil<(nPerfil*nvPerfil)+nvPerfil; desPerfil+=3){
          vertex.push_back((coseno*vertex[desPerfil]) + (seno*vertex[desPerfil+2]));
          vertex.push_back(vertex[desPerfil+1]);
          vertex.push_back(((-seno)*vertex[desPerfil]) + (coseno*vertex[desPerfil+2]));
         }
    }
}

RevolutionObject::RevolutionObject(char* file_name){
  _file_ply reader;
  reader.open(file_name);
  nSides=40;
  triangles.clear();
  reader.read(vertex,triangles);
  perfilInicial=vertex;
  generateOutline();
  generateRevolution(nSides);
  getBoundingBox();
}

void RevolutionObject::read_ply(char * file_name, int Nsides){
  _file_ply reader;
  reader.open(file_name);
  nSides=Nsides;
  triangles.clear();
  reader.read(vertex,triangles);
  perfilInicial=vertex;
  generateOutline();
  generateRevolution(nSides);
  getBoundingBox();
}

void RevolutionObject::generateLowerCap(){
  int desPerfil=0;

  vertex.push_back(0.0);
  vertex.push_back(min.y_);
  vertex.push_back(0.0);

  int nvPerfil=perfilInicial.size()/3;

  for(int nPerfil = 0; nPerfil < nSides; nPerfil++){
    for(desPerfil = nPerfil*nvPerfil; desPerfil<(nPerfil*nvPerfil)-1+nvPerfil; desPerfil++){
      if(desPerfil+1==(nPerfil*nvPerfil)+nvPerfil-1){
        if(perfilInicial[1]>perfilInicial[perfilInicial.size()-2]){
          triangles.push_back(desPerfil+1);
          triangles.push_back(vertex.size()/3 - 1);
          triangles.push_back(desPerfil+1+nvPerfil);
        }
        else{
          triangles.push_back(desPerfil+1+nvPerfil);
          triangles.push_back(vertex.size()/3 - 1);
          triangles.push_back(desPerfil+1);
        }
      }
    }
  }
}

void RevolutionObject::generateUpperCap(){
  int desPerfil=0;

  vertex.push_back(0.0);
  vertex.push_back(max.y_);
  vertex.push_back(0.0);

  int nvPerfil=perfilInicial.size()/3;

  for(int nPerfil = 0; nPerfil < nSides; nPerfil++){
    for(desPerfil = nPerfil*nvPerfil; desPerfil<(nPerfil*nvPerfil)-1+nvPerfil; desPerfil++){
      if(desPerfil==(nPerfil*nvPerfil)){
        if(perfilInicial[1]>perfilInicial[perfilInicial.size()-2]){
          triangles.push_back(desPerfil+nvPerfil);
          triangles.push_back(vertex.size()/3-1);
          triangles.push_back(desPerfil);
        }
        else{
          triangles.push_back(desPerfil);
          triangles.push_back(vertex.size()/3-1);
          triangles.push_back(desPerfil+nvPerfil);
        }
      }
    }
  }
}

void RevolutionObject::generateOutline(){
  int desPerfil=0;
  int nvPerfil=perfilInicial.size()/3;
  for(int nPerfil = 0; nPerfil < nSides; nPerfil++){
    for(desPerfil = nPerfil*nvPerfil; desPerfil<(nPerfil*nvPerfil)-1+nvPerfil; desPerfil++){
      if(perfilInicial[1]>perfilInicial[perfilInicial.size()-2]){
        triangles.push_back(desPerfil+1);
        triangles.push_back(desPerfil+nvPerfil);
        triangles.push_back(desPerfil);

        triangles.push_back(desPerfil+1);
        triangles.push_back(desPerfil+nvPerfil+1);
        triangles.push_back(desPerfil+nvPerfil);
      }
      else{
        triangles.push_back(desPerfil);
        triangles.push_back(desPerfil+nvPerfil);
        triangles.push_back(desPerfil+1);

        triangles.push_back(desPerfil+nvPerfil);
        triangles.push_back(desPerfil+nvPerfil+1);
        triangles.push_back(desPerfil+1);
      }
    }
  }
}

void RevolutionObject::changeSides(int N){
  this->nSides=N;
  this->vertex=perfilInicial;
  this->triangles.clear();
  generateOutline();
  generateRevolution(nSides);
}

int RevolutionObject::getSides(){
  return nSides;
}


void RevolutionObject::eraseCaps(){
    triangles.clear();
    generateOutline();
}

RevolutionObject::RevolutionObject(vector<float> perfil, int N){
    this->nSides=N;
    this->vertex=perfil;
    this->perfilInicial=perfil;

    generateOutline();
    generateRevolution(nSides);
    getBoundingBox();

}

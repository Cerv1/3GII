#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <string>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Object3d.h"
#include <cmath>

Object3d::Object3d(){
    this->vertex.clear();
    this->triangles.clear();
}

void Object3d::getBoundingBox(){
  Point minPoint;
  Point maxPoint;
  minPoint.x_=vertex[0];
  minPoint.y_=vertex[1];
  minPoint.z_=vertex[2];
  maxPoint.x_=vertex[0];
  maxPoint.y_=vertex[1];
  maxPoint.z_=vertex[2];

  // Calcular punto mínimo y máximo
  for(int i=0; i<vertex.size(); i+=3){
    if(vertex[i] < minPoint.x_)
      minPoint.x_=vertex[i];
    if(vertex[i+1] < minPoint.y_)
      minPoint.y_=vertex[i+1];
    if(vertex[i+2] < minPoint.z_)
      minPoint.z_=vertex[i+2];
  }

  for(int i=0; i<vertex.size(); i+=3){
    if(vertex[i] > maxPoint.x_)
      maxPoint.x_=vertex[i];
    if(vertex[i+1] > maxPoint.y_)
      maxPoint.y_=vertex[i+1];
    if(vertex[i+2] > maxPoint.z_)
      maxPoint.z_=vertex[i+2];
  }

  this->min=minPoint;
  this->max=maxPoint;
}

  float Object3d::getSizeBox(){
    Point size;
    size.x_=(max.x_-min.x_);
    size.y_=(max.y_-min.y_);
    size.z_=(max.z_-min.z_);

    return module(size);
  }

Point Object3d::getCenter(){
  Point center;
  center.x_=((min.x_+max.x_)/2.0f);
  center.y_=((min.y_+max.y_)/2.0f);
  center.z_=((min.z_+max.z_)/2.0f);

  return center;
}

float Object3d::module(Point point){
  return (sqrt(point.x_*point.x_ + point.y_*point.y_ + point.z_*point.z_));
}

void Object3d::scale(){
  float scale = getSizeBox();
  glScalef(260.0f/scale,260.0f/scale,260.0f/scale);
}

void Object3d::translate(){
  Point center = getCenter();
    glTranslatef(-1*center.x_, -1*center.y_, -1*center.z_);
}

void Object3d::draw(unsigned char draw_modde, unsigned char object){

    // scale();
    // translate();

    // glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glLineWidth(2.0);           // Cambia el grosor de la linea. Pura estética.
    glPointSize(6.0);           // Cambia el grosor de los puntos. Pura estética.

    vector<float> colors;
    for(int i=0; i<vertex.size(); i++){         // Cambiamos el color a gris.
        colors.push_back(0.3);
        colors.push_back(0.3);
        colors.push_back(0.7);
    }

    glColorPointer(3, GL_FLOAT, 0, &colors[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);

    switch(object){
      case 'S':               // Dibujar solido
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        drawSolidAndLines();
        break;
      case 'L':              // Dibujar alambres
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
        break;
      case 'P':             // Dibujar puntos
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
        break;
      case 'A':              // Dibujar ajedrez
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        draw_chess();
        break;
    }
 }

 void Object3d::drawSolidAndLines(){

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);
   glLineWidth(1.2);
   vector<float> colors;
   for(int i=0; i<vertex.size(); i++){         // Cambiamos el color a gris.
       colors.push_back(0.9);
       colors.push_back(0.9);
       colors.push_back(0.9);
   }

   glColorPointer(3, GL_FLOAT, 0, &colors[0]);
   glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
   glPolygonOffset(-1,-1);

   glEnable(GL_POLYGON_OFFSET_LINE);

   colors.clear();

   for(int i=0; i<vertex.size(); i++){         // Cambiamos el color a negro.
       colors.push_back(0.38431);
       colors.push_back(0.17647);
       colors.push_back(0.54902);
   }

   glColorPointer(3, GL_FLOAT, 0, &colors[0]);
   glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
   glDisable(GL_POLYGON_OFFSET_LINE);
 }

void Object3d::draw_chess(){

    glLineWidth(2.0);
    glPointSize(6.0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    vector<int> caras_p1, caras_p2;
    vector<float> colores_p1, colores_p2;

    for(int i=0; i<triangles.size(); i=i+6){
        // Cara par   ->       0,2,4...
        caras_p1.push_back(triangles[i+0]);
        caras_p1.push_back(triangles[i+1]);
        caras_p1.push_back(triangles[i+2]);

        // Cara impar   ->      1,3,5...
        caras_p2.push_back(triangles[i+3]);
        caras_p2.push_back(triangles[i+4]);
        caras_p2.push_back(triangles[i+5]);

        // Añadimos al vector de colores los colores para las caras impares
        colores_p1.push_back(0.0);
        colores_p1.push_back(0.3);
        colores_p1.push_back(0.3);

        colores_p1.push_back(0.0);
        colores_p1.push_back(0.3);
        colores_p1.push_back(0.3);

        colores_p1.push_back(0.0);
        colores_p1.push_back(0.3);
        colores_p1.push_back(0.3);

        // Añadimos al vector de colores los colores para las caras paras
        colores_p2.push_back(0.0);
        colores_p2.push_back(1.0);
        colores_p2.push_back(0.0);

        colores_p2.push_back(0.0);
        colores_p2.push_back(1.0);
        colores_p2.push_back(0.0);

        colores_p2.push_back(0.0);
        colores_p2.push_back(1.0);
        colores_p2.push_back(0.0);
    }

    // Dibujamos caras pares
    glColorPointer(3, GL_FLOAT, 0, &colores_p1[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
    glDrawElements(GL_TRIANGLES, caras_p1.size(), GL_UNSIGNED_INT, &caras_p1[0]);

    // Dibujamos caras impares
    glColorPointer(3, GL_FLOAT, 0, &colores_p2[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
    glDrawElements(GL_TRIANGLES, caras_p2.size(), GL_UNSIGNED_INT,&caras_p2[0]);
    }

#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Object3d.h"

Object3d::Object3d(){
    this->vertex.clear();
    this->triangles.clear();
}

void Object3d::changeSize(float size){
    for(int i=0; i<vertex.size(); i++)
        vertex[i]*=size;
}

void Object3d::changeElem(){
  if(elem)
    elem=false;
  else
    elem=true;
}

bool Object3d::getElem(){
  return elem;
}

void Object3d::draw(unsigned char draw_mode){
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glLineWidth(2.0);           // Cambia el grosor de la linea. Pura estética.
    glPointSize(6.0);           // Cambia el grosor de los puntos. Pura estética.

    vector<float> colors;
    for(int i=0; i<vertex.size(); i++){         // Cambiamos el color a gris.
        colors.push_back(0.3);
        colors.push_back(0.3);
        colors.push_back(0.3);
    }

    glColorPointer(3, GL_FLOAT, 0, &colors[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);

    switch(draw_mode){
        case 'T':               // Dibujar solido
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
            break;
        case 'Y':              // Dibujar alambres
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
            break;
        case 'U':             // Dibujar puntos
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT,&triangles[0]);
            break;
        case 'C':              // Dibujar ajedrez
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            draw_chess();
            break;
      }
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

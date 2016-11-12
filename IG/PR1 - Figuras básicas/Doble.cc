#ifdef _WIN32
#include <windows.h>
#endif

#include <cstdio>

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "Doble.h"


Doble::Doble(){
  this->vertex= {0.0,0.0,50.0,        // V0
                50.0,0.0,50.0,     // V1
                0.0,50.0,50.0,    //  V2
                50.0,50.0,50.0,   // V3
                0.0,50.0,0.0,        // V4
                50.0,50.0,0.0,       // V5
                50.0,0.0,0.0,       // V6
                0.0,0.0,0.0};        // v7

  this->triangles={0,1,3,
                   1,6,3,
                   0,3,6,
                   0,6,1,

                   4,2,5,
                   2,5,7,
                   2,4,7,
                   4,5,7};
superior=true;
}

void Doble::draw(GLenum mode, int num){
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

  glPolygonMode(GL_FRONT_AND_BACK, mode);

  if(num==0){
    glDrawElements(GL_TRIANGLES, triangles.size()/2, GL_UNSIGNED_INT, &triangles[0]);
  }
  else if(num==1){
    glDrawElements(GL_TRIANGLES, triangles.size()/2, GL_UNSIGNED_INT, &triangles[12]);
  }
}

void Doble::draw_chess(int m){
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

  if(m==0){
    // Dibujamos caras pares
    glColorPointer(3, GL_FLOAT, 0, &colores_p1[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
    glDrawElements(GL_TRIANGLES, caras_p1.size(), GL_UNSIGNED_INT, &caras_p1[0]);

    // Dibujamos caras impares
    glColorPointer(3, GL_FLOAT, 0, &colores_p2[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
    glDrawElements(GL_TRIANGLES, caras_p2.size(), GL_UNSIGNED_INT,&caras_p2[0]);
  }
  else{
    // Dibujamos caras pares
    glColorPointer(3, GL_FLOAT, 0, &colores_p1[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
    glDrawElements(GL_TRIANGLES, caras_p1.size(), GL_UNSIGNED_INT, &caras_p1[0]);

    // Dibujamos caras impares
    glColorPointer(3, GL_FLOAT, 0, &colores_p2[0]);
    glVertexPointer(3, GL_FLOAT, 0,  &vertex[0]);
    glDrawElements(GL_TRIANGLES, caras_p2.size(), GL_UNSIGNED_INT,&caras_p2[0]);
  }
}

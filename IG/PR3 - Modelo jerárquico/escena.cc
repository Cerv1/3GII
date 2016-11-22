#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"
using namespace std;

Escena::Escena(){
    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 4*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);

}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);
  cube = new Cube();
  tetrahedron = new Tetrahedron();
  objectPly = new Ply();
  mecha = new Mechanic();

  // vector<float> perfil={3,4,0,	6,0,0,	2,-3,0,		3,-6,0};
  // vector<float> perfil={2,4,0,2,-4,0};


  vector<float> perfil={1,3,0,2,3,0,2.5,2,0,5,1,0,3.5,0,0};
  revo = new RevolutionObject(perfil,30);
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects(unsigned char shape) {
    switch(shape){
        case 'T':
            mecha->draw(shape,mode,nPos,nGrip,desp, nVer);
            break;
        case 'C':
            desp+=8;
            break;
        case 'c':
            desp-=8;
            break;
        case 'X':
            if(nVer<3.8)
                nVer+=0.1;
            break;
        case 'x':
            if(nVer>0.6)
                nVer+=-0.1;
            break;
        case 'Z':
            if(nGrip<10)
                nGrip+=3;
            break;
        case 'z':
            if(nGrip>-38)
                nGrip-=3;
            break;
        case 'V':
            nPos+=8;
            break;
        case 'v':
            nPos-=8;
            break;
      }
}

void Escena::dibujar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
    draw_objects(shape);
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {
	if(toupper(Tecla1)=='Q')
        return 1;
    else if(toupper(Tecla1) == 'S' || toupper(Tecla1) == 'L' || toupper(Tecla1) == 'P' || toupper(Tecla1) == 'A' ){
        mode=toupper(Tecla1);
        return 0;
    }
    else if(Tecla1 == 'Z')
        draw_objects(Tecla1);
    else if(Tecla1 == 'z')
        draw_objects(Tecla1);
    else if(Tecla1 == 'X')
        draw_objects(Tecla1);
    else if(Tecla1 == 'x')
        draw_objects(Tecla1);
    else if(Tecla1 == 'C')
        draw_objects(Tecla1);
    else if(Tecla1 == 'c')
        draw_objects(Tecla1);
    else if(Tecla1 == 'V')
        draw_objects(Tecla1);
    else if(Tecla1 == 'v')
        draw_objects(Tecla1);
    return 0;
}
    //   if(toupper(Tecla1)=='U'){
    //     string name;
    //     cout << "Ingrese el nombre del objeto ply: ";
    //     cin >> name;
    //     char * file = new char[name.length()+1];
    //     strcpy (file, name.c_str());
    //     objectPly->readPLY(file);
    //   }
    //   else if(toupper(Tecla1)=='O'){
    //     string name;
    //     cout << "Ingrese el nombre del objeto de revlucion ply: ";
    //     cin >> name;
    //     char * file = new char[name.length()+1];
    //     strcpy (file, name.c_str());
    //     revoPly = new RevolutionObject(file);
    //   }
    //   else if(Tecla1=='+'){
    //     draw_objects(Tecla1);
    //     return 0;
    //   }
    //   else if(Tecla1=='-'){
    //     draw_objects(Tecla1);
    //     return 0;
    //   }
    //   else if(Tecla1==1){
    //     if(tieneTapaSup)
    //       return 0;
    //     else
    //       tieneTapaSup=true;
    //   }
    //   else if(Tecla1==2){
    //     if(tieneTapaInf)
    //       return 0;
    //     else
    //       tieneTapaInf=true;
    //   }
    //   shape=toupper(Tecla1);
    //   draw_objects(shape);
    //   return 0;
    // else
    //     return 0;
// }

void Escena::teclaEspecial(int Tecla1,int x,int y) {
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	// std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformaci�n de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformaci�n de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}

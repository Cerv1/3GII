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

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects(unsigned char Tecla) {
  int para=0;
    switch(Tecla){
        case 'T':
            estado_dibujo='T';
            cube.draw('T');
            break;
        case 'Y':
            estado_dibujo='Y';
            cube.draw('Y');
            break;
        case 'U':
            estado_dibujo='U';
            cube.draw('U');
            break;
        case 'G':
            estado_dibujo='G';
            tetrahedron.draw('T');
            break;
        case 'H':
            estado_dibujo='H';
            tetrahedron.draw('Y');
            break;
        case 'J':
            estado_dibujo='J';
            tetrahedron.draw('U');
            break;
        case 'C':
            estado_dibujo='C';
            cube.draw('C');
            break;
        case 'V':
            estado_dibujo='V';
            tetrahedron.draw('C');
            break;
        case '+':
            cube.changeSize(1.2);
            tetrahedron.changeSize(1.2);
            break;
        case '-':
            cube.changeSize(0.8);
            tetrahedron.changeSize(0.8);
            break;

          case 'P':
              estado_dibujo='P';
              doble.draw(GL_FILL, 0);
              break;
            case 'O':
              estado_dibujo='O';
              doble.draw(GL_POINT, 0);
              break;
            case 'I':
              estado_dibujo='I';
              doble.draw(GL_LINE, 0);
              break;
            case 'A':
              estado_dibujo='A';
              doble.draw_chess(1);
              break;
              case 'S':
                estado_dibujo='S';
                doble.draw_chess(0);
                break;
              case 'R':
                estado_dibujo='R';
                doble.draw(GL_FILL, 1);
                break;
              case 'W':
                estado_dibujo='W';
                doble.draw(GL_POINT, 1);
                break;
              case 'E':
                estado_dibujo='E';
                doble.draw(GL_LINE, 1);
                break;
            }
}

void Escena::dibujar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
    draw_objects(estado_dibujo);
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {

    std::cout << "Tecla " << Tecla1<< std::endl;
	if(toupper(Tecla1)=='Q')
        return 1;
    else if(toupper(Tecla1) == 'T' || toupper(Tecla1) == 'Y' || toupper(Tecla1) == 'U' ||       // SOLIDO / MALLA / PUNTOS PARA CUBE
                toupper(Tecla1) == 'G' || toupper(Tecla1) == 'H' || toupper(Tecla1) == 'J'  ||      // SOLIDO / MALLA / PUNTOS PARA TETRAHEDRON
                toupper(Tecla1) == 'C' || toupper(Tecla1) == 'V' ||                                                     // MODO AJEDREZ PARA CUBE / MODO AJEDREZ PARA TETRAHEDRON
                Tecla1 == '+' || Tecla1 == '-' ||
                toupper(Tecla1) == 'P' || toupper(Tecla1) == 'O' || toupper(Tecla1) == 'I'
              || toupper(Tecla1) == 'R' || toupper(Tecla1) == 'W' || toupper(Tecla1) == 'E'){                                                                                             // AUMENTA TAMAÑO DE AMBOS / DISMINUYE TAMAÑO DE AMBOS
        draw_objects(toupper(Tecla1));
        return 0;
    }
	else return 0;
}

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

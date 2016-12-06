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


  objectPly = new Ply();
  mecha = new Mechanic();

  tommygun = new Ply();
  tommygun->scale();
  tommygun->translate();
  tommygun->readPLY("tommygun.ply");

  // vector<float> perfil={3,4,0,	6,0,0,	2,-3,0,		3,-6,0};
  // vector<float> perfil={2,4,0,2,-4,0};

  vector<float> perfil={1,3,0,2,3,0,2.5,2,0,5,1,0,3.5,0,0};
  revo = new RevolutionObject(perfil,30);
  revo->generateUpperCap();
  revo->generateLowerCap();
}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects(unsigned char shape) {
  switch(shape){
    case '1':
      mecha->draw(shape,mode,claw_rotation,claw_movement,horizontal_movement, vertical_displacement,vertical_movement);
      break;
    case '2':
      revo->scale();
      revo->translate();
      revo->draw(shape,mode);
      break;
    case '3':
      glScalef(250.0f,250.0f,250.0f);
      tommygun->translate();
      tommygun->draw(shape,mode);
      break;
    case 'C':
      if(horizontal_movement<295)
        horizontal_movement+=8;
      break;
    case 'c':
      if(horizontal_movement>-275)
        horizontal_movement-=8;
      break;
    case 'X':
      if(vertical_displacement<3.6)
        vertical_displacement+=0.1;
      break;
    case 'x':
      if(vertical_displacement>1.5)
        vertical_displacement+=-0.1;
      break;
    case 'Z':
      if(claw_movement<10)
        claw_movement+=3;
      break;
    case 'z':
      if(claw_movement>-38)
        claw_movement-=3;
      break;
    case 'V':
      claw_rotation+=8;
      break;
    case 'v':
      claw_rotation-=8;
      break;
    case 'D':
      if(vertical_movement<104)
        vertical_movement+=8;
      break;
    case 'd':
      if(vertical_movement>-430)
        vertical_movement-=8;
      break;
  }
}

void Escena::animate(){
  int control;
  if(global_speed==0)
    control=-3;
  else if(global_speed==1)
    control=0;
  else if(global_speed==2)
    control=3;


  if(animation_enabled){

    if(horizontal_movement<295 && !end_horizontal_movement){
        horizontal_movement+=(6+control);
        if(horizontal_movement>295) end_horizontal_movement=true;
    }
    else if(horizontal_movement>-275 && end_horizontal_movement){
        horizontal_movement-=(6+control);
        if(horizontal_movement<-275) end_horizontal_movement=false;
    }

    if(vertical_movement<104 && !end_vertical_movement){
        vertical_movement+=(6+control);
        if(vertical_movement>104) end_vertical_movement=true;
    }
    else if(vertical_movement>-430 && end_vertical_movement){
        vertical_movement-=(6+control);
        if(vertical_movement<-430) end_vertical_movement=false;
    }

    if(vertical_displacement<3 && !end_vertical_displacement){
        vertical_displacement+=0.1;
        if(vertical_displacement>3) end_vertical_displacement=true;
    }
    else if(vertical_displacement>1.7 && end_vertical_movement){
        vertical_displacement-=0.1;
        if(vertical_displacement<1.7) end_vertical_displacement=false;
    }

    if(claw_movement<10 && !end_claw_movement){
        claw_movement+=3;
        if(claw_movement>10) end_claw_movement=true;
    }
    else if(claw_movement>-38 && end_claw_movement){
        claw_movement-=3;
        if(claw_movement<-38) end_claw_movement=false;
    }

    if(speed_claw==0)
      claw_rotation=0;
    else if(speed_claw==1)
      claw_rotation+=10;
    else if(speed_claw==2)
      claw_rotation+=50;
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

  if(Tecla1 == '1' || Tecla1 == '2' || Tecla1 == '3'){
    shape=Tecla1;
    draw_objects(Tecla1);
  }

  else if(Tecla1 == 'Z' || Tecla1 == 'z')
    draw_objects(Tecla1);
  else if(Tecla1 == 'X' || Tecla1 == 'x')
    draw_objects(Tecla1);
  else if(Tecla1 == 'C' || Tecla1 =='c')
    draw_objects(Tecla1);
  else if(Tecla1 == 'V' || Tecla1 == 'v')
    draw_objects(Tecla1);
  else if(Tecla1 == 'D' || Tecla1 == 'd')
    draw_objects(Tecla1);
  else if(Tecla1 == 'b')
    speed_claw=(speed_claw+1)%3;
  else if(Tecla1 == 'n')
    global_speed=(global_speed+1)%3;
  else if(Tecla1 == '-')
    (animation_enabled) ? animation_enabled=false : animation_enabled=true;

  return 0;
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

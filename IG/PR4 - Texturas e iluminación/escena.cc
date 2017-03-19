#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"
#include "bitmap_image.hpp"

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

  int n = 60;
  float alpha = M_PI/2, suma = 2*M_PI/n, radio = 100.0;
  vector<float> perfil_esfera;
  for(int i=0; i<=n/2; i++){
    perfil_esfera.push_back(-radio*cos(alpha));
    perfil_esfera.push_back(-radio*sin(alpha));
    perfil_esfera.push_back(0.0);
    alpha += suma;
  }

  esfera = new RevolutionObject(perfil_esfera, 100);
  esfera->scale();
  esfera->translate();
  esfera->calculateNormalArray();

  lata_body=new RevolutionObject("lata-pcue.ply");
  lata_body->translate();
  lata_body->calculateNormalArray();

  lata_sup=new RevolutionObject("lata-psup.ply");
  lata_sup->translate();
  lata_sup->generateUpperCap();
  lata_sup->calculateNormalArray();

  lata_inf=new RevolutionObject("lata-pinf.ply");
  lata_inf->translate();
  lata_inf->calculateNormalArray();

  white_peon=new RevolutionObject("revo.ply");
  white_peon->translate();
  white_peon->generateUpperCap();
  white_peon->generateLowerCap();
  white_peon->calculateNormalArray();

  black_peon=new RevolutionObject("revo.ply");
  black_peon->translate();
  black_peon->generateUpperCap();
  black_peon->generateLowerCap();
  black_peon->calculateNormalArray();
  black_peon->set_black_material();

  texture_peon=new RevolutionObject("revo.ply");
  texture_peon->translate();
  texture_peon->generateUpperCap();
  texture_peon->generateLowerCap();
  texture_peon->calculateNormalArray();

  objectPly = new Ply();
  mecha = new Mechanic();

  tommygun = new Ply();

  tommygun->translate();
  tommygun->readPLY("beethoven.ply");
  tommygun->calculateNormalArray();


  vector<float> perfil={1,3,0,2,3,0,2.5,2,0,5,1,0,3.5,0,0};
  revo = new RevolutionObject(perfil,60);
  revo->calculateNormalArray();

  glGenTextures( 1, &lata_body->idTex);
  glBindTexture(GL_TEXTURE_2D, lata_body->idTex);

  bitmap_image img("text-lata-1.bmp"); // Carga la imagen
  img.bgr_to_rgb(); // Pasa a formato RGB, ya que usa BGR por defecto
  std::cout << "Imagen de " << img.width() << " por " << img.height() << " pixels.\n";
  img.horizontal_flip();
  // img.vertical_flip();
  gluBuild2DMipmaps( GL_TEXTURE_2D,
    GL_RGB, // formato interno
    img.width(), // núm. de columnas (arbitrario)
    img.height(), // núm de filas (arbitrario)
    GL_RGB, // formato y orden de los texels en RAM
    GL_UNSIGNED_BYTE, // tipo de cada texel
    img.data()
  );

  glGenTextures(1,&texture_peon->idTex);
  glBindTexture(GL_TEXTURE_2D, texture_peon->idTex);

  bitmap_image img2("text-madera.bmp"); // Carga la imagen
  img2.bgr_to_rgb(); // Pasa a formato RGB, ya que usa BGR por defecto
  std::cout << "Imagen de " << img2.width() << " por " << img2.height() << " pixels.\n";

  gluBuild2DMipmaps( GL_TEXTURE_2D,
    GL_RGB, // formato interno
    img2.width(), // núm. de columnas (arbitrario)
    img2.height(), // núm de filas (arbitrario)
    GL_RGB, // formato y orden de los texels en RAM
    GL_UNSIGNED_BYTE, // tipo de cada texel
    img2.data()
  );

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects(unsigned char shape) {

  if(luces_enabled){
     glEnable(GL_TEXTURE_2D);
    if(positional_enabled){
      directionalLight.disable();
      positionalLight.set_up();
      positionalLight.move_light(postionLight);
    }
    else{
      // positionalLight.disable();
      // directionalLight.enable();
      blueLight.setBlueLight( disco);
      redLight.setRedLight( disco);
      greenLight.setGreenLight( disco);
      directionalLight.move_light(postionLight);
    }
  }
  else{
      glDisable(GL_TEXTURE_2D);
  }

  //GL BIND TEXTURE SOBRE REVOLUCION EN Escena
  // CARGAR IMAGENES, BINDEAR IMAGENES
  // DRAW->ENABLE ARRAY     IF CON LAS TEXTURAS QUE BINDEAR

  switch(shape){
    case '1':
      mecha->draw(shape,mode,claw_rotation,claw_movement,horizontal_movement, vertical_displacement,vertical_movement);
      break;
    case '2':
      esfera->draw(shape,mode);
      break;
    case '3':
      glScalef(25.0f,25.0f,25.0f);
      tommygun->draw(shape,mode);
      break;
    case '4':
        glPushMatrix();
            glRotatef(90,0,1,0);
            glScalef(125.0f,125.0f,125.0f);
            lata_sup->set_white_material();
            lata_sup->draw(shape,mode);
            lata_body->set_shiny_material();
            lata_body->draw(shape,mode);
            lata_inf->no_material();
            lata_inf->draw(shape,mode);
        glPopMatrix();
        glScalef(125.0f,125.0f,125.0f);
        glScalef(0.18,0.18,0.18);
        glTranslatef(0,1.25,4);
        white_peon->set_white_material();
        white_peon->draw(shape,mode);

        glTranslatef(3,0,0);
        black_peon->set_black_material();
        black_peon->draw(shape,mode);

        glTranslatef(-6,0,0);
        texture_peon->set_shiny_material();
        texture_peon->draw(shape,mode);

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
  glDisable(GL_LIGHTING);

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
  if(luces_enabled){

    if(postionLight<2500 && light_animate)
      postionLight+=50;
    else{
      light_animate=false;
      postionLight-=50;
      if(postionLight<-2500)
        light_animate=true;
    }

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

  if(Tecla1 == '1' || Tecla1 == '2' || Tecla1 == '3' || Tecla1=='4'){
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
    postionLight-=25;
  else if(Tecla1 == '+')
    postionLight+=25;
    // (animation_enabled) ? animation_enabled=false : animation_enabled=true;
  else if(Tecla1=='7'){
    (luces_enabled) ? luces_enabled=false : luces_enabled=true;
  }
  else if(Tecla1=='8'){
    (positional_enabled) ? positional_enabled=false : positional_enabled=true;
  }
  else if(Tecla1=='i'){
      alfa+=10;
  }
  else if(Tecla1=='o'){
      alfa-=10;
  }
  else if(Tecla1=='y'){
      alfa+=10;
  }
  else if(Tecla1=='u'){
      alfa-=10;
  }



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

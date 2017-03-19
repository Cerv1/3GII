#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "Object3d.h"
#include "Ply.h"
#include "Mechanic.h"
#include "RevolutionObject.h"
#include "file_ply_stl.h"
#include "Light.h"
#include "Directional.h"
#include "Positional.h"
#include "Texture.h"


using namespace std;


class Escena {
private:
// tama�o de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

Directional directionalLight;
Positional positionalLight;

Directional redLight;
Directional blueLight;
Directional greenLight;
int disco=0;

unsigned char * texture;
float postionLight=0.0;
bool luces_enabled=true;
bool positional_enabled=true;
bool light_animate=true;
Texture *tex,*tex_m;
RevolutionObject *esfera;
bool tieneTapaSup=false;
bool tieneTapaInf=false;
bool tapasQuitadas=false;
float alfa=0;
float beta=0;

Ply *objectPly;
Ply *tommygun;
RevolutionObject *lata_body, *lata_sup, *lata_inf;
RevolutionObject *white_peon, *black_peon, *texture_peon;
RevolutionObject *revo;
RevolutionObject *revoPly;
Mechanic *mecha;

int claw_rotation=1;
int claw_movement=0;
int horizontal_movement=0;
int vertical_movement=0;
float vertical_displacement=1;

int speed_claw=1;
int global_speed=0;
int speed_vertical=0;
int speed_updown=0;

bool animation_enabled=true;
bool end_horizontal_movement=false;
bool end_vertical_movement=false;
bool end_vertical_displacement=false;
bool end_claw_movement=false;

unsigned char shape='4';
unsigned char mode='S';

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

private:
	void clear_window();
	void draw_axis();
	void draw_objects(unsigned char shape);


//Transformaci�n de c�mara
	void change_projection();
	void change_observer();


public:
     Escena();
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;
	void animate();

	// Interacci�n con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);
};
#endif

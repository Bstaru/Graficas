#ifndef _OPENGL_MANAGER_H
#define _OPENGL_MANAGER_H

#include <windows.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Terrain_v2.h"
#include "Camera_v2.h"
#include "Dome.h"
#include "Model.h"
#include "Water.h"
#include "Objetos.h"
#include "Matrices.h"
//#include "Billboard.h"
#include <math.h>

int x;
float wuh;

void neblina();

#define velocidad 30.0f

class OpenGLManager
{
public:
	Matriz*mat;

	Terrain*piso;
	Terrain*piso2;

	Water*agua;

	Camera*MainCamera;

	Dome*Domito;
	Dome*Domito2;

	Model*ovni;
	Model*pasto1;
	Model*House;
	Model*pulpin;
	Model*pino;
	Model*pusheen;
	Model*nyancat;
	Model*arco;
	Model*galleta;
	Model*dona;
	Model*palomitas;
	Model*burger;
	Model*pizza;
	Model*soda;
	Model*papas;
	Model*pastel;
	
	float p1x, p1y, p1z;
	float p2x, p2y, p2z;
	float p1rad;
	float p2rad,distance;
	float p3x,p3y,p3z,p4x,p4y,p4z,p3rad,p4rad,distance2;
	float p5x,p5y,p5z,p6x,p6y,p6z,p5rad,p6rad,distance3;
	float p7x,p7y,p7z,p8x,p8y,p8z,p7rad,p8rad,distance4;
	float altura;
	float movagua;
	float movani1;
	float movani2;
	float movani3;
	float movani4;
	float movani44;
	float movani5;
	float intensity;
	float ang;
	float ang_camera;
	bool nie;
	int c;
	int cambio_cielo;
	float part1,part2,part3,part4,part5,part6,part7,part8;
	float cx,cz, ang_carr, px,pz,ang_piz;
	float ppx,ppy,ppz;

public:
	OpenGLManager(HWND hWnd)
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		glEnable(GL_BLEND);									//Niebla
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	///Transparencia
		glEnable(GL_FOG);									//Niebla
		//iluminacion
		//glEnable(GL_LIGHTING);

		Initialize();

	}

	~OpenGLManager()
	{
		//delete music;
	}

	void Initialize()
	{
		MainCamera=new Camera();

		piso=new Terrain("TEXT//height_map1.bmp","TEXT//grass2.bmp");
		piso2=new Terrain("TEXT//height_map1.bmp","TEXT//mountain.bmp");

		Domito2=new Dome("TEXT/skynight.bmp",200.0f,90,90);
		Domito=new Dome("TEXT/sky.bmp",200.0f,90,90);

		agua=new Water("TEXT/water.bmp");

		nyancat= new Model("MOD//NYANCAT_SOLO.obj","TEXT//gato.bmp");
		arco= new Model("MOD//ARCOIRIS.obj","TEXT//arco.bmp");
		pino=new Model("MOD//trees.obj","TEXT//arbolpino.bmp");
		House= new Model("MOD//CasaSimples.obj","TEXT//casaSimples_D.bmp");
		pulpin= new Model("MOD//pulpo.obj","TEXT//pulpo.bmp");
		pusheen= new Model("MOD//pusheen.obj","TEXT//pusheen.bmp");		
		galleta=new Model("MOD//galleta.obj","TEXT//cookie.bmp");
		dona=new Model("MOD//dona.obj","TEXT//dona.bmp"); 
		palomitas=new Model("MOD//palomitas.obj","TEXT//palo.bmp");
		burger=new Model("MOD//burger.obj","TEXT//burger.bmp");
		pizza=new Model("MOD//pizza.obj","TEXT//pizza.bmp");
		soda=new Model("MOD//soda.obj","TEXT//vasoekisde.bmp");
		papas=new Model("MOD//papas.obj","TEXT//papas.bmp");
		pastel=new Model("MOD//pastel.obj","TEXT//cake.bmp");

		
		p1x=1200; p1y=-50; p1z=-300;
		p2x=70;p2y=-250;p2z=-340;

		p1rad=6;
		p2rad=3900;
		movagua=0;
		movani1=600;
		movani2=0;
		movani3=10;
		movani4=0;
		movani44=0;
		movani5=0;

		part1=-100;
		part2=-100;
		part3=-100;
		part4=-100;
		part5=-100;
		part6=-100;
		part7=-100;
		part8=-100;

		cx=650;
		cz=-1000;
		ang_carr=90;
		px=1715;
		pz=-1515;
		ang_piz=270;

		ppx=2010;
		ppy=-50;
		ppz=-3390;

		intensity=4000;
		nie=false;
		ang=180;
		ang_camera=90;
		c=0;
		cambio_cielo=1;
		
		//colisiones
		p3rad=200;
		p4rad=25;
		p3x=400;
		p3y=-57;
		p3z=-635;
		p4x=0;p4y=0;p4z=0;


		//Casa-------
		p5x=1100;
		p5y=-40;
		p5z=-1300;
		//-----
		//Colisión de la casa
		p6x=1100;p6y=-60;p6z=-1200;

		p5rad=300;
		p6rad=490;

		p7x=-1000;
		p7y=-30;
		p7z=-2000;

		p8x=0;p8y=0;p8z=0;
		p7rad=225;
		p8rad=220;

	}

	void Draw(HDC hDC)
	{
pegar_domo();
colision_obj1();
colision_obj2();
colision_obj3();

		//borramos el biffer de color y el z para el control de profundidad a la 
		//hora del render a nivel pixel.
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		GLfloat LightAmb[] = { 0.0, 0.0,0.0, 0.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmb);
		glLoadIdentity();
	ControledCamera();
//___________________________________TECLAS DE LA MUSICA_______________________________________

	if (GetKeyState('M') & 8000){
			 PlaySound("NyanCatRemix.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);}

	if (GetKeyState('N') & 8000) {
			PlaySound("sln.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);}

//_______________________TECLAS PARA CAMBIAR EL CIELO _________________________________________
	if (cambio_cielo==1)
	{ if (GetKeyState('Z') & 8000) { cambio_cielo=2;}
	}

	if (cambio_cielo==2)
	{ if (GetKeyState('X') & 8000) { cambio_cielo=1;}
	}	
//_______________________TECLAS PARA CAMBIAR LA NEBLINA _________________________________________
	
	if (GetKeyState('P') & 8000) //PRENDE
	{ nie=true; }

	if(GetKeyState('O') & 8000) //APAGA
	{nie=false;	}

	if(GetKeyState('L') & 8000) //INTNSIDAD +
	{intensity=intensity-100;}

	if(GetKeyState('K') & 8000) //INTENSIDAD -
	{intensity=intensity+100;}


	if (nie==true){ neblina();}
	else{ glDisable(GL_FOG);}

//________________________________________________________________________________

	
		//Piso0---------------------------------------------------
		glPushMatrix();
		mat->trasladar(0,-50,-3800);
		
		mat->escalar(50,-10,50);
		piso->Draw();
		glPopMatrix();
		
		altura=piso->GetAltitude(p1x/50-1200,p1z/50+300);

		if(altura-50>=p1y)
		{
			p1y=p1y+30;
			MainCamera->MoveUpward(+30);
		}

		glPushMatrix();
		mat->trasladar(-800,-250,-3800);
		mat->escalar(50,10,50);
		piso2->Draw();
		glPopMatrix();

		//Domo----------------------------------------------------------------------------
		glPushMatrix();
		if (cambio_cielo==1)
		{
		mat->trasladar(0,-250,0);
		mat->escalar(20,20,25);
		if(wuh<=360){
			mat->rotar(wuh,0,1,0);
			wuh+=0.015;
		}
		Domito->Draw();
		}
		if (cambio_cielo==2)
		{
		mat->trasladar(0,-250,0);
		mat->escalar(20,20,25);

		if(wuh<=360){
			mat->rotar(wuh,0,1,0);
			wuh+=0.015;
		}
		else {wuh=0;}
		Domito2->Draw();
		}

		glPopMatrix();
		
		//Agua-----------------------------------------------------------------------------------------
		glPushMatrix();

		if (movagua <= 10)
		{
			movagua=movagua+1;
		}

		if (movagua == 10)
		{
			movagua=0;
		}
		mat->trasladar(movagua,-60,0);
		mat->escalar(180,180,180);
		glColor4f(1.0,1.0,1.0,0.9);
		agua->Draw();
		glColor3f(1.0,1.0,1.0);
		glPopMatrix();

		
		//Particles (?)-----------------------------------------------------------------------------------------
glPushMatrix();
		if (part1 <= 20)
		{
			part1=part1+1;
		}

		if (part1 == 20)
		{
			part1=-100;
		}
		mat->trasladar(400,part1,-3500);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part2 <= 50)
		{
			part2=part2+2;
		}

		if (part2 == 50)
		{
			part2=-100;
		}
		mat->trasladar(600,part2,-3500);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part3 <= 40)
		{
			part3=part3+2.5;
		}

		if (part3 == 40)
		{
			part3=-70;
		}
		mat->trasladar(300,part3,-3400);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part4 <= 20)
		{
			part4=part4+2;
		}

		if (part4 == 20)
		{
			part4=-80;
		}
		mat->trasladar(500,part4,-3400);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part5 <= 25)
		{
			part5=part5+2.5;
		}

		if (part5 == 25)
		{
			part5=-90;
		}
		mat->trasladar(350,part5,-3600);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part6 <= 60)
		{
			part6=part6+1;
		}

		if (part6 == 60)
		{
			part6=-85;
		}
		mat->trasladar(400,part6,-3250);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part7 <= 40)
		{
			part7=part7+2;
		}

		if (part7 == 40)
		{
			part7=-110;
		}
		mat->trasladar(560,part7,-3158);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();

glPushMatrix();
		if (part8 <= 30)
		{
			part8=part8+1;
		}

		if (part8 == 30)
		{
			part8=-120;
		}
		mat->trasladar(381,part8,-3158);
		glColor3f(0.0f,1.0f,1.0f);
		glutSolidSphere(5,32,32);
		glColor3f(1.0f,1.0f,1.0f);
glPopMatrix();


//________________________________________________________MODELOS _______________________________________________________
//Arboles-----------------------------------------------------------------------------------------
		glPushMatrix();
			mat->trasladar(p3x,p3y,p3z);
			mat->escalar(5,5,5);
		pino->Draw();
		glPopMatrix();

		glPushMatrix();
			mat->trasladar(-1500,-60,-2000);
			mat->escalar(5,5,5);
		pino->Draw();
		glPopMatrix();

		glPushMatrix();
			mat->trasladar(2500,-60,-1560);
			mat->escalar(7,7,7);
		pino->Draw();
		glPopMatrix();

		glPushMatrix();
			mat->trasladar(2500,-60,-2560);
			mat->escalar(7,7,7);
		pino->Draw();
		glPopMatrix();

		glPushMatrix();
			mat->trasladar(-2500,-60,-1560);
			mat->escalar(7,7,7);
		pino->Draw();
		glPopMatrix();

		glPushMatrix();
			mat->trasladar(-500,-60,-200);
			mat->escalar(5,5,5);
		pino->Draw();
		glPopMatrix();

		glPushMatrix();
			mat->trasladar(0,0,0);
			mat->escalar(15,15,15);
		pino->Draw();
		glPopMatrix();

//pasteeeel-----------------------------------------------------------------------------------------
		glPushMatrix();
		mat->trasladar(p5x,p5y,p5z);
			mat->escalar(15,15,15);
		pastel->Draw();
		glPopMatrix();
//-----hamburguesa-----------------------------------------
		glPushMatrix();
		if (movani44 <= 360) { movani44=movani44+1; }
		if (movani44 == 360) { movani44=0; }
		if (p7y>=-30) { p7y=p7y+1; }
		if (p7y==20) { p7y=20; }
		mat->trasladar(p7x, p7y, p7z);
		mat->rotar(movani44,0,1,0);
		mat->escalar(10,10,10);
		burger->Draw();
		glPopMatrix();
//-----dona----------------------------------------------------
		glPushMatrix();
		if ((p1z<=-1470)&&(p1z>=-1980)) {
		if (movani4 <= 360) { movani4=movani4+1; }
		if (movani4 == 360) { movani4=0; }
		}
		mat->trasladar(2000, 500, -1800);
		mat->rotar(movani4,0,1,0);
		mat->escalar(10,10,10);
		dona->Draw();
		glPopMatrix();
		
//arbol que se mueve rotando en y-----------------------------------------------------------------------------------------
		glPushMatrix();
		if ((p1z<=-1650)&&(p1z>=-2250)){
		if (movani2 <= 360) {movani2=movani2+1;}
		if (movani2 == 360) {movani2=0;}
		}
		mat->trasladar(10,-60,-2000);
			mat->escalar(10,10,10);
			mat->rotar(movani2,0,1,0);
		pino->Draw();
		glPopMatrix();
//galleta---------------------------------------------------------------------------------------------
		glPushMatrix();
		if ((p1z<=-1890)&&(p1z>=-3390)) { 
			if ((p1x<=3000)&&(p1x>=1500)) {
			ppx=p1x+20;
			ppy=p1y;
			ppz=p1z-100;
			}
		}
		mat->trasladar(ppx,ppy,ppz);
		mat->rotar(-180,0,1,0);
		mat->escalar(1,1,1);
		galleta->Draw();
		glPopMatrix();
//pulpo-----------------------------------------------------------------------------------------
		glPushMatrix();
		if ((p1z<=-3060)&&(p1z>=-4800)) {
		if (movani1 <= 2000) {movani1=movani1+5;}
		if (movani1 == 2000) {movani1=600;}
		}
		mat->trasladar(movani1,-60,-3780);
		mat->rotar(90,0,1,0);
		mat->escalar(5,5,5);
		pulpin->Draw();
		glPopMatrix();
//nyancat2------------------------------------------------------------------------------------
		glPushMatrix();
		if ((p1z<=-3060)&&(p1z>=-4800)) {
		if (movani5 <= 2000){ movani5=movani1+5; }
		if (movani5 == 2000){ movani5=600; }
		}
		mat->trasladar(movani5,500,-3780);
		mat->rotar(90,0,1,0);
		mat->escalar(5,5,5);
		nyancat->Draw();
		if((p1z<=-3060)&&(p1z>=-4800)){
				arco->Draw();}
		glPopMatrix();
//pusheen----------------------------------------------------------------------------------------
		glPushMatrix();
		if (cx <= 1710) { cx=cx+5; }
		if (cx == 1715) { ang_carr=180; }
		if (ang_carr == 180){ cz=cz-5;}
		if (cz <= -1410) { cz=-1410; ang_carr=270;}
		mat->trasladar(cx,-7,cz);
		mat->escalar(5,5,5);
		mat->rotar(ang_carr,0,1,0);
		pusheen->Draw();
		glPopMatrix();
//pizzaaaaaa-----------------------------------------------------------------------------------
		glPushMatrix();
		if (cz==-1410 && px <= 1715) { px = px-5; }
		//if (px == 1710) { ang_piz=0;}
		//if (ang_piz == 0){ pz=pz=+5;}
		mat->trasladar (px,50,pz);
		mat->escalar (5,5,5);
		mat->rotar (ang_piz,0,1,0);
		pizza ->Draw();
		glPopMatrix();
//nyancat-----------------------------------------------------------------------------------------
		glPushMatrix();		
		//H
		if (ang==180)
		{
		mat->trasladar(p1x, p1y, p1z);
		mat->rotar(ang,0,1,0);
			mat->escalar(1,1,1);
			nyancat->Draw();
			if(p1y>=10){
				arco->Draw();}
		}
		//D
		if (ang==90)
		{
		mat->trasladar(p1x+200, p1y, p1z+200);
		mat->rotar(ang,0,1,0);
			mat->escalar(1,1,1);
			nyancat->Draw();
			if(p1y>=10){
				arco->Draw();}
		}
		//F
		if (ang==0)
		{
		mat->trasladar(p1x, p1y, p1z+400);
		mat->rotar(ang,0,1,0);
			mat->escalar(1,1,1);
			nyancat->Draw();
			if(p1y>=10){
				arco->Draw();}
		}
		//G
		if (ang==270)
		{
		mat->trasladar(p1x-200, p1y, p1z+200);
		mat->rotar(ang,0,1,0);
		mat->escalar(1,1,1);
			nyancat->Draw();
			if(p1y>=10){
				arco->Draw();}
		}	
		glPopMatrix();

		SwapBuffers(hDC);
	}

void ControledCamera(){

		MainCamera->Update();

		if (c==0)
		{
			if (GetKeyState('U') & 8000)
			{
				MainCamera->camcam(true,false);
				c=1;
			}

			if (GetKeyState('Y') & 8000)
				{
				MainCamera->camcam(false,true);
				c=1;
			}
		}

		if (ang==180) //-----------------------------------------------------------------------180
		{
		if (GetKeyState(VK_UP) & 8000) {MainCamera->MoveForward(-velocidad);
		p1z= p1z-30;
		c=0;}
		if (GetKeyState(VK_DOWN) & 8000) {MainCamera->MoveForward(velocidad);
		p1z = p1z+30;
		c=0;}
		if (GetKeyState(VK_RIGHT) & 8000) { MainCamera->StrafeRight(velocidad);
		p1x=p1x+30;
		c=0;}
		if (GetKeyState(VK_LEFT) & 8000) { MainCamera->StrafeRight(-velocidad);
			p1x=p1x-30;
		c=0;}
		
		if (GetKeyState('W') & 8000){MainCamera->MoveUpward(velocidad);
		p1y=p1y+30;
		c=0;
		}
		if (GetKeyState('S') & 8000){MainCamera->MoveUpward(-velocidad);
		p1y=p1y-30;
		c=0;}

		if (GetKeyState('D') & 8000) {MainCamera->RotateY(-90);
		ang=90;
		c=0; }

		if (GetKeyState('G') & 8000){MainCamera->RotateY(90);
	
		ang=270;
		c=0;
		}
		}


		if (ang==90) //-----------------------------------------------------------------------90
		{
		if (GetKeyState(VK_UP) & 8000) {MainCamera->MoveForward(-velocidad);
		p1x= p1x+30;
		c=0;}
		if (GetKeyState(VK_DOWN) & 8000) {MainCamera->MoveForward(velocidad);
		p1x = p1x-30;
		c=0;}
		if (GetKeyState(VK_RIGHT) & 8000) { MainCamera->StrafeRight(velocidad);
		p1z=p1z+30;
		c=0;}
		if (GetKeyState(VK_LEFT) & 8000) { MainCamera->StrafeRight(-velocidad);
			p1z=p1z-30;
		c=0;}
		
		if (GetKeyState('W') & 8000){MainCamera->MoveUpward(velocidad);
		p1y=p1y+30;
		c=0;
		}
		if (GetKeyState('S') & 8000){MainCamera->MoveUpward(-velocidad);
		p1y=p1y-30;
		c=0;}
		if (GetKeyState('F') & 8000){MainCamera->RotateY((-ang_camera));

		ang=0;
		c=0;
		}
		
		if (GetKeyState('H') & 8000){MainCamera->RotateY(ang_camera);
		ang=180;
		c=0;
		}
		}


		if (ang==0)  //-----------------------------------------------------------------------0
		{
		if (GetKeyState(VK_UP) & 8000) {MainCamera->MoveForward(-velocidad);
		p1z= p1z+30;
		c=0;}
		if (GetKeyState(VK_DOWN) & 8000) {MainCamera->MoveForward(velocidad);
		p1z = p1z-30;
		c=0;}
		if (GetKeyState(VK_RIGHT) & 8000) { MainCamera->StrafeRight(velocidad);
		p1x=p1x-30;
		c=0;}
		if (GetKeyState(VK_LEFT) & 8000) { MainCamera->StrafeRight(-velocidad);
			p1x=p1x+30;
		c=0;}
		
		if (GetKeyState('W') & 8000){MainCamera->MoveUpward(velocidad);
		p1y=p1y+30;
		c=0;
		}
		if (GetKeyState('S') & 8000){MainCamera->MoveUpward(-velocidad);
		p1y=p1y-30;
		c=0;}
		if (GetKeyState('G') & 8000) {MainCamera->RotateY(-90);
		ang=270;
		c=0;
			}
		if (GetKeyState('D') & 8000){MainCamera->RotateY(90);
		ang=90;
		c=0;
		}

		}

		if (ang==270)  //-----------------------------------------------------------------------270
		{
		if (GetKeyState(VK_UP) & 8000) {MainCamera->MoveForward(-velocidad);
		p1x= p1x-30;
		c=0;}

		if (GetKeyState(VK_DOWN) & 8000) {MainCamera->MoveForward(velocidad);
		p1x = p1x+30;
		c=0;}

		if (GetKeyState(VK_RIGHT) & 8000) { MainCamera->StrafeRight(velocidad);
		p1z=p1z-30;
		c=0;}

		if (GetKeyState(VK_LEFT) & 8000) { MainCamera->StrafeRight(-velocidad);
			p1z=p1z+30;
		c=0;}
		
		if (GetKeyState('W') & 8000){MainCamera->MoveUpward(velocidad);
		p1y=p1y+30;
		c=0;}

		if (GetKeyState('S') & 8000){MainCamera->MoveUpward(-velocidad);
		p1y=p1y-30;
		c=0;}
		
		if (GetKeyState('H') & 8000){MainCamera->RotateY((-ang_camera));
		ang=180;
		c=0;}

		if (GetKeyState('F') & 8000){MainCamera->RotateY(ang_camera);
		ang=0;
		c=0;}

		}

	}
	
	void neblina()
	{
		glEnable(GL_FOG);
		float fogColor[]={0.5,0.5,0.5,0.2};
		glFogfv(GL_FOG_COLOR,fogColor);
		glFogi(GL_FOG_MODE,GL_LINEAR);
		glFogf(GL_FOG_START,0.0f);
		glFogf(GL_FOG_END,intensity);


	}

	void pegar_domo()
	{
		distance=sqrt(((p2x-p1x)*(p2x-p1x))+((p2y-p1y)*(p2y-p1y))+((p2z-p1z)*(p2z-p1z)));
		if (distance<=p1rad+p2rad)
		{
			p1z = p1z;
			p1y=p1y;
			p1x=p1x;

		}


		else
		{ 
			
			if ((p1z<=-3060)&&(p1z>=-4800))
			{

			p1z=p1z+30;
			MainCamera->MoveForward(+velocidad);
			}
			
			if ((p1y<=3300)&&(p1y>=2590))
			{
				p1y=p1y-30;
				MainCamera->MoveUpward(-velocidad);
			}

			if ((p1x<=4500)&&(p1x>=3000))
			{
				p1x=p1x-30;
				MainCamera->StrafeRight(-velocidad);
			}

			if ((p1x<=-3090)&&(p1x>=-3900))
			{
				p1x=p1x+30;
				MainCamera->StrafeRight(+velocidad);
			}

			if ((p1z<=4620)&&(p1z>=2970))
			{

			p1z=p1z-30;
			MainCamera->MoveForward(-velocidad);
			}
		}
		
	}

	void colision_obj1()
	{
		distance2 = sqrt(((p1x - p3x) * (p1x - p3x)) + ((p1y - p3y) * (p1y - p3y)) + ((p1z - p3z) * (p1z - p3z)));


		if (distance2 <= p3rad + p1rad)
		{

			if((p1x>=240) && (p1x<=550))
			{
				p1z=p1z+30;
				MainCamera->MoveForward(+30);
			}

		}
	}
		

	void colision_obj2()
	{
		distance3 = sqrt(((p1x - p6x) * (p1x - p6x)) + ((p1y - p6y) * (p1y - p6y)) + ((p1z - p6z) * (p1z - p6z)));


		if (distance3 <= p5rad + p1rad)
		{

			if((p1x>=720) && (p1x<=1560))
			{
				p1z=p1z+30;
				MainCamera->MoveForward(+30);
			}

		}
	}


	void colision_obj3()
	{
			distance4 = sqrt(((p1x - p7x) * (p1x - p7x)) + ((p1y - p7y) * (p1y - p7y)) + ((p1z - p7z) * (p1z - p7z)));


		if (distance4 <= p7rad + p1rad)
		{

			if((p1x>=-1170) && (p1x<=-810))
			{
				p1z=p1z+30;
				MainCamera->MoveForward(+30);
			}

		}
	}
	
	
	
};
#endif 
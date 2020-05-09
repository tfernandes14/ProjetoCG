#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "RgbImage.h"
#include "materials.h"

using namespace std;

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

GLfloat tam = 0.5;
GLfloat distX = 6;
GLfloat distZ = 3;
GLfloat altPernas = 1;
GLfloat altTampo = 0.001;

static GLfloat verticesPernas[] = {
	//�������������������������������������� x=tam (Esquerda)
		-tam,  0,  tam,	// 0 
		-tam,  tam + altPernas,  tam,	// 1 
		-tam,  tam + altPernas, -tam,	// 2 
		-tam,  0, -tam,	// 3 
	//�������������������� Direita
		 tam,  0,  tam,	// 4 
		 tam,  tam + altPernas,  tam,	// 5 
		 tam,  tam + altPernas, -tam,	// 6 
		 tam,  0, -tam,	// 7 
	//��������������������� (Cima
		-tam,  tam + altPernas,  tam,	// 8 
		-tam,  tam + altPernas, -tam,	// 9 
		 tam,  tam + altPernas, -tam,	// 10 
		 tam,  tam + altPernas,  tam,	// 11 
};

static GLfloat normaisPernas[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… x=tam (Direita)
		  1.0,  0.0,  0.0,
		  1.0,  0.0,  0.0,
		  1.0,  0.0,  0.0,
		  1.0,  0.0,  0.0,
		  //…………………………………………………………………………………………………… y=tam (Cima)
		 0.0,  1.0,  0.0,
		 0.0,  1.0,  0.0,
		 0.0,  1.0,  0.0,
		 0.0,  1.0,  0.0,
};
//------------------------------------------------------------ Cores
static GLfloat corPernas[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda) - Red
	  1.0,  0.0, 0.0,	// 0 
	  1.0,  0.0, 0.0,	// 1 
	  1.0,  1.0, 0.0,	// 2 
	  1.0,  1.0, 0.0,	// 3 
	//…………………………………………………………………………………………………… x=2*tam (Direita) - Green
	  0.0,  1.0, 1.0,	// 4 
	  0.0,  1.0, 1.0,	// 5 
	  0.0,  1.0, 0.0,	// 6 
	  0.0,  1.0, 0.0,	// 7 
	//…………………………………………………………………………………………………… y=tam (Cima) - Blue
	  0.0,  0.0, 1.0,	// 8 
	  0.0,  0.0, 1.0,	// 9 
	  1.0,  0.0, 1.0,	// 10 
	  1.0,  0.0, 1.0,	// 11 
};



static GLfloat verticesTampo[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam + altTampo,  tam,	// 1 
		-tam,   tam + altTampo, -tam - distZ,	// 2 
		-tam,  -tam, -tam - distZ,	// 3 
	//…………………………………………………… Direita
		 tam + distX,  -tam,  tam,	// 4 
		 tam + distX,   tam + altTampo, tam,	// 5 
		 tam + distX,   tam + altTampo, -tam - distZ,	// 6 
		 tam + distX,  -tam, -tam - distZ,	// 7 
	//……………………………………………………… (Cima
		-tam,  tam + altTampo,  tam,	// 8 
		-tam,  tam + altTampo, -tam - distZ,	// 9 
		 tam + distX,  tam + altTampo, -tam - distZ,	// 10 
		 tam + distX,  tam + altTampo,  tam,	// 11 
};

static GLfloat normaisTampo[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… x=tam (Direita)
		  1.0,  0.0,  0.0,
		  1.0,  0.0,  0.0,
		  1.0,  0.0,  0.0,
		  1.0,  0.0,  0.0,
		  //…………………………………………………………………………………………………… y=tam (Cima)
		 0.0,  1.0,  0.0,
		 0.0,  1.0,  0.0,
		 0.0,  1.0,  0.0,
		 0.0,  1.0,  0.0,
};
//------------------------------------------------------------ Cores
static GLfloat corTampo[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda) - Red
	  1.0,  0.0, 0.0,	// 0 
	  1.0,  0.0, 0.0,	// 1 
	  1.0,  1.0, 0.0,	// 2 
	  1.0,  1.0, 0.0,	// 3 
	//…………………………………………………………………………………………………… x=2*tam (Direita) - Green
	  0.0,  1.0, 1.0,	// 4 
	  0.0,  1.0, 1.0,	// 5 
	  0.0,  1.0, 0.0,	// 6 
	  0.0,  1.0, 0.0,	// 7 
	//…………………………………………………………………………………………………… y=tam (Cima) - Blue
	  0.0,  0.0, 1.0,	// 8 
	  0.0,  0.0, 1.0,	// 9 
	  1.0,  0.0, 1.0,	// 10 
	  1.0,  0.0, 1.0,	// 11 
};

//=========================================================== FACES DA MESA
GLboolean frenteVisivel = 1;

static GLuint cimaPernas[] = { 8, 11, 10, 9 };   // regra da mao direita
static GLuint esqPernas[] = { 0, 1, 2, 3 };
static GLuint dirPernas[] = { 4, 7, 6, 5 };
static GLuint baixoPernas[] = { 0, 3, 7, 4 };
static GLuint frentePernas[] = { 1, 0, 4, 5 };
static GLuint trasPernas[] = { 3, 2, 6, 7 };

static GLuint cimaTampo[] = { 8, 11, 10, 9 };   // regra da mao direita
static GLuint esqTampo[] = { 0, 1, 2, 3 };
static GLuint dirTampo[] = { 4, 7, 6, 5 };
static GLuint baixoTampo[] = { 0, 3, 7, 4 };
static GLuint frenteTampo[] = { 1, 0, 4, 5 };
static GLuint trasTampo[] = { 3, 2, 6, 7 };

//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 15.0, yC = 15.0, zC = 15.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 5.0, aVisao = 0.5 * PI, incVisao = 0.25;
GLfloat  obsPini[] = { 1, 4.0, 0.5 * xC };
GLfloat  obsPfin[] = { obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao * sin(aVisao) };
GLfloat  translateZ[] = { 0, 0, 0 };
GLfloat  translateX[] = { 0, 0, 0 };
GLfloat  rotateTudo[] = { 0, 0, 1, 0 };
GLfloat  angPersp = 90;
GLfloat  incZoom = 3;
GLint   msec = 20;						//.. definicao do timer (actualizacao)
GLboolean  anim = false;
GLfloat angAnimEsq = 0;
GLfloat angAnimDir = 0;
GLint incrementDir = 2;
GLint incrementEsq = -2;
GLfloat incrementX = 0.02;
GLUquadricObj* bola = gluNewQuadric();		// Skybox

// -------------------------------------------------------------- Texturas
GLint transparencia = 0;

// -------------------------------------------------------------- Texturas
GLuint   texture[2];
RgbImage imag;

// -------------------------------------------------------------- Iluminacao - Ambiente
GLint   Dia = 1;     //:::   'D'  
GLfloat luzGlobalCorAmb[4] = { 1.0, 1.0, 1.0, 1.0 };   // 

// -------------------------------------------------------------- Iluminacao - Teto
GLint luzTeto = 1;	// 'T'
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLint luzR = 1;		// 'R'
GLint luzG = 1;		// 'G'
GLint luzB = 1;		// 'B'
GLfloat localPos[4] = { 0, 10.0, 0, 1.0 };				// no teto
GLfloat localCorAmb[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };

// -------------------------------------------------------------- Iluminacao - Foco
GLint   ligaFoco = 0;
GLfloat rFoco = 10, aFoco = aVisao;
GLfloat incH = 0.0, incV = 0.0;
GLfloat incMaxH = 0.5, incMaxV = 0.35;
GLfloat focoPini[] = { obsPini[0], obsPini[1], obsPini[2], 1.0 };
GLfloat focoPfin[] = { obsPini[0] - rFoco * cos(aFoco), obsPini[1], obsPini[2] - rFoco * sin(aFoco), 1.0 };
GLfloat focoDir[] = { -cos(aVisao), 0, -sin(aVisao) };
GLfloat focoExp = 1.0;
GLfloat focoCut = 20.0;	// Angulo

GLfloat focoCorDif[4] = { 0.9, 0.9, 0.9, 1.0 };
GLfloat focoCorEsp[4] = { 1.0, 1.0, 1.0, 1.0 };

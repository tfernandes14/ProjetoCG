#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "RgbImage.h"

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

static GLuint cimaPernas[] = {8, 11, 10, 9};   // regra da mao direita
static GLuint esqPernas[] = {0, 1, 2, 3};
static GLuint dirPernas[] = {4, 7, 6, 5};
static GLuint baixoPernas[] = {0, 3, 7, 4};
static GLuint frentePernas[] = {1, 0, 4, 5};
static GLuint trasPernas[] = {3, 2, 6, 7};

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
GLfloat  obsPfin[] = { obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao * sin(aVisao)};
GLfloat  translateZ[] = { 0, 0, 0 };
GLfloat  translateX[] = { 0, 0, 0 };
GLfloat  rotateTudo[] = {0, 0, 1, 0};
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

// -------------------------------------------------------------- Materiais
int material = 15;
GLfloat  esmeraldAmb[] = { 0.0215 ,0.1745 ,0.0215 };
GLfloat  esmeraldDif[] = { 0.07568 ,0.61424 ,0.07568 };
GLfloat  esmeraldSpec[] = { 0.633 ,0.727811 ,0.633 };
GLint    esmeraldCoef = 0.6 * 128;

GLfloat  jadeAmb[] = { 0.135 ,0.2225 ,0.1575 };
GLfloat  jadeDif[] = { 0.54 ,0.89 ,0.63 };
GLfloat  jadeSpec[] = { 0.316228 ,0.316228 ,0.316228 };
GLint   jadeCoef = 0.1 * 128;

GLfloat  obsidianAmb[] = { 0.05375 ,0.05 ,0.06625 };
GLfloat  obsidianDif[] = { 0.18275 ,0.17 ,0.22525 };
GLfloat  obsidianSpec[] = { 0.332741 ,0.328634 ,0.346435 };
GLint  obsidianCoef = 0.3 * 128;

GLfloat  pearlAmb[] = { 0.25 ,0.20725 ,0.20725 };
GLfloat  pearlDif[] = { 1.0 ,0.829 ,0.829 };
GLfloat  pearlSpec[] = { 0.296648 ,0.296648 ,0.296648 };
GLint  pearlCoef = 0.088 * 128;

GLfloat  rubyAmb[] = { 0.1745 ,0.01175 ,0.01175 };
GLfloat  rubyDif[] = { 0.61424 ,0.04136 ,0.04136 };
GLfloat  rubySpec[] = { 0.727811 ,0.626959 ,0.626959 };
GLint  rubyCoef = 0.6 * 128;

GLfloat  turquoiseAmb[] = { 0.1 ,0.18725 ,0.1745 };
GLfloat  turquoiseDif[] = { 0.396 ,0.74151 ,0.69102 };
GLfloat  turquoiseSpec[] = { 0.297254 ,0.30829 ,0.306678 };
GLint  turquoiseCoef = 0.1 * 128;

GLfloat  brassAmb[] = { 0.329412 ,0.223529 ,0.027451 };
GLfloat  brassDif[] = { 0.780392 ,0.568627 ,0.113725 };
GLfloat  brassSpec[] = { 0.992157 ,0.941176 ,0.807843 };
GLint  brassCoef = 0.21794872 * 128;

GLfloat  bronzeAmb[] = { 0.2125 ,0.1275 ,0.054 };
GLfloat  bronzeDif[] = { 0.714 ,0.4284 ,0.18144 };
GLfloat  bronzeSpec[] = { 0.393548 ,0.271906 ,0.166721 };
GLint  bronzeCoef = 0.2 * 128;

GLfloat  chromeAmb[] = { 0.25 ,0.25 ,0.25 };
GLfloat  chromeDif[] = { 0.4 ,0.4 ,0.4 };
GLfloat  chromeSpec[] = { 0.774597 ,0.774597 ,0.774597 };
GLint  chromeCoef = 0.6 * 128;

GLfloat  copperAmb[] = { 0.19125 ,0.0735 ,0.0225 };
GLfloat  copperDif[] = { 0.7038 ,0.27048 ,0.0828 };
GLfloat  copperSpec[] = { 0.256777 ,0.137622 ,0.086014 };
GLint  copperCoef = 0.1 * 128;

GLfloat  goldAmb[] = { 0.24725 ,0.1995 ,0.0745 };
GLfloat  goldDif[] = { 0.75164 ,0.60648 ,0.22648 };
GLfloat  goldSpec[] = { 0.628281 ,0.555802 ,0.366065 };
GLint  goldCoef = 0.4 * 128;

GLfloat  silverAmb[] = { 0.19225 ,0.19225 ,0.19225 };
GLfloat  silverDif[] = { 0.50754 ,0.50754 ,0.50754 };
GLfloat  silverSpec[] = { 0.508273 ,0.508273 ,0.508273 };
GLint  silverCoef = 0.4 * 128;

GLfloat blackPlasticAmb[] = { 0.0 ,0.0 ,0.0 };
GLfloat blackPlasticDif[] = { 0.01 ,0.01 ,0.01 };
GLfloat blackPlasticSpec[] = { 0.50 ,0.50 ,0.50 };
GLint blackPlasticCoef = 0.25 * 128;

GLfloat  cyanPlasticAmb[] = { 0.0 ,0.1 ,0.06 };
GLfloat  cyanPlasticDif[] = { 0.0 ,0.50980392 ,0.50980392 };
GLfloat  cyanPlasticSpec[] = { 0.50196078 ,0.50196078 ,0.50196078 };
GLint  cyanPlasticCoef = 0.25 * 128;

GLfloat greenPlasticAmb[] = { 0.0 ,0.0 ,0.0 };
GLfloat greenPlasticDif[] = { 0.1 ,0.35 ,0.1 };
GLfloat greenPlasticSpec[] = { 0.45 ,0.55 ,0.45 };
GLint greenPlasticCoef = 0.25 * 128;

GLfloat  redPlasticAmb[] = { 0.0 ,0.0 ,0.0 };
GLfloat  redPlasticDif[] = { 0.5 ,0.0 ,0.0 };
GLfloat  redPlasticSpec[] = { 0.7 ,0.6 ,0.6 };
GLint  redPlasticCoef = 0.25 * 128;

GLfloat whitePlasticAmb[] = { 0.8 ,0.8 ,0.8 };
GLfloat whitePlasticDif[] = { 0.55 ,0.55 ,0.55, 0.35};
GLfloat whitePlasticSpec[] = { 0.870 ,0.870 ,0.870 };
GLint whitePlasticCoef = 0.25 * 128;

GLfloat yellowPlasticAmb[] = { 0.0 ,0.0 ,0.0 };
GLfloat yellowPlasticDif[] = { 0.5 ,0.5 ,0.0 };
GLfloat yellowPlasticSpec[] = { 0.60 ,0.60 ,0.50 };
GLint yellowPlasticCoef = 0.25 * 128;

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



//================================================================================
//=========================================================================== INIT
void initTexturas()
{
	//----------------------------------------- Chao
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("madeira.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("bola.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}

void initMaterials(int material) {

	switch (material) {
	case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, brassCoef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
		break;
	case 22: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowPlasticCoef);
		break;
	}
}

void initLights(void) {
	//…………………………………………………………………………………………………………………………………………… Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);

	//…………………………………………………………………………………………………………………………………………… Foco
	glLightfv(GL_LIGHT1, GL_POSITION, focoPini);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, focoDir);
	//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, focoExp);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, focoCut);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, localCorEsp);
	glLightfv(GL_LIGHT1, GL_AMBIENT, localCorAmb);
}

void inicializa(void){
	glClearColor(0, 0, 0, 1);		//………………………………………………………………………………Apagar
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glEnable(GL_NORMALIZE);	//………………………………………………………………………………Profundidade

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	initTexturas();
	initLights();

	/*glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente*/
}



void drawEixos()
{
	initMaterials(16);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 10);
	glEnd();

}

void desenhaPerna(int i) {
	initMaterials(material);
	GLfloat aux;
	GLfloat translatePernas[] = { 0, 0, 0 };
	GLfloat translateAnim[] = {0, 0, 0};
	if (i == 0) {
		// Perna da origem
		translatePernas[0] = 0;
		translatePernas[1] = 0;
		translatePernas[2] = 0;
		translateAnim[0] = 0;
		translateAnim[1] = -altPernas;
		translateAnim[2] = 0;
		aux = angAnimEsq;
	}
	if (i == 1) {
		// Perna do canto superior direito
		translatePernas[0] = distX;
		translatePernas[1] = 0;
		translatePernas[2] = 0;
		translateAnim[0] = -tam - distX;
		translateAnim[1] = -altPernas;
		translateAnim[2] = 0;
		aux = angAnimDir;
	}
	else if (i == 2) {
		// Perna do canto inferior esquerdo
		translatePernas[0] = 0;
		translatePernas[1] = 0;
		translatePernas[2] = distZ;
		translateAnim[0] = 0;
		translateAnim[1] = -altPernas;
		translateAnim[2] = 0;
		aux = angAnimEsq;
	}
	else if (i == 3) {
		// Perna do canto inferior direito
		translatePernas[0] = distX;
		translatePernas[1] = 0;
		translatePernas[2] = distZ;
		translateAnim[0] = -tam - distX;
		translateAnim[1] = -altPernas;
		translateAnim[2] = 0;
		aux = angAnimDir;
	}

	if (anim) {
		translateX[0] += incrementX;
		if (translateX[0] > 10) {
			incrementX = -incrementX;
		}
		if (translateX[0] < -10) {
			incrementX = -incrementX;
		}

		angAnimEsq += incrementEsq;
		if (angAnimEsq <= -90) {
			incrementEsq = -incrementEsq;
		}
		if (angAnimEsq >= 0) {
			incrementEsq = -incrementEsq;
		}

		angAnimDir += incrementDir;
		if (angAnimDir < 90) {
			incrementDir = -incrementDir;
		}
		if (angAnimDir > 0) {
			incrementDir = -incrementDir;
		}
	}

	//==================================== MESA	
	//glColorPointer(3, GL_FLOAT, 0, cor);	 podia ser modificada a cor !
	glPushMatrix();
		// Face de cima
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
			glTranslatef(-translateAnim[0], -translateAnim[1], translateAnim[2]);
			glRotatef(aux, 0, 0, 1);
			glTranslatef(translateAnim[0], translateAnim[1], translateAnim[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaPernas);   // desenhar uma das faces da mesa
	glPopMatrix();

	glPushMatrix();
		// Face de baixo
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
			glTranslatef(-translateAnim[0], -translateAnim[1], translateAnim[2]);
			glRotatef(aux, 0, 0, 1);
			glTranslatef(translateAnim[0], translateAnim[1], translateAnim[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoPernas);
	glPopMatrix();

	glPushMatrix();
		// Face da frente
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
			glTranslatef(-translateAnim[0], -translateAnim[1], translateAnim[2]);
			glRotatef(aux, 0, 0, 1);
			glTranslatef(translateAnim[0], translateAnim[1], translateAnim[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frentePernas);
	glPopMatrix();

	glPushMatrix();
		// Face de tras
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
			glTranslatef(-translateAnim[0], -translateAnim[1], translateAnim[2]);
			glRotatef(aux, 0, 0, 1);
			glTranslatef(translateAnim[0], translateAnim[1], translateAnim[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasPernas);
	glPopMatrix();

	glPushMatrix();
		// Face da esquerda
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
			glTranslatef(-translateAnim[0], -translateAnim[1], translateAnim[2]);
			glRotatef(aux, 0, 0, 1);
			glTranslatef(translateAnim[0], translateAnim[1], translateAnim[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esqPernas);
	glPopMatrix();

	glPushMatrix();
		// Face da direita
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
			glTranslatef(-translateAnim[0], -translateAnim[1], translateAnim[2]);
			glRotatef(aux, 0, 0, 1);
			glTranslatef(translateAnim[0], translateAnim[1], translateAnim[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dirPernas);
	glPopMatrix();
}

void desenhaTampo() {
	initMaterials(material);
	GLfloat  translatePernas[] = { 0, altPernas + 0.5, distZ };

	if (anim) {
		translateX[0] += incrementX;
		if (translateX[0] > 10) {
			incrementX = -incrementX;
		}
		if (translateX[0] < -10) {
			incrementX = -incrementX;
		}
	}

	//==================================== Tampo
	//glColorPointer(3, GL_FLOAT, 0, cor);	 podia ser modificada a cor !
	glPushMatrix();
		// Face de cima
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cimaTampo);   // desenhar uma das faces da mesa
	glPopMatrix();

	glPushMatrix();
		// Face de baixo
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixoTampo);
	glPopMatrix();

	glPushMatrix();
		// Face da frente
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frenteTampo);
	glPopMatrix();

	glPushMatrix();
		// Face de tras
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, trasTampo);
	glPopMatrix();

	glPushMatrix();
		// Face da esquerda
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);

		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esqTampo);
	glPopMatrix();

	glPushMatrix();
		// Face da direita
		glRotatef(rotateTudo[0], rotateTudo[1], rotateTudo[2], rotateTudo[3]);
		glTranslatef(translateZ[0], translateZ[1], translateZ[2]);
		
		if (anim) {
			glTranslatef(translateX[0], translateX[1], translateX[2]);
		}

		glTranslatef(translatePernas[0], translatePernas[1], translatePernas[2]);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, dirTampo);
	glPopMatrix();
}

void drawMesa() {
	initMaterials(material);
	//=================================================== Qual o lado visivel ???
	if (frenteVisivel)
		glCullFace(GL_BACK);  //.. o de tras é eliminado
	else
		glCullFace(GL_FRONT);  //.. o de frente é eliminado

	glVertexPointer(3, GL_FLOAT, 0, verticesPernas); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normaisPernas);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, corPernas);
	glEnableClientState(GL_COLOR_ARRAY);

	glPushMatrix();
		for (int i = 0; i < 4; i++) {
			desenhaPerna(i);
		}
	glPopMatrix();

	glVertexPointer(3, GL_FLOAT, 0, verticesTampo); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normaisTampo);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, corTampo);
	glEnableClientState(GL_COLOR_ARRAY);

	glPushMatrix();
		desenhaTampo();
	glPopMatrix();
}

void drawChao() {
	int inc = 0.1;
	int inicio_menor_x = -xC, inicio_menor_y = -xC;
	initMaterials(22);
	//if (transparencia) {
		glEnable(GL_BLEND);	//………………………………………………………………………………Transparencia
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glNormal3f(0, 1, 0);
		glPushMatrix();
			glTranslatef(4, 0, 0);
			for (int i = 0; i < xC / inc; i++) {
				for (int j = 0; j < xC / inc; j++) {
					glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(inicio_menor_x, 0, inicio_menor_y);
					glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(inicio_menor_x, 0, inicio_menor_y + inc);
					glTexCoord2f(1.0f, 1.0f);    glVertex3i(inicio_menor_x + inc, 0, inicio_menor_y + inc);
					glTexCoord2f(0.0f, 1.0f);    glVertex3i(inicio_menor_x + inc, 0, inicio_menor_y);
					glEnd();
					inicio_menor_y += inc;
				}
				inicio_menor_y = -xC;
				inicio_menor_x += inc;
			}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
	/*}
	else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glNormal3f(0, 1, 0);
		glPushMatrix();
			glTranslatef(4, 0, 0);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f);  	 glVertex3i(-xC, 0, -xC);
				glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(-xC, 0, xC);
				glTexCoord2f(1.0f, 1.0f);    glVertex3i(xC, 0, xC);
				glTexCoord2f(0.0f, 1.0f);    glVertex3i(xC, 0, -xC);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}*/
}

void drawParedes() {
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	initMaterials(16);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (int i = 0; i < 4; i++){
		if (i == 0) {
			glPushMatrix();
				glTranslatef(4, xC, -xC);
				glRotatef(90, 1, 0, 0);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  		glVertex3i(-xC, 0, -xC);
					glTexCoord2f(1.0, 0.0); 		glVertex3i(-xC, 0, xC);
					glTexCoord2f(1.0, 1.0);			glVertex3i(xC, 0, xC);
					glTexCoord2f(0.0, 1.0);			glVertex3i(xC, 0, -xC);
				glEnd();
			glPopMatrix();
		}
		if (i == 1) {
			glPushMatrix();
				glTranslatef(4, xC, xC);
				glRotatef(-90, 1, 0, 0);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  		glVertex3i(-xC, 0, -xC);
					glTexCoord2f(1.0, 0.0); 		glVertex3i(-xC, 0, xC);
					glTexCoord2f(1.0, 1.0);			glVertex3i(xC, 0, xC);
					glTexCoord2f(0.0, 1.0);			glVertex3i(xC, 0, -xC);
				glEnd();
			glPopMatrix();
		}
		if (i == 2) {
			glPushMatrix();
				glTranslatef(4-xC, xC, 0);
				glRotatef(-90, 0, 0, 1);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  		glVertex3i(-xC, 0, -xC);
					glTexCoord2f(1.0, 0.0); 		glVertex3i(-xC, 0, xC);
					glTexCoord2f(1.0, 1.0);			glVertex3i(xC, 0, xC);
					glTexCoord2f(0.0, 1.0);			glVertex3i(xC, 0, -xC);
				glEnd();
			glPopMatrix();
		}
		if (i == 3) {
			glPushMatrix();
				glTranslatef(4+xC, xC, 0);
				glRotatef(90, 0, 0, 1);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0f, 0.0f);  		glVertex3i(-xC, 0, -xC);
					glTexCoord2f(1.0, 0.0); 		glVertex3i(-xC, 0, xC);
					glTexCoord2f(1.0, 1.0);			glVertex3i(xC, 0, xC);
					glTexCoord2f(0.0, 1.0);			glVertex3i(xC, 0, -xC);
				glEnd();
			glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);
}

void drawSkyBox(){
	initMaterials(22);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	//------------------------- Skybox
	glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glPushMatrix();
			glTranslatef(2, 4, 2);
			gluQuadricDrawStyle(bola, GLU_FILL);
			gluQuadricNormals(bola, GLU_SMOOTH);
			gluQuadricTexture(bola, GL_TRUE);
			gluSphere(bola, 30.0, 150, 150);
		glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void iluminacao() {
	if (luzTeto)		glEnable(GL_LIGHT0);
	else				glDisable(GL_LIGHT0);

	if (ligaFoco)		glEnable(GL_LIGHT1);
	else				glDisable(GL_LIGHT1);
}

void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angPersp, (float) wScreen / hScreen, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!
	   

	//…………………………………………………………………………………………………………………………………………………………Objectos
	//drawEixos();
	iluminacao();
	//drawParedes();
	drawSkyBox();
	drawChao();
	drawMesa();
	
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

void updateVisao() {
	obsPfin[0] = obsPini[0] + rVisao * cos(aVisao);
	obsPfin[2] = obsPini[2] - rVisao * sin(aVisao);

	/*focoPini[0] = obsPini[0];
	focoPini[2] = obsPini[2];
	focoPfin[0] = focoPini[0] - rFoco * cos(aFoco + incH);
	focoPfin[2] = focoPini[2] - rFoco * sin(aFoco + incH);
	focoPini[1] = obsPini[1];
	focoPini[2] = obsPini[2];
	focoDir[0] = focoPfin[0] - focoPini[0];
	focoDir[1] = incV;
	focoDir[2] = focoPfin[2] - focoPini[2];*/

	glutPostRedisplay();
}

void updateLuz() {
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	// --------------------------------------------- Visibilidade
	case 'v':
	case 'V':
		frenteVisivel = !frenteVisivel;
		glutPostRedisplay();
		break;

	// --------------------------------------------- Observador
	case 'q': 
	case 'Q':
		obsPini[1] = obsPini[1] + 1;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		obsPini[1] = obsPini[1] - 1;
		glutPostRedisplay();
		break;
	case 's': case 'S':
		angPersp = angPersp + 3;
		if (angPersp > 170) angPersp = 170;
		glutPostRedisplay();
		break;
	case 'w': case 'W':
		angPersp = angPersp - 3;
		if (angPersp < 1) angPersp = 1;
		glutPostRedisplay();
		break;

		// --------------------------------------------- Mesa
	case 'z':
	case 'Z':
		translateZ[2] = (translateZ[2] - 1);
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		translateZ[2] = (translateZ[2] + 1);
		glutPostRedisplay();
		break;
	case 'o':
	case 'O':
		rotateTudo[0] = (rotateTudo[0] - 30);
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		rotateTudo[0] = (rotateTudo[0] + 30);
		glutPostRedisplay();
		break;

	// --------------------------------------------- Animacao
	case 'e':
	case 'E':
		anim = !anim;
		glutPostRedisplay();
		break;

	// --------------------------------------------- Material mesa
	case 'm':
	case 'M':
		material = (material + 1) % 17;
		initMaterials(material);
		glutPostRedisplay();
		break;

	// --------------------------------------------- Transparencia
	case 'k':
	case 'K':
		transparencia = !transparencia;
		glutPostRedisplay();
		break;

	// --------------------------------------------- Luz Ambiente
	case 'd':
	case 'D':
		Dia = !Dia;
		
		if (Dia) { luzGlobalCorAmb[0] = 1;   luzGlobalCorAmb[1] = 1;   luzGlobalCorAmb[2] = 1; cout << "Dia: On\n"; }
		else { luzGlobalCorAmb[0] = 0;   luzGlobalCorAmb[1] = 0;   luzGlobalCorAmb[2] = 0;  cout << "Dia: Off\n";}
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

	// --------------------------------------------- Luz Teto
	// Liga e desliga
	case 't':
	case 'T':
		luzTeto = !luzTeto;
		if (luzTeto)	cout << "Teto: On\n";
		else            cout << "Teto: Off\n";
		updateLuz();
		glutPostRedisplay();
		break;
	// Aumenta a intensidade
	case 'i':
	case 'I':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	// Cores da luz do teto
	case 'r':case 'R':
		luzR = (luzR + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':case 'G':
		luzG = (luzG + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':case 'B':
		luzB = (luzB + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;

	// --------------------------------------------- Luz Foco
	case 'f':
	case 'F':
		ligaFoco = !ligaFoco;
		if (ligaFoco)	cout << "Foco: On\n";
		else            cout << "Foco: Off\n";
		updateLuz();
		glutPostRedisplay();
		break;

	// --------------------------------------------- Sair
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		obsPini[0] = obsPini[0] + incVisao * cos(aVisao);
		obsPini[2] = obsPini[2] - incVisao * sin(aVisao);
	}
	if (key == GLUT_KEY_DOWN) {
		obsPini[0] = obsPini[0] - incVisao * cos(aVisao);
		obsPini[2] = obsPini[2] + incVisao * sin(aVisao);
	}
	if (key == GLUT_KEY_LEFT)   aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT) 	aVisao = (aVisao - 0.1);
	updateVisao();
}


void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("SETAS/Q/A/W/S: Observador | E: Animacao | Z/XO/P: Mesa | F: Frente vis | D: Luz ambiente | T/I/R/G/B: Luz teto");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}

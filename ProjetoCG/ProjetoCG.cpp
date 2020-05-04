#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>

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
GLfloat altTampo = 0.1;

static GLfloat verticesPernas[] = {
	//�������������������������������������� x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam + altPernas,  tam,	// 1 
		-tam,   tam + altPernas, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//�������������������� Direita
		 tam,  -tam,  tam,	// 4 
		 tam,   tam + altPernas,  tam,	// 5 
		 tam,   tam + altPernas, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
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
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat  translateZ[] = { 0, 0, 0 };
GLfloat  translateX[] = { 0, 0, 0 };
GLfloat  rotateTudo[] = {0, 0, 1, 0};
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;
GLint   msec = 20;						//.. definicao do timer (actualizacao)
GLboolean  anim = false;
GLfloat angAnimEsq = 0;
GLfloat angAnimDir = 0;
GLint incrementDir = 2;
GLint incrementEsq = -2;
GLfloat incrementX = 0.02;

//================================================================================
//=========================================================================== INIT
void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	

	glEnable(GL_CULL_FACE);		//………………………………………………………………………………Faces visiveis
	glCullFace(GL_BACK);		//………………………………………………………………………………Mostrar so as da frente
}



void drawEixos()
{
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


void drawScene() {

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

	//==================================== Chaleira Amarela
	glColor4f(YELLOW);
	glPushMatrix();
		//?? escala, rotacao, translacao ??
		//glutWireTeapot(1);
	glPopMatrix();

}

void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float) wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!
	   

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawScene();
	
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'f':
	case 'F':
		frenteVisivel = !frenteVisivel;
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		translateZ[2] = (translateZ[2] - 1);
		glutPostRedisplay();
		break;

	case 'S':
	case 's':
		translateZ[2] = (translateZ[2] + 1);
		glutPostRedisplay();
		break;

	case 'e':
	case 'E':
		rotateTudo[0] = (rotateTudo[0] - 30);
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		rotateTudo[0] = (rotateTudo[0] + 30);
		glutPostRedisplay();
		break;

	case 'r':
	case 'R':
		if (!anim) {
			anim = true;
		}
		else {
			anim = false;
		}
		glutPostRedisplay();
		break;

		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar à volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)   obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN) obsP[1] = (obsP[1] - 0.1);
	if (key == GLUT_KEY_LEFT)  aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT) aVisao = (aVisao - 0.1);
	
	if (obsP[1] >  yC)   obsP[1] = yC;   // limita altura
	if (obsP[1] < -yC)  obsP[1] = -yC;

	obsP[0] = rVisao * cos(aVisao);      // actualiza posicao (X,Z)
	obsP[2] = rVisao * sin(aVisao);
	
	glutPostRedisplay();
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
	glutCreateWindow("{jh,ep}@dei.uc.pt | Mover/rodar Cima: 'r' | FaceVisivel: 'f' | Observador: 'SETAS' | Andar: 'a/s' | Rodar: 'e/d'| Animacao: 'r'");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}

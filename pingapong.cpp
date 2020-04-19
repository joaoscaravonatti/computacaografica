#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 400
#define janela_largura 600
#define PI 3.14159265359
#define raquete_altura 100
#define raquete_largura 20
#define raio 10


typedef struct sObject {
	float x;
	float y;
} Object;

Object player1, player2, ball, step;


void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void specialKeys(int tecla, int x, int y);
void animate(int value);
void startGame();

int main(int argc, char** argv) {
	player1.x = -janela_largura / 2;
	startGame();

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela_largura, janela_altura);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("pinga pong");
	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutSpecialFunc(&specialKeys);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(50, animate, 1);
	glutMainLoop();

	return 0;
}

void startGame() {
	player1.x = -janela_largura / 2;
	player1.y = raquete_altura / 2;

	player2.x = janela_largura / 2 - raquete_largura;
	player2.y = raquete_altura / 2;

	ball.x = 0;
	ball.y = 0;

	step.x = 10;
	step.y = 10;
}


void animate(int value) {
	if (ball.x > (janela_largura / 2) - 2 *raio || ball.x < -((janela_largura / 2) - 2 * raio)) {
		startGame();
	}

	if (ball.y > janela_altura - 2 * raio || ball.y < -((janela_altura / 2 - 2 * raio))) {
		step.y = -step.y;
	}

	if (ball.y >= player2.y && ball.y <= player2.y + raquete_altura && ball.x == player2.x) {
		step.x = -step.x;
	}

	if (ball.y >= player1.y && ball.y <= player1.y + raquete_altura && ball.x == player1.x + raquete_largura) {
		step.x = -step.x;
	}

	ball.x += step.x;
	ball.y += step.y;

	glutPostRedisplay();
	glutTimerFunc(50, animate, 1);
}

void keyboard(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'w':
		if (player1.y < (float) (janela_altura / 2) + raquete_altura) {
			player1.y += 10.0;
		}
		break;
	case 's':
		if (player1.y > -(float) janela_altura / 2) {
			player1.y -= 10.0;
		}
		break;
	}
	glutPostRedisplay();
}

void specialKeys(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_UP:
		if (player2.y < (float)(janela_altura / 2) + raquete_altura) {
			player2.y += 10.0;
		}
		break;
	case GLUT_KEY_DOWN:
		if (player2.y > -(float)janela_altura / 2) {
			player2.y -= 10.0;
		}
		break;
	}

	glutPostRedisplay();
}

void desenhar() {
	glPushMatrix();
	glTranslatef(player1.x, player1.y, 0);

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0, 0);
	glVertex2f(0, raquete_altura);
	glVertex2f(raquete_largura, raquete_altura);
	glVertex2f(raquete_largura, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(player2.x, player2.y, 0);

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(0, 0);
	glVertex2f(0, raquete_altura);
	glVertex2f(raquete_largura, raquete_altura);
	glVertex2f(raquete_largura, 0);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(ball.x, ball.y, 0);

	GLfloat circ_pnt = 30;
	GLfloat ang;


	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raio, sin(ang) * raio);
	}
	glEnd();

	glPopMatrix();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush();
}

void tela(GLsizei, GLsizei) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, janela_largura, 0, janela_largura);

	glMatrixMode(GL_MODELVIEW);
}


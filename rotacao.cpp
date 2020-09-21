#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define janela_altura 400
#define janela_largura 600

float rotacao = 1;
float zoom = 1;
float trans = 1;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela_largura, janela_altura);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("rotacao");

	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutMainLoop();

	return 0;
}

void keyboard(unsigned char tecla, int x, int y) {
	printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda, 2 para direita: ");
	printf("\no mouse estava em %d x %d\n", x, y);

	if (tecla == '1') {
		rotacao += 2;
		printf("\no valor de rotacao e %.2f\n", rotacao);
	}

	if (tecla == '2') {
		rotacao -= 2;
		printf("\no valor de rotacao e %.2f\n", rotacao);
	}

	if (tecla == '3') {
		zoom += 1;
		printf("\no valor do zoom e %.2f\n", zoom);
	}

	if (tecla == '4') {
		trans += 2;
		printf("\no valor do trans e %.2f\n", zoom);
	}


	if (tecla == '5') {
		trans -= 2;
		printf("\no valor do trans e %.2f\n", zoom);
	}

	glutPostRedisplay();
}

void desenhar() {
	glRotated(rotacao, 0, 0, 1);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-100, -100);
	glVertex2f(0, 0);
	glVertex2f(100, -100);
	glEnd();

	glRotated(-rotacao, 0, 0, 1);

	glScalef(zoom, zoom, 0);
	glTranslatef(trans, 0, 0);

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(-30, 30);
	glVertex2f(-10, 30);
	glVertex2f(-10, 50);
	glVertex2f(-30, 50);
	glEnd();

	glScalef(1, 1, 0);
	glTranslatef(1, 1, 0);
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define janela_altura 400
#define janela_largura 600

float zoom[] = { 1.0, 1.0, 1.0 };
float transX[] = { 1.0, 1.0, 1.0 };
float transY[] = { 1.0, 1.0, 1.0 };
int opcao;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void specialKeys(int tecla, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(janela_largura, janela_altura);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("rotacao");

	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutSpecialFunc(&specialKeys);
	glutKeyboardFunc(&keyboard);
	glutMainLoop();

	return 0;
}

void keyboard(unsigned char tecla, int x, int y) {
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);

	switch (tecla) {
	case '1':
		opcao = 0;
		break;
	case '2':
		opcao = 1;
		break;
	case '3':
		opcao = 2;
		break;
	default:
		opcao = 0;
		break;
	}

	printf("\nOpcao: %d", opcao);

	glutPostRedisplay();
}

void specialKeys(int tecla, int x, int y) {
	switch (tecla) {
	case GLUT_KEY_UP:
		transY[opcao] += 5.0;
		break;
	case GLUT_KEY_DOWN:
		transY[opcao] -= 5.0;
		break;
	case GLUT_KEY_LEFT:
		transX[opcao] -= 5.0;
		break;
	case GLUT_KEY_RIGHT:
		transX[opcao] += 5.0;
		break;
	case GLUT_KEY_PAGE_UP:
		zoom[opcao] += 0.05;
		break;
	case GLUT_KEY_PAGE_DOWN:
		zoom[opcao] -= 0.05;
		break;
	}

	printf("\nX: %f, Y: %f", transX[opcao], transY[opcao]);
	glutPostRedisplay();
}

void desenhar() {

	glTranslatef(transX[0], transY[0], 0);
	glScalef(zoom[0], zoom[0], 0);

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(-200, -100);
	glVertex2f(-200, 200);
	glVertex2f(-150, 200);
	glVertex2f(-150, -100);
	glEnd();

	//glScalef(-zoom[0], -zoom[0], 0);
	glTranslatef(-transX[0], -transY[0], 0);

	glTranslatef(transX[1], transY[1], 0);

	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(-100, -100);
	glVertex2f(-100, 0);
	glVertex2f(0, 0);
	glVertex2f(0, -100);
	glEnd();

	glTranslatef(-transX[1], -transY[1], 0);

	glTranslatef(transX[2], transY[2], 0);

	glBegin(GL_TRIANGLES);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2f(50, -100);
	glVertex2f(100, 0);
	glVertex2f(150, -100);
	glEnd();

	glTranslatef(-transX[2], -transY[2], 0);

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

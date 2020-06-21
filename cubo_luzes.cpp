#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 480
#define janela_largura 640
int on = 1;
float x = 0.0, y = 0.0, z = 0.0;

float mat_ambient[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
float mat_diffuse[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
float mat_specular[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
float shine[] = { 89.6f };

void reshape(GLsizei largura, GLsizei altura);
void display();
void keyboard(unsigned char key, int a, int b);
void conf_luz();
void switch_shapes_color();

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Ligar GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer
    glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
    glutInitWindowPosition(50, 50); // Pos. onde surge a janela
    glutCreateWindow("iluminacao"); // Criar Janela
    conf_luz(); // configuração de luz
    glutDisplayFunc(display); // imagem
    glutReshapeFunc(reshape); // config telas
    glutKeyboardFunc(keyboard); // funcoes de teclado
    glutMainLoop(); // loop
    return 0;
}
void conf_luz(void)
{
    float ambiente[] = { 0.0, 0.0, 0.0, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float posicao[] = { 1.5, 0.0 };
    float lmodel_ambiente[] = { 0.4, 0.4, 0.4, 1.0 };
    float local_view[] = { 0.0 };
    glClearColor(0.0, 0.1, 0.1, 0.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, posicao);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(GLsizei largura, GLsizei altura)
{

    if (altura == 0) altura = 1; // previne a divisão por zero
    GLfloat aspecto = (GLfloat)largura / (GLfloat)altura;


    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION); // manipulando matriz de projeção
    glLoadIdentity(); // zerando a matriz
    gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // configura fundo sem transparencia
    glEnable(GL_DEPTH_TEST); // alunos devem testar
    glShadeModel(GL_SMOOTH); // acabamento com suavização
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}
void display()
{
    float padrao[] = { 0.0, 0.0, 0.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpeza
    glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos

    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.5f, 0.0f, -6.0f); // posiciona a piramide

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glMaterialfv(GL_FRONT, GL_EMISSION, padrao);
    glutSolidSphere(1.0, 60, 60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, 0.0f, -6.0f); // posiciona a piramide
    glRotatef(15.0f, 1.0f, 0.0f, 0.0f);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shine);
    glMaterialfv(GL_FRONT, GL_EMISSION, padrao);
    glutSolidCube(1.5f);
    glPopMatrix();
    glutSwapBuffers(); // trocar a matriz da tela por esta aqui.
}
void keyboard(unsigned char key, int a, int b)
{
    if (key == 'c') {
        switch_shapes_color();
        glutPostRedisplay();
    }
            
}

void switch_shapes_color() {
    float mat_ambient_silver[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
    float mat_diffuse_silver[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
    float mat_specular_silver[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
    float shine_silver[] = { 89.6f };

    float mat_ambient_copper[] = { 0.2295f, 0.08825f, 0.0275f, 1.0f };
    float mat_diffuse_copper[] = { 0.5508f, 0.2118f, 0.066f, 1.0f };
    float mat_specular_copper[] = { 0.580594f, 0.223257f, 0.0695701f, 1.0f };
    float shine_copper[] = { 51.2f };

    if(on) {
        for (int i = 0; i < 4; i++) {
            mat_ambient[i] = mat_ambient_copper[i];
            mat_diffuse[i] = mat_diffuse_copper[i];
            mat_specular[i] = mat_specular_copper[i];
        }

        shine[0] = shine_copper[0];

        on = 0;
    } else {
        for (int i = 0; i < 4; i++) {
            mat_ambient[i] = mat_ambient_silver[i];
            mat_diffuse[i] = mat_diffuse_silver[i];
            mat_specular[i] = mat_specular_silver[i];
        }

        shine[0] = shine_silver[0];
        on = 1;
    }
}
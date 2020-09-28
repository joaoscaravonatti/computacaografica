#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define janela_largura 500
#define janela_altura 500

typedef struct sObject {
    float x;
    float y;
    int offsetX;
    int offsetY;
    int visible = 1;
} Object;

Object airplanePosition;
Object screenPosition;
Object panelPosition;
Object pointerPosition;
Object shotPosition;
Object heart1Position;
Object heart2Position;
Object heart3Position;
int start = 0;
int life = 3;

void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);
void arrow_keys(int tecla, int x, int y);
void animate(int value);
void startGame(Object airplanePosition);
void playGame();

Object fuels[8];
Object helicopters[6];
Object ships[8];
Object houses[3];
Object grasses[10];
Object bridges[2];

int main(int argc, char** argv) {
    playGame();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(janela_largura, janela_altura);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("River raid");
    glutKeyboardFunc(&keyboard);
    glutSpecialFunc(arrow_keys);
    glutReshapeFunc(&resize);
    glutDisplayFunc(display);
    glutTimerFunc(50, animate, 1);
    glutMainLoop();

    return EXIT_SUCCESS;
}

void playGame() {
    screenPosition.x = 750;
    screenPosition.y = janela_altura / 2;
}

void startGame(Object object) {
    if (object.y > 1500) {
        screenPosition.y = -1400;
        airplanePosition.y = 1600;
        pointerPosition.y = 1650;
        panelPosition.y = 1650;
        heart1Position.y = 1650;
        heart2Position.y = 1650;
        heart3Position.y = 1650;
    }
    else {
        screenPosition.y = janela_altura / 2;
        airplanePosition.y = -120;
        pointerPosition.y = 0;
        panelPosition.y = 0;
        heart1Position.y = 0;
        heart2Position.y = 0;
        heart3Position.y = 0;
    }

    heart1Position.x = 0;
    heart2Position.x = 20;
    heart3Position.x = 40;

    screenPosition.x = janela_largura / 2;

    airplanePosition.x = 0;
    airplanePosition.offsetX = 15;
    airplanePosition.offsetY = 25;
    panelPosition.x = 0;
    pointerPosition.x = 150;
    shotPosition.visible = 0;

    bridges[0].x = 0;
    bridges[0].y = 1500;
    bridges[0].offsetX = 250;
    bridges[0].offsetY = 30;

    bridges[1].x = 0;
    bridges[1].y = 3000;
    bridges[1].offsetX = 250;
    bridges[1].offsetY = 30;

    for (int i = 0; i < 2; i++) {
        bridges[i].visible = 1;
    }

    //////////////////////////////
    grasses[0].x = 0;
    grasses[0].y = 150;
    grasses[0].offsetX = 40;
    grasses[0].offsetY = 60;

    grasses[1].x = 70;
    grasses[1].y = 800;
    grasses[1].offsetX = 10;
    grasses[1].offsetY = 30;

    grasses[2].x = 0;
    grasses[2].y = 1100;
    grasses[2].offsetX = 30;
    grasses[2].offsetY = 30;

    grasses[3].x = -150;
    grasses[3].y = 325;
    grasses[3].offsetX = 30;
    grasses[3].offsetY = 70;

    grasses[4].x = 0;
    grasses[4].y = 600;
    grasses[4].offsetX = 100;
    grasses[4].offsetY = 100;

    grasses[5].x = 0;
    grasses[5].y = 1850;
    grasses[5].offsetX = 100;
    grasses[5].offsetY = 50;

    grasses[6].x = -120;
    grasses[6].y = 2150;
    grasses[6].offsetX = 50;
    grasses[6].offsetY = 100;

    grasses[7].x = 120;
    grasses[7].y = 2150;
    grasses[7].offsetX = 50;
    grasses[7].offsetY = 100;

    grasses[8].x = -200;
    grasses[8].y = 2750;
    grasses[8].offsetX = 200;
    grasses[8].offsetY = 50;

    grasses[9].x = 200;
    grasses[9].y = 2750;
    grasses[9].offsetX = 80;
    grasses[9].offsetY = 50;

    //////////////////////////
    fuels[0].x = -70;
    fuels[0].y = 50;
    fuels[0].offsetX = 12;
    fuels[0].offsetY = 22;

    fuels[1].x = 0;
    fuels[1].y = 600;
    fuels[1].offsetX = 12;
    fuels[1].offsetY = 22;

    fuels[2].x = 170;
    fuels[2].y = 600;
    fuels[2].offsetX = 12;
    fuels[2].offsetY = 22;

    fuels[3].x = -100;
    fuels[3].y = 800;
    fuels[3].offsetX = 12;
    fuels[3].offsetY = 22;

    fuels[4].x = 50;
    fuels[4].y = 1150;
    fuels[4].offsetX = 12;
    fuels[4].offsetY = 22;

    fuels[5].x = 120;
    fuels[5].y = 1850;
    fuels[5].offsetX = 12;
    fuels[5].offsetY = 22;

    fuels[6].x = 0;
    fuels[6].y = 2300;
    fuels[6].offsetX = 12;
    fuels[6].offsetY = 22;

    fuels[7].x = -120;
    fuels[7].y = 2600;
    fuels[7].offsetX = 12;
    fuels[7].offsetY = 22;

    for (int i = 0; i < 8; i++) {
        fuels[i].visible = 1;
    }

    ////////////////////////
    helicopters[0].x = 70;
    helicopters[0].y = 100;
    helicopters[0].offsetX = 25;
    helicopters[0].offsetY = 15;

    helicopters[1].x = -50;
    helicopters[1].y = 450;
    helicopters[1].offsetX = 25;
    helicopters[1].offsetY = 15;

    helicopters[2].x = 0;
    helicopters[2].y = 1000;
    helicopters[2].offsetX = 25;
    helicopters[2].offsetY = 15;

    helicopters[3].x = -100;
    helicopters[3].y = 1200;
    helicopters[3].offsetX = 25;
    helicopters[3].offsetY = 15;

    helicopters[4].x = 150;
    helicopters[4].y = 1700;
    helicopters[4].offsetX = 25;
    helicopters[4].offsetY = 15;

    helicopters[5].x = -100;
    helicopters[5].y = 2500;
    helicopters[5].offsetX = 25;
    helicopters[5].offsetY = 15;

    for (int i = 0; i < 6; i++) {
        helicopters[i].visible = 1;
    }

    /////////////
    houses[0].x = 210;
    houses[0].y = 100;

    houses[1].x = -240;
    houses[1].y = 00;

    houses[2].x = 20;
    houses[2].y = 600;

    //////////////////
    ships[0].x = -155;
    ships[0].y = 200;
    ships[0].offsetX = 27;
    ships[0].offsetY = 17;

    ships[1].x = 25;
    ships[1].y = 375;
    ships[1].offsetX = 27;
    ships[1].offsetY = 17;

    ships[2].x = -165;
    ships[2].y = 700;
    ships[2].offsetX = 27;
    ships[2].offsetY = 17;

    ships[3].x = -25;
    ships[3].y = 1400;
    ships[3].offsetX = 27;
    ships[3].offsetY = 17;

    ships[4].x = -75;
    ships[4].y = 1060;
    ships[4].offsetX = 27;
    ships[4].offsetY = 17;

    ships[5].x = 100;
    ships[5].y = 2300;
    ships[5].offsetX = 27;
    ships[5].offsetY = 17;

    ships[6].x = 50;
    ships[6].y = 2600;
    ships[6].offsetX = 27;
    ships[6].offsetY = 17;

    ships[7].x = -50;
    ships[7].y = 2900;
    ships[7].offsetX = 27;
    ships[7].offsetY = 17;

    for (int i = 0; i < 8; i++) {
        ships[i].visible = 1;
    }
}

int colision(Object a, Object b) {

    float leftA = (a.x - a.offsetX);
    float leftB = (b.x - b.offsetX);
    float rightA = (a.x + a.offsetX);
    float rightB = (b.x + b.offsetX);

    float upA = (a.y + a.offsetY);
    float downB = (b.y - b.offsetY);
    float downA = (a.y - a.offsetY);
    float upB = (b.y + b.offsetY);

    if ((upA >= downB) && (downA <= upB) && (leftA < rightB) && (rightA > leftB)) {
        if (b.visible) {
            return 1;
        }
    }
    return 0;
}

void animate(int value) {
    if (start == 1) {
        airplanePosition.y += 4;
        screenPosition.y += -4;
        panelPosition.y += 4;
        heart1Position.y += 4;
        heart2Position.y += 4;
        heart3Position.y += 4;

        pointerPosition.y += 4;
        pointerPosition.x -= 1;
    }

    if (life < 0) {
        start = 0;
        screenPosition.x = 1500;
        screenPosition.y = janela_altura / 2;
    }

    if (bridges[1].visible == 0) {
        screenPosition.x = 3000;
        screenPosition.y = janela_altura / 2;
    }

    if (shotPosition.visible) {
        shotPosition.y += 30;
    }

    if (shotPosition.y > airplanePosition.y + 250) {
        shotPosition.visible = 0;
    }

    if (airplanePosition.x > 180 || airplanePosition.x < -180) {
        life--;
        startGame(airplanePosition);
    }

    if (pointerPosition.x < -150) {
        life--;
        startGame(airplanePosition);
    }

    for (int i = 0; i < 8; i++) {
        if (colision(airplanePosition, fuels[i]) && fuels[i].visible) {
            pointerPosition.x = 150;
            fuels[i].visible = 0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(50, animate, 1);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    case '\x0D':
        airplanePosition.x = 0;
        airplanePosition.y = 0;
        airplanePosition.offsetX = 15;
        airplanePosition.offsetY = 25;
        startGame(airplanePosition);
        life = 3;
        start = 1;
        break;
    }
}

void arrow_keys(int tecla, int x, int y) {
    if (tecla == GLUT_KEY_RIGHT) {
        airplanePosition.x += 5;
    }

    if (tecla == GLUT_KEY_LEFT) {
        airplanePosition.x -= 5;
    }

    if (tecla == GLUT_KEY_UP) {
        colision(airplanePosition, fuels[0]);
        shotPosition.x = airplanePosition.x;
        shotPosition.y = airplanePosition.y + airplanePosition.offsetY;
        shotPosition.visible = airplanePosition.visible;
    }

    glutPostRedisplay();
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w <= h) {
        gluOrtho2D(0.0f, janela_altura, 0.0f, janela_largura * h / w);
    }
    else {
        gluOrtho2D(0.0f, janela_altura * w / h, 0.0f, janela_largura);
    }


    glMatrixMode(GL_MODELVIEW);



}

void river() {
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    glVertex2f(-200, -250);
    glVertex2f(-200, 3000);
    glVertex2f(200, 3000);
    glVertex2f(200, -250);
    glEnd();
}

void airplane(Object object) {
    int x = object.x;
    int y = object.y;
    int offsetX = object.offsetX;
    int offsetY = object.offsetY;
    glScalef(1, 1, 1);
    glColor3f(1, 1, 1);


    glBegin(GL_POLYGON);
    glVertex2f(x - 3, y - offsetY + 5);
    glVertex2f(x - 3, y + offsetY);
    glVertex2f(x + 3, y + offsetY);
    glVertex2f(x + 3, y - offsetY + 5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f((x - offsetX), y);
    glVertex2f((x - offsetX), y + 8);
    glVertex2f(x, y + 16);
    glVertex2f(x, y + 8);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f((x + offsetX), y);
    glVertex2f((x + offsetX), y + 8);
    glVertex2f(x, y + 16);
    glVertex2f(x, y + 8);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f((x - offsetX + 5), y - offsetY);
    glVertex2f((x - offsetX + 5), y - offsetY + 5);
    glVertex2f(x, y - offsetY + 10);
    glVertex2f(x, y - offsetY + 5);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f((x + offsetX - 5), y - offsetY);
    glVertex2f((x + offsetX - 5), y - offsetY + 5);
    glVertex2f(x, y - offsetY + 10);
    glVertex2f(x, y - offsetY + 5);
    glEnd();
}

void fuel(Object object) {
    int x = object.x;
    int y = object.y;
    int offsetX = object.offsetX;
    int offsetY = object.offsetY;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - offsetX, y - offsetY);
    glVertex2f((x + offsetX), y - offsetY);
    glVertex2f((x + offsetX), (y - offsetY + 10));
    glVertex2f(x - offsetX, (y - offsetY + 10));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x - offsetX, (y - offsetY + 10));
    glVertex2f((x + offsetX), (y - offsetY + 10));
    glVertex2f((x + offsetX), (y - offsetY + 20));
    glVertex2f(x - offsetX, (y - offsetY + 20));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - offsetX, (y - offsetY + 20));
    glVertex2f((x + offsetX), (y - offsetY + 20));
    glVertex2f((x + offsetX), (y - offsetY + 30));
    glVertex2f(x - offsetX, (y - offsetY + 30));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x - offsetX, (y - offsetY + 30));
    glVertex2f((x + offsetX), (y - offsetY + 30));
    glVertex2f((x + offsetX), (y + offsetY - 5));
    glVertex2f(x - offsetX, (y + offsetY - 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f((x - offsetX + 20), y + offsetY - 5);
    glVertex2f((x - offsetX + 20), (y + offsetY));
    glVertex2f((x - offsetX + 5), (y + offsetY));
    glVertex2f((x - offsetX + 5), (y + offsetY - 5));
    glEnd();
}

void grass(Object object) {
    int x = object.x;
    int y = object.y;
    int offsetX = object.offsetX;
    int offsetY = object.offsetY;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.65f, 0.33f);
    glVertex2f(x - offsetX, y - offsetY);
    glVertex2f((x + offsetX), y - offsetY);
    glVertex2f((x + offsetX), (y + offsetY));
    glVertex2f(x - offsetX, (y + offsetY));
    glEnd();
}

void bridge(Object object) {
    int x = object.x;
    int y = object.y;
    int offsetX = object.offsetX;
    int offsetY = object.offsetY;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(0.32, 0.32, 0.28);
    glVertex2f(x - offsetX, y - offsetY);
    glVertex2f((x + offsetX), y - offsetY);
    glVertex2f((x + offsetX), (y + offsetY));
    glVertex2f(x - offsetX, (y + offsetY));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x - offsetX + 50, y - 5);
    glVertex2f((x - offsetX + 50), y + 5);
    glVertex2f((x - 100), (y + 5));
    glVertex2f(x - 100, (y - 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x - 50, y - 5);
    glVertex2f((x - 50), y + 5);
    glVertex2f((x + 50), (y + 5));
    glVertex2f(x + 50, (y - 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x + 100, y - 5);
    glVertex2f((x + 100), y + 5);
    glVertex2f((x + 200), (y + 5));
    glVertex2f(x + 200, (y - 5));
    glEnd();
}

void ship(Object object) {
    int x = object.x;
    int y = object.y;
    int offsetX = object.offsetX;
    int offsetY = object.offsetY;

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.33, 0.13);
    glVertex2f((x - offsetX), y - offsetY);
    glVertex2f((x + offsetX), y - offsetY);
    glVertex2f((x + offsetX), (y - offsetY + 5));
    glVertex2f((x - offsetX), (y - offsetY + 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f((x - offsetX), (y - offsetY + 5));
    glVertex2f((x + offsetX + 5), (y - offsetY + 5));
    glVertex2f((x + offsetX + 5), (y - offsetY + 15));
    glVertex2f((x - offsetX), (y - offsetY + 15));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f((x - offsetX + 10), (y - offsetY + 15));
    glVertex2f((x + offsetX - 5), (y - offsetY + 15));
    glVertex2f((x + offsetX - 5), (y - offsetY + 20));
    glVertex2f((x - offsetX + 10), (y - offsetY + 20));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f((x - offsetX + 20), (y - offsetY + 20));
    glVertex2f((x + offsetX - 15), (y - offsetY + 20));
    glVertex2f((x + offsetX - 15), (y - offsetY + 24));
    glVertex2f((x - offsetX + 20), (y - offsetY + 24));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0, 0, 0);
    glVertex2f((x - offsetX + 25), (y - offsetY + 24));
    glVertex2f((x + offsetX - 20), (y - offsetY + 24));
    glVertex2f((x + offsetX - 20), (y + offsetY));
    glVertex2f((x - offsetX + 25), (y + offsetY));
    glEnd();
}

void helicopter(Object object) {
    int x = object.x;
    int y = object.y;
    int offsetX = object.offsetX;
    int offsetY = object.offsetY;

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 1);
    glVertex2f((x - 10), y - offsetY);
    glVertex2f((x - 10), y - offsetY + 3);
    glVertex2f((x + 10), y - offsetY + 3);
    glVertex2f((x + 10), (y - offsetY));
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 1);
    glVertex2f((x - 2), y - offsetY);
    glVertex2f((x - 2), y);
    glVertex2f((x + 2), y);
    glVertex2f((x + 2), (y - offsetY));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2f((x - offsetX), y);
    glVertex2f((x - offsetX), (y + 5));
    glVertex2f((x + offsetX), (y + 5));
    glVertex2f((x + offsetX), y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2f((x - offsetX + 15), y - 5);
    glVertex2f((x - offsetX + 15), (y + 5));
    glVertex2f((x + offsetX - 10), (y + 5));
    glVertex2f((x + offsetX - 10), y - 5);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 1);
    glVertex2f((x - offsetX), (y - 10));
    glVertex2f((x - offsetX), (y + 10));
    glVertex2f((x - offsetX + 7), (y + 5));
    glVertex2f((x - offsetX + 7), (y - 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f((x - 2), (y + 5));
    glVertex2f((x - 2), (y + 10));
    glVertex2f((x + 2), (y + 10));
    glVertex2f((x + 2), (y + 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x - 2, (y + 10));
    glVertex2f(x - 2, (y + 12.5));
    glVertex2f((x + 20), (y + 12.5));
    glVertex2f((x + 20), (y + 10));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x - 2, (y + 12.5));
    glVertex2f(x - 2, (y + 15));
    glVertex2f((x - offsetX + 5), (y + 15));
    glVertex2f((x - offsetX + 5), (y + 12.5));
    glEnd();

}

void house(int x, int y) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.45, 0.33, 0.13);
    glVertex2f(x, y);
    glVertex2f((x + 35), y);
    glVertex2f((x + 17), (y + 15));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(x, (y - 15));
    glVertex2f((x + 35), (y - 15));
    glVertex2f((x + 35), y);
    glVertex2f(x, y);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.33, 0.13);
    glVertex2f((x + 5), (y - 10));
    glVertex2f((x + 10), (y - 10));
    glVertex2f((x + 10), (y - 5));
    glVertex2f((x + 5), (y - 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.33, 0.13);
    glVertex2f((x + 15), (y - 10));
    glVertex2f((x + 20), (y - 10));
    glVertex2f((x + 20), (y - 5));
    glVertex2f((x + 15), (y - 5));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.45, 0.33, 0.13);
    glVertex2f((x + 25), (y - 10));
    glVertex2f((x + 30), (y - 10));
    glVertex2f((x + 30), (y - 5));
    glVertex2f((x + 25), (y - 5));
    glEnd();
}

void panel(Object object) {
    int x = object.x;
    int y = object.y;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(0.32, 0.32, 0.28);
    glVertex2f(x - 250, y - 250);
    glVertex2f((x + 250), y - 250);
    glVertex2f((x + 250), (y - 170));
    glVertex2f(x - 250, (y - 170));
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 200, y - 180);
    glVertex2f((x + 200), y - 180);
    glVertex2f((x + 200), (y - 230));
    glVertex2f(x - 200, (y - 230));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 150, y - 180);
    glVertex2f((x - 150), y - 190);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 150, y - 180);
    glVertex2f((x + 150), y - 190);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x, y - 180);
    glVertex2f(x, y - 190);
    glEnd();

    //E
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 140, y - 220);
    glVertex2f((x - 160), y - 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 140, y - 200);
    glVertex2f((x - 160), y - 200);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 140, y - 210);
    glVertex2f((x - 160), y - 210);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 160, y - 220);
    glVertex2f((x - 160), y - 200);
    glEnd();

    //F
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 140, y - 210);
    glVertex2f((x + 160), y - 210);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 140, y - 200);
    glVertex2f((x + 160), y - 200);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 140, y - 220);
    glVertex2f((x + 140), y - 200);
    glEnd();

    //1/2
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 10, y - 220);
    glVertex2f((x + 10), y - 200);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 10, y - 200);
    glVertex2f((x - 5), y - 200);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 5, y - 200);
    glVertex2f((x - 5), y - 210);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 8, y - 210);
    glVertex2f((x + 13), y - 210);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 8, y - 215);
    glVertex2f((x + 13), y - 215);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 8, y - 220);
    glVertex2f((x + 13), y - 220);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 13, y - 210);
    glVertex2f((x + 13), y - 215);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 8, y - 215);
    glVertex2f((x + 8), y - 220);
    glEnd();
}

void pointer(Object object) {
    int x = object.x;
    int y = object.y;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x - 5, y - 190);
    glVertex2f((x - 5), y - 220);
    glVertex2f((x + 5), (y - 220));
    glVertex2f(x + 5, (y - 190));
    glEnd();
}

void heart(Object object) {
    int x = object.x;
    int y = object.y;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - 194, y - 250);
    glVertex2f((x - 194), y - 247);
    glVertex2f((x - 191), (y - 247));
    glVertex2f(x - 191, (y - 250));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - 188, y - 247);
    glVertex2f((x - 188), y - 243);
    glVertex2f((x - 197), (y - 243));
    glVertex2f(x - 197, (y - 247));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - 185, y - 243);
    glVertex2f((x - 185), y - 240);
    glVertex2f((x - 200), (y - 240));
    glVertex2f(x - 200, (y - 243));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - 194, y - 240);
    glVertex2f((x - 194), y - 237);
    glVertex2f((x - 198), (y - 237));
    glVertex2f(x - 198, (y - 240));
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(x - 187, y - 240);
    glVertex2f((x - 187), y - 237);
    glVertex2f((x - 191), (y - 237));
    glVertex2f(x - 191, (y - 240));
    glEnd();
}

void names(int x, int y) {
    glScalef(1, 1, 1);

    //c
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 220, y - 220);
    glVertex2f((x - 240), y - 220);
    glVertex2f((x - 240), (y - 190));
    glVertex2f(x - 220, (y - 190));
    glEnd();

    //a
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 210, y - 220);
    glVertex2f((x - 200), y - 190);
    glVertex2f((x - 190), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 205, y - 205);
    glVertex2f((x - 195), y - 205);
    glEnd();

    //m
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 180, y - 220);
    glVertex2f((x - 180), y - 190);
    glVertex2f((x - 160), (y - 205));
    glVertex2f((x - 140), (y - 190));
    glVertex2f((x - 140), (y - 220));
    glEnd();

    //i
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 130, y - 220);
    glVertex2f((x - 130), y - 190);
    glEnd();

    //l
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 120, y - 190);
    glVertex2f((x - 120), y - 220);
    glVertex2f((x - 100), (y - 220));
    glEnd();

    //l
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 90, y - 190);
    glVertex2f((x - 90), y - 220);
    glVertex2f((x - 70), (y - 220));
    glEnd();

    //a
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 60, y - 220);
    glVertex2f((x - 50), y - 190);
    glVertex2f((x - 40), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 55, y - 205);
    glVertex2f((x - 45), y - 205);
    glEnd();

    //e
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x + 10, y - 190);
    glVertex2f((x - 10), y - 190);
    glVertex2f((x - 10), (y - 220));
    glVertex2f((x + 10), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 10, y - 205);
    glVertex2f((x + 10), y - 205);
    glEnd();

    //j
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x + 50, y - 190);
    glVertex2f((x + 50), y - 220);
    glVertex2f((x + 40), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 40, y - 190);
    glVertex2f((x + 60), y - 190);
    glEnd();

    //o
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(x + 70, y - 190);
    glVertex2f((x + 70), y - 220);
    glVertex2f((x + 90), (y - 220));
    glVertex2f((x + 90), (y - 190));
    glEnd();

    //a
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x + 100, y - 220);
    glVertex2f((x + 110), y - 190);
    glVertex2f((x + 120), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x + 105, y - 205);
    glVertex2f((x + 115), y - 205);
    glEnd();

    //o
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(x + 130, y - 190);
    glVertex2f((x + 130), y - 220);
    glVertex2f((x + 150), (y - 220));
    glVertex2f((x + 150), (y - 190));
    glEnd();
}

void piramide() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);	glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);	glVertex3f(1.5f, 0.5f, 1.0f);
    glEnd();
}

void draw3d() {
    glPushMatrix();
    glTranslatef(-520.0f, 0.0f, 1.0f);
    glScalef(60, 60, 1);
    piramide();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-400.0f, 0.0f, 1.0f);
    glScalef(60, 60, 1);
    piramide();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-500.0f, -50.0f, 1.0f);
    glScalef(60, 60, 1);
    piramide();
    glPopMatrix();
}

void riverraid(int x, int y) {
    //r
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 240, y - 220);
    glVertex2f((x - 240), y - 190);
    glVertex2f((x - 220), (y - 190));
    glVertex2f((x - 220), (y - 195));
    glVertex2f(x - 240, (y - 195));
    glVertex2f(x - 220, (y - 220));
    glEnd();

    //i
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 210, y - 220);
    glVertex2f((x - 210), y - 190);
    glEnd();

    //v
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 200, y - 190);
    glVertex2f((x - 190), y - 220);
    glVertex2f((x - 180), (y - 190));
    glEnd();

    //e
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 150, y - 190);
    glVertex2f((x - 170), y - 190);
    glVertex2f((x - 170), (y - 220));
    glVertex2f((x - 150), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 170, y - 205);
    glVertex2f((x - 150), y - 205);
    glEnd();

    //r
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 140, y - 220);
    glVertex2f((x - 140), y - 190);
    glVertex2f((x - 120), (y - 190));
    glVertex2f((x - 120), (y - 195));
    glVertex2f(x - 140, (y - 195));
    glVertex2f(x - 120, (y - 220));
    glEnd();

    //r
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 90, y - 220);
    glVertex2f((x - 90), y - 190);
    glVertex2f((x - 70), (y - 190));
    glVertex2f((x - 70), (y - 195));
    glVertex2f(x - 90, (y - 195));
    glVertex2f(x - 70, (y - 220));
    glEnd();

    //a
    glBegin(GL_LINE_STRIP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 60, y - 220);
    glVertex2f((x - 50), y - 190);
    glVertex2f((x - 40), (y - 220));
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 55, y - 205);
    glVertex2f((x - 45), y - 205);
    glEnd();

    //i
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(x - 30, y - 220);
    glVertex2f((x - 30), y - 190);
    glEnd();

    //D
    glBegin(GL_LINE_LOOP);
    glColor3f(1, 1, 1);
    glVertex2f(x - 20, y - 220);
    glVertex2f((x - 20), y - 190);
    glVertex2f((x - 10), (y - 205));
    glEnd();

}

void shot(Object object) {
    int x = object.x;
    int y = object.y;
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 0);
    glVertex2f(x - 1, y - 20);
    glVertex2f((x - 1), y - 30);
    glVertex2f((x + 1), (y - 30));
    glVertex2f(x + 1, (y - 20));
    glEnd();
}

void sad() {
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-1350, 60);
    glVertex2f(-1320, 60);
    glVertex2f(-1320, 90);
    glVertex2f(-1350, 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-1200, 60);
    glVertex2f(-1170, 60);
    glVertex2f(-1170, 90);
    glVertex2f(-1200, 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-1350, -100);
    glVertex2f(-1320, -100);
    glVertex2f(-1320, -50);
    glVertex2f(-1350, -50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-1200, -100);
    glVertex2f(-1170, -100);
    glVertex2f(-1170, -50);
    glVertex2f(-1200, -50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-1320, -70);
    glVertex2f(-1200, -70);
    glVertex2f(-1200, -50);
    glVertex2f(-1320, -50);
    glEnd();
}

void happy() {
    glScalef(1, 1, 1);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-2900, 60);
    glVertex2f(-2840, 60);
    glVertex2f(-2840, 90);
    glVertex2f(-2900, 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-2700, 60);
    glVertex2f(-2640, 60);
    glVertex2f(-2640, 90);
    glVertex2f(-2700, 90);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-2900, -100);
    glVertex2f(-2840, -100);
    glVertex2f(-2840, -50);
    glVertex2f(-2900, -50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-2700, -100);
    glVertex2f(-2640, -100);
    glVertex2f(-2640, -50);
    glVertex2f(-2700, -50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2f(-2840, -70);
    glVertex2f(-2700, -70);
    glVertex2f(-2700, -100);
    glVertex2f(-2840, -100);
    glEnd();
}

void draw() {
    river();

    airplane(airplanePosition);

    if (shotPosition.visible) {
        shot(shotPosition);
    }

    for (int i = 0; i < 2; i++) {
        if (colision(shotPosition, bridges[i])) {
            bridges[i].visible = 0;
            shotPosition.visible = 0;
        }
        if (bridges[i].visible) {
            bridge(bridges[i]);
        }
        if (colision(airplanePosition, bridges[i])) {
            life--;
            startGame(airplanePosition);
        }
    }

    for (int i = 0; i < 8; i++) {
        if (fuels[i].visible) {
            fuel(fuels[i]);
        }
    }

    for (int i = 0; i < 10; i++) {
        grass(grasses[i]);
        if (colision(airplanePosition, grasses[i])) {
            life--;
            startGame(airplanePosition);
        }
    }

    for (int i = 0; i < 6; i++) {
        if (colision(shotPosition, helicopters[i])) {
            helicopters[i].visible = 0;
            shotPosition.visible = 0;
        }
        if (helicopters[i].visible) {
            helicopter(helicopters[i]);
        }
        if (colision(airplanePosition, helicopters[i])) {
            life--;
            startGame(airplanePosition);
        }
    }

    for (int i = 0; i < 3; i++) {
        house(houses[i].x, houses[i].y);
    }

    for (int i = 0; i < 8; i++) {
        if (colision(shotPosition, ships[i])) {
            ships[i].visible = 0;
            shotPosition.visible = 0;
        }
        if (ships[i].visible) {
            ship(ships[i]);
        }
        if (colision(airplanePosition, ships[i])) {
            life--;
            startGame(airplanePosition);
        }
    }

    panel(panelPosition);
    pointer(pointerPosition);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.2f, 0.65f, 0.33f, 0.0f);
    glTranslatef(screenPosition.x, screenPosition.y, 0.0f);

    draw();

    names(-480, 0);
    riverraid(-400, 300);

    if (life == 3) {
        heart(heart1Position);
        heart(heart2Position);
        heart(heart3Position);
    }
    else if (life == 2) {
        heart(heart1Position);
        heart(heart2Position);
    }
    else if (life == 1) {
        heart(heart1Position);
    }

    sad();
    happy();
    draw3d();
    glFlush();
}

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float cataventoPosX = 0.0f, cataventoPosY = 0.1f; 
float cataventoScale = 1.0f;
float rotationAngle = 0.0f;
float rotationSpeed = 0.05f;
bool isRotating = true;
float cores[4][3] = { {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f} };
float nuvemPosX = -1.0f;
float nuvemSpeed = 0.001f;

void desenhaCatavento() {
    glPushMatrix();
    glTranslatef(cataventoPosX, cataventoPosY, 0.0f);
    glScalef(cataventoScale, cataventoScale, 1.0f);
    glColor3f(0.65f, 0.33f, 0.16f);    
    glBegin(GL_QUADS);
        glVertex2f(-0.025f, -0.55f);
        glVertex2f(0.025f, -0.55f);
        glVertex2f(0.025f, 0.0f);
        glVertex2f(-0.025f, 0.0f);
    glEnd();
    
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
    for (int i = 0; i < 4; ++i) {
        glColor3fv(cores[i]);
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.3f * cos(i * M_PI / 2), 0.3f * sin(i * M_PI / 2));
            glVertex2f(0.15f * cos((i + 1) * M_PI / 2), 0.15f * sin((i + 1) * M_PI / 2));
        glEnd();
    }
    glPopMatrix();
}

void desenhaSol(float PosX, float PosY, float cor, float raio) {
    glColor3f(1.0f, 1.0f, cor);
    float radius = raio;
    int numSegments = 50;
    float posX = PosX;
    float posY = PosY;

    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; ++i) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = posX + radius * cos(angle);
        float y = posY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void desenhaColina(float PosX, float PosY, float Raio, float verde) {
    glColor3f(0.0f, verde, 0.0f);
    float radius = Raio;
    int numSegments = 100;
    float posX = PosX;
    float posY = PosY;

    glBegin(GL_POLYGON);
    for (int i = 0; i <= numSegments / 2; ++i) {
        float angle = M_PI * i / (numSegments / 2);
        float x = posX + radius * cos(angle);
        float y = posY + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    desenhaSol(0.7, 0.7, 0.0, 0.4);

    desenhaSol(nuvemPosX - 0.1f, 0.7f, 1.0f, 0.08f);
    desenhaSol(nuvemPosX, 0.7f, 1.0f, 0.1f);
    desenhaSol(nuvemPosX + 0.1f, 0.7f, 1.0f, 0.1f);
    desenhaSol(nuvemPosX + 0.2f, 0.7f, 1.0f, 0.11f);
    desenhaSol(nuvemPosX + 0.3f, 0.7f, 1.0f, 0.08f);

    desenhaColina(0.7, -1.4, 1.2, 0.5);
    desenhaColina(-0.7, -1.8, 1.2, 0.5);
    desenhaColina(0.0, -1.6, 1.2, 0.7);

    desenhaCatavento();

    glutSwapBuffers();
}

void idle() {
    if (isRotating) {
        rotationAngle += rotationSpeed;
        nuvemPosX += nuvemSpeed;
        
        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
        if (nuvemPosX > 1.2f) {
            nuvemPosX = -1.2f;
        } else if (nuvemPosX < -1.2f) {
            nuvemPosX = 1.2f;
        }
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r':
            rotationSpeed = -fabs(rotationSpeed);
            nuvemSpeed = -fabs(nuvemSpeed);
            isRotating = true;
            break;
        case 'l':
            rotationSpeed = fabs(rotationSpeed);
            nuvemSpeed = fabs(nuvemSpeed);
            isRotating = true;
            break;
        case 'p':
            isRotating = !isRotating;
            break;
        case '+':
            cataventoScale += 0.1f;
            break;
        case '-':
            if (cataventoScale > 0.2f) cataventoScale -= 0.1f;
            break;
        case 'c':
            for (int i = 0; i < 4; ++i) {
                cores[i][0] = (float)rand() / RAND_MAX;
                cores[i][1] = (float)rand() / RAND_MAX;
                cores[i][2] = (float)rand() / RAND_MAX;
            }
            break;
        case '1':
            rotationSpeed = 0.05f;
            nuvemSpeed = 0.0007f;
            break;
        case '2':
            rotationSpeed = 0.1f;
            nuvemSpeed = 0.002f;
            break;
        case '3':
            rotationSpeed = 0.3f;
            nuvemSpeed = 0.003f;
            break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            cataventoPosY += 0.1f;
            break;
        case GLUT_KEY_DOWN:
            cataventoPosY -= 0.1f;
            break;
        case GLUT_KEY_LEFT:
            cataventoPosX -= 0.1f;
            break;
        case GLUT_KEY_RIGHT:
            cataventoPosX += 0.1f;
            break;
    }
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            float primeiraCor[3] = { cores[0][0], cores[0][1], cores[0][2] };

            for (int i = 0; i < 3; ++i) {
                cores[i][0] = cores[i + 1][0];
                cores[i][1] = cores[i + 1][1];
                cores[i][2] = cores[i + 1][2];
            }

            cores[3][0] = primeiraCor[0];
            cores[3][1] = primeiraCor[1];
            cores[3][2] = primeiraCor[2];
        } else if (button == GLUT_RIGHT_BUTTON) {
            cataventoPosX = 0.0f;
            cataventoPosY = 0.0f;
            cataventoScale = 1.0f;
            rotationAngle = 0.0f;
        }
        glutPostRedisplay();
    }
}

void init() {
    srand(time(NULL));
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Catavento Interativo 2D");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

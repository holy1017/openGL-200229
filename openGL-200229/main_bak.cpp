#include <gl/glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv);

void doDisplay();
void doIdle();

void ChgWinSize(int w, int h);

void KeyUp(unsigned char key, int x, int y);
void KeyDown(unsigned char key, int x, int y);
void KeySpecialUp(int key, int x, int y);
void KeySpecialDown(int key, int x, int y);
void MouseDown(int button, int state, int x, int y);

void DoMenu(int value);

void renderScene1();
void renderScene2();
void renderScene3();
void renderScene4();
void renderScene5();

void (*renderSceneP)(); // = NULL;

void initMain();

void setScene();

void initScene();
void initScene1();
void initScene2();
void initScene3();
void initScene4();
void initScene5();

void (*initSceneP)(); // = NULL;

void KeySpecialDown3(int key, int x, int y);
void KeySpecialDown4(int key, int x, int y);

GLuint createDL();
void orientMe(float ang);
void moveMeFlat(int direction);

void Lock();


GLfloat f_x = 0.0, f_y = 0.0;
GLint   s_mod = '5'; // ��� �⺻��
GLint   i_x = 0, i_y = 0;
GLint   w_w = 300, w_h = 400;

GLfloat Alpha = 0.1f;
GLenum Src = GL_SRC_ALPHA;
GLenum Dest = GL_ONE_MINUS_SRC_ALPHA;
float red = 1.0, blue = 1.0, green = 1.0;

int k_mod;

static float angle = 0.0, ratio;
static GLdouble x = 0.0f, y = 1.75f, z = 5.0f;
static GLdouble lx = 0.0f, ly = 0.0f, lz = -1.0f;
static GLint snowman_display_list;


// ((x - x1) / (xr)) ^ (2) + ((y - y1) / (yr)) ^ (2) = 1
// ((x - x1) / (r)) ^ (2) + ((y - y1) / (r)) ^ (2) = 1   // xr==yr �ϰ�� ����. r�� ġȯ. ������
// (x - x1) ^ (2) + (y - y1) ^ (2) = r ^ 2 // �Ϲ� �� ������ ����

// y= a*x^2 + b*x + c
// y= a(x-x1)^2 + y1
// y-y1=a(x-x1)^2 
// 0=(x-x1)^2 - (y-y1)/a
// ((x-x1)/(xr))^(2) - (y-y1)*(yr)=0 // ������

// ((x-x1)/(xr))^(2)- ((y-y1)/(yr))^(2)=1 // �ְ , 
//  x1:��ǥ,xr:������


int main(int argc, char** argv)
{
    glutInit(&argc, argv);              // �ʱ�ȭ


    //glutInitDisplayMode();
    //glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT DEPTH);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    //  �Ʒ��� �̸� ���ǵǾ� �ִ� ���� ��(color model)�� ����Դϴ�.
    //
    //    GLUT_RGBA �Ǵ� GLUT_RGB - RGBA â�� ����ϴ�.�� ���� glut �� ����ϴ� �⺻ ���� ����Դϴ�.
    //    GLUT_INDEX - �ε��� ���� ���� �����մϴ�.
    //
    //    ���÷��� ���� ���Ϲ��� â�� ���� ������ �ƴϸ� ���߹��� â�� ���� ������ �����ϴ� ���ε�, �Ʒ��� ������ �� �ִ� ����� �ֽ��ϴ�.:
    //    GLUT_SINGLE - ���Ϲ���(single buffer) â�� �����.
    //    GLUT_DOUBLE - ���߹���(double buffer) â�� �����.�ε巯�� ���ϸ��̼��� ���� �� �ʿ��մϴ�.
    //
    //    �׸��� �������� ���Ѵٸ� Ư�� ���۷� ������ â�� ���� �� �ֽ��ϴ�.�Ʒ��� ���� ���� �����ϴ� �����Դϴ�. :
    //    GLUT_ACCUM - ��ť�ķ��̼� ����(The accumulation buffer)
    //    GLUT_STENCIL - ���ٽ� ����(The stencil buffer)
    //    GLUT_DEPTH - ���� ����(The depth buffer)

    glutCreateWindow("OpenGL");         // ������ �����.
    glutInitWindowPosition(100, 100);   // ȭ�� �ʱ� ��ġ
    glutInitWindowSize(w_w, w_h);       // ȭ�� ũ��

    initMain();
    initScene();

    glutKeyboardFunc(KeyDown);          // Ű���� �Է� �Լ�.
    glutKeyboardUpFunc(KeyUp);          //

    glutSpecialFunc(KeySpecialDown);
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutDisplayFunc(doDisplay);         // ȭ��ǥ���Լ�.
    glutIdleFunc(doIdle);          //�޸�(idle)�ð��� ȣ��� �Լ��� �����Ѵ�.


    glutCreateMenu(DoMenu);             // �޴� ���� �Լ�
    glutAddMenuEntry("renderScene1", 1);      // �޴� ��Ʈ�� 1
    glutAddMenuEntry("renderScene2", 2);  // �޴� ��Ʈ�� 2
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // ������ ��ư�� ������ �޴�����

    glEnable(GL_DEPTH_TEST);   //���� �˻簡 �����ϵ��� �����Ѵ�.

    glutReshapeFunc(ChgWinSize);     // ������ ũ�� ����� ����

    glutMainLoop();                     // ���η���

    return 0;
}
//================================================================

void initMain() {
    snowman_display_list = createDL();

    switch (s_mod) {
    case '1':
        renderSceneP = renderScene1;
        initSceneP = initScene1;
        break;
    case '2':
        renderSceneP = renderScene2;
        initSceneP = initScene2;
        break;
    case '3':
        renderSceneP = renderScene3;
        initSceneP = initScene3;
        break;
    case '4':
        renderSceneP = renderScene4;
        initSceneP = initScene4;
        break;
    case '5':
        renderSceneP = renderScene5;
        initSceneP = initScene5;
        break;
    }
}

void Lock()
{
    glLoadIdentity();
    gluLookAt(x, y, z,
        x + lx, y + ly, z + lz,
        0.0f, 1.0f, 0.0f);
    printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", x, y, z, lx, ly, lz);
}

//================================================================
void KeyDown(unsigned char key, int x, int y) // q, a�� ������ �� ���İ� ����
{
    k_mod = glutGetModifiers();
    printf("KeyDown : %c , %d : %d , %d \n", key, k_mod, x, y);
    switch (key) {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
        s_mod = key;
        initScene();
        printf("mod : %d \n", s_mod);
        break;
    case 'a':
        if (k_mod == GLUT_ACTIVE_SHIFT)
            printf("");
        break;
    case 'd':
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    default:
        printf("");
    }
    glutPostRedisplay(); // ȭ�� �����
}
void KeyUp(unsigned char key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeyUp : %c , %d : %d , %d \n", key, k_mod, x, y);
}
void KeySpecialDown(int key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeySpecialDown : %d , %d : %d , %d \n", key, k_mod, x, y);
    //��:100
    //��:101
    //��:102
    //��:103
    //    GLUT_KEY_F1            F1 Ű
    //    GLUT_KEY_F2            F2 Ű
    //    GLUT_KEY_F3            F3 Ű
    //    GLUT_KEY_F4            F4 Ű
    //    GLUT_KEY_F5            F5 Ű
    //    GLUT_KEY_F6            F6 Ű
    //    GLUT_KEY_F7            F7 Ű
    //    GLUT_KEY_F8            F8 Ű
    //    GLUT_KEY_F9            F9 Ű
    //    GLUT_KEY_F10        F10 Ű
    //    GLUT_KEY_F11        F11 Ű
    //    GLUT_KEY_F12        F12 Ű
    //    GLUT_KEY_LEFT        ���� ����Ű(��)
    //    GLUT_KEY_RIGHT        ������ ����Ű(��)
    //    GLUT_KEY_UP            ���� ����Ű(��)
    //    GLUT_KEY_DOWN        �Ʒ��� ����Ű(��)
    //    GLUT_KEY_PAGE_UP    Page Up Ű
    //    GLUT_KEY_PAGE_DOWN    Page Down Ű
    //    GLUT_KEY_HOME        Home Ű
    //    GLUT_KEY_END        End Ű
    //    GLUT_KEY_INSERT        Insert Ű    
    switch (s_mod)
    {
    case '3':
        KeySpecialDown3(key, x, y);
        break;
    case '4':
        KeySpecialDown4(key, x, y);
        break;
    default:
        break;
    }
    glutPostRedisplay(); // ȭ�� �����
}


void KeySpecialUp(int key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeySpecialUp : %d , %d : %d , %d \n", key, k_mod, x, y);
    //��:100
    //��:101
    //��:102
    //��:103
}

void MouseDown(int button, int state, int x, int y)
{
    printf("Mouse : %d , %d : %d , %d \n", button, state, x, y);
    // 1:�ٿ� , 2:��
}

//================================================================

void doDisplay()
{
    renderSceneP();
    //switch (s_mod) {
    //case '1':
    //    renderScene1();
    //    break;    
    //case '2':
    //    renderScene2();
    //    break;
    //case '3':
    //    renderScene3();
    //    break;
    //case '4':        
    //    renderScene4();
    //    break;
    //case '5':        
    //    renderScene5();
    //    break;
    //case 'd':
    //    
    //    break;
    //default:
    //
    //    printf("DoDisplay : %d \n", s_mod);
    //}
}
void doIdle()
{
    switch (s_mod) {
    case '1':
        //renderScene();
        break;
    case '2':
        renderScene2();
        break;
    case '3':
        //renderScene3();
        break;
    case '4':
        renderScene4();
        break;
    case '5':
        //renderScene5();
        break;
    case 'd':

        break;
    default:

        printf("DoIdle : %d \n", s_mod);
    }
}
void DoMenu(int value)
{
    switch (value) {
    case 1:
        s_mod = '1';
        break;
    case 2:
        s_mod = '2';
        break;
    }
    glutPostRedisplay(); // ȭ�� �����
}

//================================================================

void initScene()
{
    printf("initScene : %d \n", s_mod);
    switch (s_mod) {
    case '1':
        initScene1();
        initSceneP = initScene1;
        break;
    case '2':
        initScene2();
        break;
    case '3':
        initScene3();
        break;
    case '4':
        initScene4();
        break;
    case '5':
        initScene4();
        break;
    }
}

//================================================================

void initScene1()
{
    angle = 0.0, ratio;
    x = 0.0f, y = 0.0f, z = 5.0f;
    lx = 0.0f, ly = 0.0f, lz = -1.0f - z;
    //glLoadIdentity();
    //gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
    Lock();
}

void renderScene1()
{
    printf("renderScene1\n");
    //glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();

    glPopMatrix();
    glutSwapBuffers();
}
//================================================================

void initScene2()
{
    angle = 0.0, ratio;
    x = 0.0f, y = 0.0f, z = 5.0f;
    lx = 0.0f, ly = 0.0f, lz = -1.0f - z;
    //glLoadIdentity();
    //gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
    Lock();
}

void renderScene2()
{
    printf("renderScene2\n");
    // ���� ���۸� ������ �������մϴ�.
    // ���� ���۰� ���������� �ƹ��͵� �׷����� �ʱ� ��������. 
    // �Ʒ��� ���̹��۸� �����ִ� �ڵ��Դϴ�.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ������ ������ �͵��� �����մϴ�.
    // ���⼭�� ī�޶��� ������ �����մϴ�.
    glPushMatrix();

    // angle �������� ȸ�������� y ��(0, 1, 0)�� �߽����� ȸ����ȯ�� �����մϴ�. 
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    // �𵨸� ��ȯ�� ��ġ����
    // ī�޶����� ������� ���������ϴ�.
    glPopMatrix();

    // ������ �׸����� �����ֱ� ���ؼ� ���۸� ��ü�մϴ�.
    glutSwapBuffers();

    // ���������� angle ������ 1 �� �����ݴϴ�.
    angle++;
}

//================================================================

void KeySpecialDown3(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_F1:
        if (k_mod == (GLUT_ACTIVE_CTRL | GLUT_ACTIVE_ALT))
        {
            red = 1.0; green = 0.0; blue = 0.0;
            printf("GLUT_ACTIVE \n");
        }
        break;
    case GLUT_KEY_F2:
        red = 0.0;
        green = 1.0;
        blue = 0.0;
        break;
    case GLUT_KEY_F3:
        red = 0.0;
        green = 0.0;
        blue = 1.0;
        break;
    }
}


void initScene3()
{
    angle = 0.0, ratio;
    x = 0.0f, y = 0.0f, z = 5.0f;
    lx = 0.0f, ly = 0.0f, lz = -1.0f - z;
    //glLoadIdentity();
    //gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
    //printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", x, y, z, lx, ly, lz);
    Lock();
}

void renderScene3(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    // ���⼭ ���� ���� �����մϴ�.
    // glColor �� ������ �׷��� ��ü���� ���� �����մϴ�.
    glColor3f(red, green, blue);

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glPopMatrix();

    angle++;
    glutSwapBuffers();
}


void ChgWinSize(int w, int h)
{
    printf("changeSize : %d , %d \n", w, h);

    //https://skyfe79.gitbooks.io/glut-tutorials/chapter3.html
    //â�� ���� ���� ��, 0 ���� ������ ���� �����մϴ�.
    if (h == 0)
        h = 1;

    w_h = h;
    w_w = w;

    ratio = 1.0f * w / h;

    //��ǥ�踦 �����ϱ� ���� �ʱ�ȭ�մϴ�.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //����Ʈ�� â�� ��ü ũ��� �����մϴ�.
    glViewport(0, 0, w, h);

    //���ð��� �����մϴ�.
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //gluLookAt(
    //    x, y, z,
    //    x + lx, y + ly, z + lz,
    //    0.0f, 1.0f, 0.0f
    //);
    //printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", x, y, z, lx, ly, lz);
    Lock();
}

//================================================================

void KeySpecialDown4(int key, int x, int y) {
    switch (key)
    {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        orientMe(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        orientMe(angle);
        break;
    case GLUT_KEY_UP:
        moveMeFlat(1);
        break;
    case GLUT_KEY_DOWN:
        moveMeFlat(-1);
        break;
    }
}

void initScene4()
{
    glEnable(GL_DEPTH_TEST);
    //snowman_display_list = createDL(); // initmain ���� �̵�
    angle = 0.0;
    x = 0.0f, y = 1.75f, z = 5.0f;
    lx = 0.0f, ly = 0.0f, lz = -1.0f;

    //lx = sin(ang);
    //lz = -cos(ang);
    //x = x + direction * (lx) * 0.1;
    //z = z + direction * (lz) * 0.1;
    //glLoadIdentity();
    //gluLookAt(x, y, z,
    //    x + lx, y + ly, z + lz,
    //    0.0f, 1.0f, 0.0f);
    //printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", x, y, z, lx, ly, lz);
    Lock();
}

void renderScene4(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ������ �׸��ϴ�.
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // 36���� ������� �׸��ϴ�.
    for (int i = -3; i < 3; i++)
        for (int j = -3; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            glCallList(snowman_display_list);;
            glPopMatrix();
        }
    glutSwapBuffers();
}

void drawSnowMan()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    // ���� �׸��ϴ�.
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

    // �Ӹ��� �׸��ϴ�.
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    // �� ���� �׸��ϴ�.
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    // �ڸ� �׸��ϴ�.
    glColor3f(1.0f, 0.5f, 0.5f);
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}

GLuint createDL()
{
    GLuint snowManDL;

    // ���÷��̸���Ʈ�� �����ϰ� id �� ��ȯ�մϴ�.
    snowManDL = glGenLists(1);

    // ���÷��̸���Ʈ�� �����մϴ�.
    glNewList(snowManDL, GL_COMPILE);

    // �������� �����ϴ� �Լ��� ȣ���մϴ�.
    drawSnowMan();

    // ���÷��̸���Ʈ�� ����Ĩ�ϴ�.
    glEndList();

    return(snowManDL);
}

void orientMe(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);
    //glLoadIdentity();
    //gluLookAt(x, y, z,
    //    x + lx, y + ly, z + lz,
    //    0.0f, 1.0f, 0.0f);
    //printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", x, y, z, lx, ly, lz);
    Lock();
}

void moveMeFlat(int direction)
{
    x = x + direction * (lx) * 0.1;
    z = z + direction * (lz) * 0.1;
    Lock();
}



//================================================================
//================================================================















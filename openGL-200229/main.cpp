#include <gl/glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"
#include "CScene.cpp"
#include "CScene3.cpp"
#include "CScene4.cpp"
#include <iostream>
using namespace std;

//==============================================================

//typedef void (*renderScene)(); // = NULL;
//typedef void (*initScene)(); // = NULL;
//typedef void (*doDisplay)(); // = NULL;
//typedef void (*doIdle)(); // = NULL;

CScene* sf1, * sf2, * sf3;
void (CScene::* sm)(void);
CScene* sf;

static int s_mod = '3'; // ��� ��� �⺻��

enum Menu : int
{
    S1,
    S2,
    S3
};

//==============================================================

void doDisplay();
void doIdle();

void ChgWinSize(int w, int h);

void KeyUp(unsigned char key, int x, int y);
void KeyDown(unsigned char key, int x, int y);
void KeySpecialUp(int key, int x, int y);
void KeySpecialDown(int key, int x, int y);
void MouseDown(int button, int state, int x, int y);

void initMain();

void setScene();

void KeySpecialDown(int key, int x, int y);
void KeySpecialUp(int key, int x, int y);

//==============================================================

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


    // Sub menu
    GLint SubMenu = glutCreateMenu(doMenu);
    glutAddMenuEntry("Red", 4);
    glutAddMenuEntry("Green", 5);
    glutAddMenuEntry("Blue", 6);

    // Menu
    glutCreateMenu(doMenu);
    glutAddMenuEntry("White", 1);
    glutAddMenuEntry("Black", 2);
    glutAddMenuEntry("Gray", 3);

    // Add sub menu
    glutAddSubMenu("Triangle Color", SubMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    initMain();
    sf->initScene();

    glutAttachMenu(GLUT_RIGHT_BUTTON);  // ������ ��ư�� ������ �޴�����

    glutKeyboardFunc(KeyDown);          // Ű���� �Է� �Լ�.
    glutKeyboardUpFunc(KeyUp);          //

    glutSpecialFunc(KeySpecialDown);
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutDisplayFunc(doDisplay);         // ȭ��ǥ���Լ�.
    glutIdleFunc(doIdle);          //�޸�(idle)�ð��� ȣ��� �Լ��� �����Ѵ�.



    glEnable(GL_DEPTH_TEST);   //���� �˻簡 �����ϵ��� �����Ѵ�.

    glutReshapeFunc(ChgWinSize);     // ������ ũ�� ����� ����

    glutMainLoop();                     // ���η���

    return 0;
}

void initMain() {

    cout << &sf << endl; // 005EB140 sf ��ü �ּ�
    cout << *(&sf) << endl; // 005EB140 sf�� ����Ű�� �ּ�
    sf1 = new CScene1( sf);
    sf = sf1;
    cout << &sf << endl; // 005EB140
    cout << *(&sf) << endl; // 005EB140
    sf2 = new CScene2(sf);
    sf3 = new CScene3(sf);
       
    setScene();
}

void setScene()
{

    switch (s_mod) {
    case '1':
        sf = sf1;
        break;
    case '2':
        sf = sf2;
        break;
    case '3':
        sf = sf3;
        break;
    }

    //cout << &sf3 << endl; // 005EB140
    //cout << *(&sf3) << endl; // 005EB140
    //cout << sizeof(sf) << endl; // 8
}

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
        setScene();
        sf->initScene();
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
        printf("default ");
        sf->KeyDown(key,x,y);
    }
    glutPostRedisplay(); // ȭ�� �����
}

void KeyUp(unsigned char key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeyUp : %c , %d : %d , %d \n", key, k_mod, x, y);
    sf->KeyDown(key, x, y);
}

void KeySpecialDown(int key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeySpecialDown main : %d , %d : %d , %d \n", key, k_mod, x, y);
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
    sf->KeySpecialDown(key, x, y);
    //glutPostRedisplay(); // ȭ�� �����
}

void KeySpecialUp(int key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeySpecialUp : %d , %d : %d , %d \n", key, k_mod, x, y);
    //��:100
    //��:101
    //��:102
    //��:103
    sf->KeySpecialUp(key, x, y);
}

void MouseDown(int button, int state, int x, int y)
{
    printf("Mouse : %d , %d : %d , %d \n", button, state, x, y);
    // 1:�ٿ� , 2:��
    sf->MouseDown(button, state, x, y);
}

void doDisplay()
{
    sf->doDisplay();
}

void doIdle()
{
    sf->doIdle();
}
void doMenu(int value)
{
    cout << "doMenu main :" + value << endl;
    //switch (value) {
    //case 1:
    //    s_mod = '1';
    //    break;
    //case 2:
    //    s_mod = '2';
    //    break;
    //case 3:
    //    s_mod = '3';        
    //    break;
    //}

    //setScene();
    //sf->doMenu(value);
    //sf->initScene();
    //glutPostRedisplay(); // ȭ�� �����
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
    sf->Lock();
}

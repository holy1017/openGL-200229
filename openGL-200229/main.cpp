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

static int s_mod = '3'; // 장면 모드 기본값

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

    glutInit(&argc, argv);              // 초기화


    //glutInitDisplayMode();
    //glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT DEPTH);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    //  아래는 미리 정의되어 있는 색상 모델(color model)의 상수입니다.
    //
    //    GLUT_RGBA 또는 GLUT_RGB - RGBA 창을 만듭니다.이 값은 glut 가 사용하는 기본 색상 모드입니다.
    //    GLUT_INDEX - 인덱스 색상 모드로 설정합니다.
    //
    //    디스플레이 모드는 단일버퍼 창을 만들 것인지 아니면 이중버퍼 창을 만들 것인지 결정하는 것인데, 아래에 설정할 수 있는 상수가 있습니다.:
    //    GLUT_SINGLE - 단일버퍼(single buffer) 창을 마든다.
    //    GLUT_DOUBLE - 이중버퍼(double buffer) 창을 만든다.부드러운 에니메이션을 만들 때 필요합니다.
    //
    //    그리고 여러분이 원한다면 특정 버퍼로 설정된 창을 만들 수 있습니다.아래는 가장 많이 설정하는 버퍼입니다. :
    //    GLUT_ACCUM - 어큐뮬레이션 버퍼(The accumulation buffer)
    //    GLUT_STENCIL - 스텐실 버퍼(The stencil buffer)
    //    GLUT_DEPTH - 깊이 버퍼(The depth buffer)

    glutCreateWindow("OpenGL");         // 윈도우 만들기.
    glutInitWindowPosition(100, 100);   // 화면 초기 위치
    glutInitWindowSize(w_w, w_h);       // 화면 크기


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

    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 오른쪽 버튼을 누르면 메뉴생성

    glutKeyboardFunc(KeyDown);          // 키보드 입력 함수.
    glutKeyboardUpFunc(KeyUp);          //

    glutSpecialFunc(KeySpecialDown);
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutDisplayFunc(doDisplay);         // 화면표시함수.
    glutIdleFunc(doIdle);          //휴면(idle)시간에 호출될 함수를 설정한다.



    glEnable(GL_DEPTH_TEST);   //깊이 검사가 가능하도록 설정한다.

    glutReshapeFunc(ChgWinSize);     // 윈도우 크기 변경시 대응

    glutMainLoop();                     // 메인루프

    return 0;
}

void initMain() {

    cout << &sf << endl; // 005EB140 sf 자체 주소
    cout << *(&sf) << endl; // 005EB140 sf가 가리키는 주소
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

void KeyDown(unsigned char key, int x, int y) // q, a를 눌렀을 때 알파값 변경
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
    glutPostRedisplay(); // 화면 재생성
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
    //←:100
    //↑:101
    //→:102
    //↓:103
    //    GLUT_KEY_F1            F1 키
    //    GLUT_KEY_F2            F2 키
    //    GLUT_KEY_F3            F3 키
    //    GLUT_KEY_F4            F4 키
    //    GLUT_KEY_F5            F5 키
    //    GLUT_KEY_F6            F6 키
    //    GLUT_KEY_F7            F7 키
    //    GLUT_KEY_F8            F8 키
    //    GLUT_KEY_F9            F9 키
    //    GLUT_KEY_F10        F10 키
    //    GLUT_KEY_F11        F11 키
    //    GLUT_KEY_F12        F12 키
    //    GLUT_KEY_LEFT        왼쪽 방향키(←)
    //    GLUT_KEY_RIGHT        오른쪽 방향키(→)
    //    GLUT_KEY_UP            위쪽 방향키(↑)
    //    GLUT_KEY_DOWN        아래쪽 방향키(↓)
    //    GLUT_KEY_PAGE_UP    Page Up 키
    //    GLUT_KEY_PAGE_DOWN    Page Down 키
    //    GLUT_KEY_HOME        Home 키
    //    GLUT_KEY_END        End 키
    //    GLUT_KEY_INSERT        Insert 키    
    sf->KeySpecialDown(key, x, y);
    //glutPostRedisplay(); // 화면 재생성
}

void KeySpecialUp(int key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeySpecialUp : %d , %d : %d , %d \n", key, k_mod, x, y);
    //←:100
    //↑:101
    //→:102
    //↓:103
    sf->KeySpecialUp(key, x, y);
}

void MouseDown(int button, int state, int x, int y)
{
    printf("Mouse : %d , %d : %d , %d \n", button, state, x, y);
    // 1:다운 , 2:업
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
    //glutPostRedisplay(); // 화면 재생성
}


void ChgWinSize(int w, int h)
{
    printf("changeSize : %d , %d \n", w, h);

    //https://skyfe79.gitbooks.io/glut-tutorials/chapter3.html
    //창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
    if (h == 0)
        h = 1;

    w_h = h;
    w_w = w;

    ratio = 1.0f * w / h;

    //좌표계를 수정하기 전에 초기화합니다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //뷰포트를 창의 전체 크기로 설정합니다.
    glViewport(0, 0, w, h);

    //투시값을 설정합니다.
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


#include <gl/glut.h>
#include <stdio.h>

void DoDisplay();
void ChangeWinSize(int w, int h);
void KeyDown(unsigned char key, int x, int y);
void MouseDown(int button, int state, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void KeySpecialUp(int key, int x, int y);
void DoMenu(int value);

GLfloat Alpha = 0.1f;
GLenum Src = GL_SRC_ALPHA;
GLenum Dest = GL_ONE_MINUS_SRC_ALPHA;
GLfloat f_x = 0.0, f_y = 0.0;

int main(int argc, char** argv)
{
    glutInit(&argc, argv);              // 초기화

    glutCreateWindow("OpenGL");         // 윈도우 만들기.
    glutDisplayFunc(DoDisplay);         // 화면표시함수.
    //glutInitDisplayMode();
    //glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT DEPTH);
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

    glutInitWindowPosition(100, 100);   // 화면 초기 위치
    glutInitWindowSize(320, 320);       // 화면 크기
    glutReshapeFunc(changeWinSize);     // 윈도우 크기 변경시 대응

    glutKeyboardFunc(KeyDown);          // 키보드 입력 함수.
    glutKeyboardUpFunc(KeyUp);          //
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutCreateMenu(DoMenu);             // 메뉴 생성 함수
    glutAddMenuEntry("Opaque", 1);      // 메뉴 엔트리 1
    glutAddMenuEntry("Traslucent", 2);  // 메뉴 엔트리 2
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 오른쪽 버튼을 누르면 메뉴생성

    glutMainLoop();                     // 메인루프

    return 0;
}

void renderScene1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();
    glFlush();
    //glutPostRedisplay(); // 화면 재생성
}

// extern void APIENTRY glutKeyboardUpFunc(void (*func)(unsigned char key, int x, int y));
// extern void APIENTRY glutSpecialUpFunc(void (*func)(int key, int x, int y));

void KeyUp(unsigned char key, int x, int y)
{
    printf("KeyUp : %c : %d , %d \n", key, x, y);
}
void KeySpecialUp(int key, int x, int y)
{
    printf("SpecialUp : %d : %d , %d \n", key, x, y);
    //←:100
    //↑:101
    //→:102
    //↓:103
}
void MouseDown(int button, int state, int x, int y)
{
    printf("Mouse : %d , %d : %d , %d \n", button, state, x, y);
    // 1:다운 , 2:업
}

void KeyDown(unsigned char key, int x, int y) // q, a를 눌렀을 때 알파값 변경
{
    // 좌상단이 기준
    printf("key : %c : %d , %d \n", key, x, y);
    // teb,
    switch (key) {
    case 'q':
        if (Alpha < 1.0)
            Alpha += 0.1;
        break;
    case 'a':
        if (Alpha > 0.0)
            Alpha -= 0.1;
        break;
    case '1':
        renderScene1();
        break;
    case 'd':
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    }
    printf("Alpha : %f : %X \n", Alpha, &Alpha);
    glutPostRedisplay(); // 화면 재생성
}

void changeWinSize(int w, int h)
{
    printf("changeSize : %d , %d \n", w, h);

    //https://skyfe79.gitbooks.io/glut-tutorials/chapter3.html
    //창이 아주 작을 때, 0 으로 나누는 것을 예방합니다.
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;

    //좌표계를 수정하기 전에 초기화합니다.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //뷰포트를 창의 전체 크기로 설정합니다.
    glViewport(0, 0, w, h);

    //투시값을 설정합니다.
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
}

void DoMenu(int value)
{
    switch (value) {
    case 1:
        Src = GL_ONE;
        Dest = GL_ZERO;
        break;
    case 2:
        Src = GL_SRC_ALPHA;
        Dest = GL_ONE_MINUS_SRC_ALPHA;
        break;
    }
    glutPostRedisplay();
}

void DoDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);                        // 정점의 색은 빨간색
    glPointSize(10.0);                     // 점의 크기는 10

    glBegin(GL_POINTS);                // 점만 찍어낸다.
    glVertex2f(0.0, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    glFlush();


    glColor3f(1, 0, 0);

    glLineWidth(10.0);                    // 너비 10짜리 선

    glBegin(GL_LINE_LOOP);         // 삼각형

    glVertex2f(0.0, 0.25);

    glVertex2f(-0.25, -0.25);

    glVertex2f(0.25, -0.25);

    glEnd();

    glFlush();


    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);

    glBegin(GL_TRIANGLES);

    GLfloat x = -0.8;

    GLfloat y = 0.4;

    for (int i = 0; i < 6; i++) {

        glVertex2f(x, y);

        x += 0.3;

        y *= -1;                       // +1과 -1의 반복 (곱하기니까)

    }

    glEnd();

    glFlush();



}


//출처: https://wonjayk.tistory.com/33?category=535168 [배고파서 까먹고 만든 블로그]


// 출처: https://wonjayk.tistory.com/34?category=535168 [배고파서 까먹고 만든 블로그]

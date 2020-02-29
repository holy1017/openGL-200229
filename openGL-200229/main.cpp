#include <gl/glut.h>
#include <stdio.h>

void DoDisplay();
void ChgWinSize(int w, int h);
void KeyDown(unsigned char key, int x, int y);
void MouseDown(int button, int state, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void KeySpecialUp(int key, int x, int y);
void KeySpecialDown(int key, int x, int y);
void DoMenu(int value);
void renderScene1();
void renderScene2();
void renderScene3();
void DoIdle();

GLfloat f_x = 0.0, f_y = 0.0;
GLint   s_mod = '3'  ;
GLint   i_x=0 , i_y = 0 ;
GLint   w_w=300 , w_h = 400 ;

GLfloat Alpha = 0.1f;
GLenum Src = GL_SRC_ALPHA;
GLenum Dest = GL_ONE_MINUS_SRC_ALPHA;
float angle = 0.0;
float red = 1.0, blue = 1.0, green = 1.0;

int k_mod;

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
    glutReshapeFunc(ChgWinSize);     // 윈도우 크기 변경시 대응

    glutDisplayFunc(DoDisplay);         // 화면표시함수.
    glutIdleFunc(DoIdle);          //휴면(idle)시간에 호출될 함수를 설정한다.

    glutKeyboardFunc(KeyDown);          // 키보드 입력 함수.
    glutKeyboardUpFunc(KeyUp);          //

    glutSpecialFunc(KeySpecialDown);
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutCreateMenu(DoMenu);             // 메뉴 생성 함수
    glutAddMenuEntry("renderScene1", 1);      // 메뉴 엔트리 1
    glutAddMenuEntry("renderScene2", 2);  // 메뉴 엔트리 2
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // 오른쪽 버튼을 누르면 메뉴생성


    glEnable(GL_DEPTH_TEST);   //깊이 검사가 가능하도록 설정한다.

    glutMainLoop();                     // 메인루프

    return 0;
}
//================================================================
void KeyDown(unsigned char key, int x, int y) // q, a를 눌렀을 때 알파값 변경
{
    k_mod = glutGetModifiers();
    printf("KeyDown : %c , %d : %d , %d \n", key, k_mod, x, y);
    switch (key) {
    case '1':
    case '2':
    case '3':
        s_mod = key;
        printf("mod : %d \n", s_mod);
        break;
    case 'a' :
        if (k_mod == GLUT_ACTIVE_SHIFT)
            printf("");
        break;
    case 'd':
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    default :
            printf("");
    }
    glutPostRedisplay(); // 화면 재생성
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
    glutPostRedisplay(); // 화면 재생성
}
void KeySpecialUp(int key, int x, int y)
{
    k_mod = glutGetModifiers();
    printf("KeySpecialUp : %d , %d : %d , %d \n", key, k_mod, x, y);
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

//================================================================

void DoDisplay()
{
    switch (s_mod) {
    case '1':
        renderScene1();
        break;    
    case '2':
        renderScene2();
        break;
    case '3':
        renderScene3();
        break;
    case 'd':
        
        break;
    default:

        printf("DoDisplay : %d \n", s_mod);
    }
}
void DoIdle()
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
    glutPostRedisplay(); // 화면 재생성
}
//================================================================

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
void renderScene2()
{
    printf("renderScene2\n");
    // 깊이 버퍼를 깨끗이 지워야합니다.
    // 깊이 버퍼가 꽉차있으면 아무것도 그려지지 않기 때문이죠. 
    // 아래는 깊이버퍼를 지워주는 코드입니다.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 이전에 설정한 것들을 저장합니다.
    // 여기서는 카메라의 설정을 저장합니다.
    glPushMatrix();

    // angle 변수값을 회전량으로 y 축(0, 1, 0)을 중심으로 회전변환을 수행합니다. 
    glRotatef(angle, 0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.0, 0.0);
    glVertex3f(0.0, 0.5, 0.0);
    glEnd();

    // 모델링 변환을 마치고나서
    // 카메라설정을 원래대로 돌려놓습니다.
    glPopMatrix();

    // 위에서 그린것을 보여주기 위해서 버퍼를 교체합니다.
    glutSwapBuffers();

    // 마지막으로 angle 변수에 1 을 더해줍니다.
    angle++;
}

void renderScene3(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.0, 1.0, 0.0);
    // 여기서 실제 색을 설정합니다.
    // glColor 는 앞으로 그려질 물체들의 색을 결정합니다.
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
    w_h = h;
    w_w = w;

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
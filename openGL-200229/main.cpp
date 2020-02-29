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
    glutReshapeFunc(ChgWinSize);     // ������ ũ�� ����� ����

    glutDisplayFunc(DoDisplay);         // ȭ��ǥ���Լ�.
    glutIdleFunc(DoIdle);          //�޸�(idle)�ð��� ȣ��� �Լ��� �����Ѵ�.

    glutKeyboardFunc(KeyDown);          // Ű���� �Է� �Լ�.
    glutKeyboardUpFunc(KeyUp);          //

    glutSpecialFunc(KeySpecialDown);
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutCreateMenu(DoMenu);             // �޴� ���� �Լ�
    glutAddMenuEntry("renderScene1", 1);      // �޴� ��Ʈ�� 1
    glutAddMenuEntry("renderScene2", 2);  // �޴� ��Ʈ�� 2
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // ������ ��ư�� ������ �޴�����


    glEnable(GL_DEPTH_TEST);   //���� �˻簡 �����ϵ��� �����Ѵ�.

    glutMainLoop();                     // ���η���

    return 0;
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
    glutPostRedisplay(); // ȭ�� �����
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
    w_h = h;
    w_w = w;

    //https://skyfe79.gitbooks.io/glut-tutorials/chapter3.html
    //â�� ���� ���� ��, 0 ���� ������ ���� �����մϴ�.
    if (h == 0)
        h = 1;
    float ratio = 1.0 * w / h;

    //��ǥ�踦 �����ϱ� ���� �ʱ�ȭ�մϴ�.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //����Ʈ�� â�� ��ü ũ��� �����մϴ�.
    glViewport(0, 0, w, h);

    //���ð��� �����մϴ�.
    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
}
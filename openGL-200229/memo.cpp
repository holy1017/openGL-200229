
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
    glutInit(&argc, argv);              // �ʱ�ȭ

    glutCreateWindow("OpenGL");         // ������ �����.
    glutDisplayFunc(DoDisplay);         // ȭ��ǥ���Լ�.
    //glutInitDisplayMode();
    //glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT DEPTH);
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

    glutInitWindowPosition(100, 100);   // ȭ�� �ʱ� ��ġ
    glutInitWindowSize(320, 320);       // ȭ�� ũ��
    glutReshapeFunc(changeWinSize);     // ������ ũ�� ����� ����

    glutKeyboardFunc(KeyDown);          // Ű���� �Է� �Լ�.
    glutKeyboardUpFunc(KeyUp);          //
    glutSpecialUpFunc(KeySpecialUp);       //
    glutMouseFunc(MouseDown);           //

    glutCreateMenu(DoMenu);             // �޴� ���� �Լ�
    glutAddMenuEntry("Opaque", 1);      // �޴� ��Ʈ�� 1
    glutAddMenuEntry("Traslucent", 2);  // �޴� ��Ʈ�� 2
    glutAttachMenu(GLUT_RIGHT_BUTTON);  // ������ ��ư�� ������ �޴�����

    glutMainLoop();                     // ���η���

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
    //glutPostRedisplay(); // ȭ�� �����
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

void KeyDown(unsigned char key, int x, int y) // q, a�� ������ �� ���İ� ����
{
    // �»���� ����
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
    glutPostRedisplay(); // ȭ�� �����
}

void changeWinSize(int w, int h)
{
    printf("changeSize : %d , %d \n", w, h);

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

    glColor3f(1, 0, 0);                        // ������ ���� ������
    glPointSize(10.0);                     // ���� ũ��� 10

    glBegin(GL_POINTS);                // ���� ����.
    glVertex2f(0.0, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    glFlush();


    glColor3f(1, 0, 0);

    glLineWidth(10.0);                    // �ʺ� 10¥�� ��

    glBegin(GL_LINE_LOOP);         // �ﰢ��

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

        y *= -1;                       // +1�� -1�� �ݺ� (���ϱ�ϱ�)

    }

    glEnd();

    glFlush();



}


//��ó: https://wonjayk.tistory.com/33?category=535168 [����ļ� ��԰� ���� ��α�]


// ��ó: https://wonjayk.tistory.com/34?category=535168 [����ļ� ��԰� ���� ��α�]

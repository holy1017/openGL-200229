#pragma once
#include <stdio.h>
#include <gl/glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//==============================================================


static GLfloat angle = 0.0, ratio;
static GLint   w_w = 300, w_h = 400; // �ػ�
static GLdouble x = 0.0f, y = 1.75f, z = 5.0f;
static GLdouble lx = 0.0f, ly = 0.0f, lz = -1.0f;

static float debug_f = 72.0;
static int k_mod, s_menu = 0;


//==============================================================

class CScene
{
public:
    //CScene* sf;
     CScene(CScene *s) {
        
    };
     CScene() {

    };


    int k_mod=0;
	//�����غ��� �߻�Ŭ������ �ؼ� ������ �ʿ���� ����
	//virtual void initScene() = 0;
	//virtual void renderScene() = 0;
	//virtual void doDisplay() = 0;
	//virtual void doIdle()=0;
	//virtual void KeyDown()=0;
	virtual void initScene() {
		printf("CScene initScene\n");
	}

	virtual void doDisplay() {
	};
	virtual void doIdle() {
	};
	virtual void KeyDown(unsigned char key, int x, int y)
	{
		k_mod = glutGetModifiers();
		printf("CScene KeyDown : %c , %d : %d , %d \n", key, k_mod, x, y);
	};
	virtual void KeyUp(unsigned char key, int x, int y)
	{
		k_mod = glutGetModifiers();
		printf("CScene KeyUp : %c , %d : %d , %d \n", key, k_mod, x, y);
	}

	virtual void Lock()
	{
		glLoadIdentity();
		gluLookAt(x, y, z,
			x + lx, y + ly, z + lz,
			0.0f, 1.0f, 0.0f);
		printf("CScene %lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", x, y, z, lx, ly, lz);
	}

    virtual void KeySpecialDown(int key, int x, int y)
    {
        k_mod = glutGetModifiers();
        printf("KeySpecialDown CScene: %d , %d : %d , %d \n", key, k_mod, x, y);
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

        glutPostRedisplay(); // ȭ�� �����
    }

    virtual void KeySpecialUp(int key, int x, int y)
    {
        k_mod = glutGetModifiers();
        printf("CScene KeySpecialUp : %d , %d : %d , %d \n", key, k_mod, x, y);
        //��:100
        //��:101
        //��:102
        //��:103

    }

    virtual void MouseDown(int button, int state, int x, int y)
    {
        printf("CScene Mouse : %d , %d : %d , %d \n", button, state, x, y);
        // 1:�ٿ� , 2:��
    }
    virtual void doMenu(int value)
    {
        //glutPostRedisplay(); // ȭ�� �����
    }
};


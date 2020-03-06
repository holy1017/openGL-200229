#include "CScene3.h"
#include "CScene.h"
#include <gl/glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

static GLint snowman_display_list;


class CScene3 : public CScene
{
public:

	enum eColor3 : int
	{
		Red,
		Green,
		Blue
	};


	int menu = 0;
	CScene* s;
	CScene3(CScene* sf) {
		cout << &sf << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&sf) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&s) << endl; // 005EB140 sf�� ����Ű�� �ּ�

	};

	static void doMenu(int v) {
		cout << "doMenu CScene3 :" + v << endl;
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

	void renderScene(void)
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

	void initScene() {

		snowman_display_list = createDL();
		angle = 0.0;
		x = 0.0f, y = 1.75f, z = 5.0f;
		lx = 0.0f, ly = 0.0f, lz = -1.0f;
		Lock();
	}


	// CScene��(��) ���� ��ӵ�
	 void doDisplay() 
	{
		 renderScene();
	}
	 void doIdle() 
	{
		 renderScene();
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

	// CScene��(��) ���� ��ӵ�
	void KeyDown(unsigned char key, int x, int y)
	{
	}

	virtual void KeySpecialDown(int key, int x, int y) {
		printf("KeySpecialDown CScene3: %d , %d : %d , %d \n", key, k_mod, x, y);
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
		glutPostRedisplay(); // ȭ�� �����
	}
};

#include "CScene.h"
#include <gl/glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

enum eColor1 : int
{
	Red,
	Green,
	Blue
};

class CScene1 : public CScene
{
public:



	int menu = 0;
	CScene* s = NULL;;
	CScene1(CScene* sf) {
		cout << &sf << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&sf) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&s) << endl; // 005EB140 sf�� ����Ű�� �ּ�

	};
	CScene1() {

	};

	void init() {

	}

	static void doMenu(int v) {
		cout << "doMenu CScene1 :"+v << endl;
	}

	virtual void initScene() {
		printf("CScene1 initScene\n");
		angle = 0.0, ratio;
		x = 0.0f, y = 0.0f, z = 5.0f;
		lx = 0.0f, ly = 0.0f, lz = -1.0f - z;
		//glLoadIdentity();
		//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
		Lock();
	}
	virtual void renderScene() {
		if (fmod(angle, debug_f)==0.0)
		{
			printf("renderScene CScene1 %f", angle);
		}		
		//printf("CScene1 renderScene\n");
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
	

	// CScene��(��) ���� ��ӵ�
	virtual void doDisplay()
	{
		 renderScene();
	}

	 virtual void doIdle()
	{
		 renderScene();
	}



};



class CScene2 : public CScene1
{
public:

	enum eColor : int
	{
		Red,
		Green,
		Blue
	};

	int menu = 0;
	CScene* s = NULL;;
	CScene2(CScene* sf) {
		cout << &sf << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&sf) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&s) << endl; // 005EB140 sf�� ����Ű�� �ּ�

	};
	CScene2() {

	};

	static void doMenu(int v) {
		cout << "doMenu CScene1 :" + v << endl;
	}


	GLfloat red = 1.0, blue = 1.0, green = 1.0;

	virtual void renderScene() {
		if (fmod(angle, debug_f) == 0.0)
		{
			printf("renderScene CScene2 %f", angle);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();
		glRotatef(angle, 1.0, 0.0, 0.0);
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



	virtual void KeySpecialDown(int key, int x, int y) {
		 printf("KeySpecialDown CScene2: %d , %d : %d , %d \n", key, k_mod, x, y);
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
};

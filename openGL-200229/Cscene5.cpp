#include "CScene.h"
#include <iostream>
#include <cstdio>
using namespace std;

class CScene5 : public CScene
{
public:

	GLfloat locationX = 0.0f, locationY = 0.0f;
	const GLfloat step = 0.02f;
	const GLfloat size = 0.2f;

	int menu = 0;
	CScene* s;
	CScene5(CScene* sf) {
		//cout << &sf << endl; // 005EB140 sf ��ü �ּ�
		//cout << *(&sf) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		menu = ++s_menu;
		s = sf;
		//cout << &s << endl; // 005EB140 sf ��ü �ּ�
		//cout << *(&s) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		//glutAddMenuEntry("Scene4", menu);
	};

	~CScene5()
	{
	}


	void initScene() {
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

		printf("CScene1 initScene\n");
		angle = 0.0, ratio;
		x = 0.0f, y = 0.0f, z = 5.0f;
		lx = 0.0f, ly = 0.0f, lz = -1.0f - z;
		//glLoadIdentity();
		//gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);
		Lock();
	}

	static void doMenu(int value)
	{
		cout << "doMenu main :" + value << endl;

		switch (value) {
		case 1:
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    // ��� ���

			break;
		case 2:
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    // ��� ������

			break;
		case 3:
			glClearColor(0.5f, 0.5f, 0.5f, 1.0f);    // ��� ȸ��

			break;
		case 4:
			glColor3f(1.0f, 0.0f, 0.0f);            // �ﰨ�� ������

			break;
		case 5:
			glColor3f(0.0f, 1.0f, 0.0f);            // �ﰨ�� ���

			break;
		case 6:
			glColor3f(0.0f, 0.0f, 1.0f);            // �ﰨ�� �Ķ���

			break;
		default:

			break;
		}

		glutPostRedisplay();
	}

	void KeyDown(unsigned char key, int x, int y)
	{
		k_mod = glutGetModifiers();
		printf("KeyDown CScene5 : %c , %d : %d , %d \n", key, k_mod, x, y);

		switch (key) {
		case 'r':
		case 'R':
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);    // ��� ������

			break;
		case 'g':
		case 'G':
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f);    // ��� ���

			break;
		case 'b':
		case 'B':
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);    // ��� �Ķ���

			break;
		case 27:
			glutDestroyWindow(winId);                // ESCŰ ���α׷� ����
			exit(0);

			break;
		default:

			break;
		}

		glutPostRedisplay();
	}
	void KeySpecialDown(int key, int x, int y)
	{
		k_mod = glutGetModifiers();
		printf("KeySpecialDown CScene5: %d , %d : %d , %d \n", key, k_mod, x, y);

		switch (key) {
		case GLUT_KEY_LEFT:        // step ��ŭ x����
			locationX -= step;

			break;
		case GLUT_KEY_RIGHT:    // step ��ŭ x����
			locationX += step;

			break;
		case GLUT_KEY_UP:        // step ��ŭ y����
			locationY += step;

			break;
		case GLUT_KEY_DOWN:        // step ��ŭ y����
			locationY -= step;

			break;
		}
		char title[128] = { 0, };
		sprintf_s(title, "Triangle location (%.2f, y=%.2f)", locationX, locationY);
		glutSetWindowTitle(title); // ����ǥ���ٿ� �ﰢ�� ��ǥ ǥ��

		glutPostRedisplay();
	}
	virtual void MouseDown(int button, int state, int x, int y)
	{
		printf("Mouse CScene5 : %d , %d : %d , %d \n", button, state, x, y);
		// 1:�ٿ� , 2:��

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			glColor3f(0.0f, 1.0f, 1.0f);    // �ﰢ�� �ϴû�
			char title[128] = { 0, };
			sprintf_s(title, "Click (x: %d, y: %d)", x, y);
			glutSetWindowTitle(title); // ����ǥ���ٿ� Ŭ�� ��ǥ ǥ��

			glutPostRedisplay();
		}
		else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			glColor3f(1.0f, 1.0f, 0.0f);    // �ﰢ�� �����

			glutPostRedisplay();
		}
	}
	virtual void doDisplay() {
		//printf("doDisplay CScene5 \n");

		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		glVertex2f(locationX, locationY + size);
		glVertex2f(locationX - size, locationY - size);
		glVertex2f(locationX + size, locationY - size);
		glEnd();

		//glFinish();
		glPopMatrix();
		glutSwapBuffers();
	};
	virtual void doIdle() {
		doDisplay();
	};
};
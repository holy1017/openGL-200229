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
		cout << &sf << endl; // 005EB140 sf 자체 주소
		cout << *(&sf) << endl; // 005EB140 sf가 가리키는 주소
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf 자체 주소
		cout << *(&s) << endl; // 005EB140 sf가 가리키는 주소

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
	

	// CScene을(를) 통해 상속됨
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
		cout << &sf << endl; // 005EB140 sf 자체 주소
		cout << *(&sf) << endl; // 005EB140 sf가 가리키는 주소
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf 자체 주소
		cout << *(&s) << endl; // 005EB140 sf가 가리키는 주소

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
		 glutPostRedisplay(); // 화면 재생성
	 }
};

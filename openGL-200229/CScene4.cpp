#include "CScene.h"
#include <iostream>
using namespace std;

class CScene4 : CScene
{

public:

	int menu = 0;
	CScene* s;
	CScene4(CScene* sf) {
		cout << &sf << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&sf) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf ��ü �ּ�
		cout << *(&s) << endl; // 005EB140 sf�� ����Ű�� �ּ�
		glutAddMenuEntry("Scene4", menu);
	};

	~CScene4()
	{
	}

private:

};

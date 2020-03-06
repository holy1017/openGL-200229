#include "CScene.h"
#include <iostream>
using namespace std;

class CScene4 : CScene
{

public:

	int menu = 0;
	CScene* s;
	CScene4(CScene* sf) {
		cout << &sf << endl; // 005EB140 sf 자체 주소
		cout << *(&sf) << endl; // 005EB140 sf가 가리키는 주소
		menu = ++s_menu;
		s = sf;
		cout << &s << endl; // 005EB140 sf 자체 주소
		cout << *(&s) << endl; // 005EB140 sf가 가리키는 주소
		glutAddMenuEntry("Scene4", menu);
	};

	~CScene4()
	{
	}

private:

};

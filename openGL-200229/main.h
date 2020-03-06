#pragma once
int main(int argc, char** argv);

//void doDisplay();
//void doIdle();
void doMenu(int value);

void initMain();
//void initScene();

void setScene();

void ChgWinSize(int w, int h);

void KeyUp(unsigned char key, int x, int y);
void KeyDown(unsigned char key, int x, int y);
void KeySpecialUp(int key, int x, int y);
void KeySpecialDown(int key, int x, int y);
void MouseDown(int button, int state, int x, int y);
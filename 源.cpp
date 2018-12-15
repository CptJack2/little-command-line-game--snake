#include <iostream>
#include <windows.h>
#include <conio.h>
#include<stdlib.h>
#include"GlobalSettings.h"
#include"snake.h"
#include<time.h>
#include<thread>
#include<set>
using namespace std;

snake s;

void DrawFrame() {
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	for (int i = 0; i <=GlobalSettings::area_width+1; i++)
		cout << "��";
	for (int j = 0; j <= GlobalSettings::area_height+1;j++){
		csbiInfo.dwCursorPosition.X = 0;
		csbiInfo.dwCursorPosition.Y = j;
		SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
		cout << "��";
		csbiInfo.dwCursorPosition.X = 2*GlobalSettings::area_width+2;
		SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
		cout << "��";
	}
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = GlobalSettings::area_height+1;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
	for (int i = 0; i <= GlobalSettings::area_width+1; i++)
		cout << "��";
	cout << endl;
}

void gotoxy(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
} 

void DisplaySnake(snake& snake) {
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	//�����β
	pair<int,int> t = s.body.back();
	csbiInfo.dwCursorPosition.X = t.second*2+2;
	csbiInfo.dwCursorPosition.Y = t.first+1;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
	cout << " ";
	//ʹ���ƶ�
	s.move();
	s.judgealive();
	//��������ͷ
	t = s.body.front();
	csbiInfo.dwCursorPosition.X = t.second * 2 + 2;
	csbiInfo.dwCursorPosition.Y = t.first + 1;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
	cout << "��";
}
void DisplayFood() {
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	for (set<pair<int, int>>::iterator i = s.foods.begin(); i != s.foods.end();i++) {
		csbiInfo.dwCursorPosition.X = (*i).second * 2+2;
		csbiInfo.dwCursorPosition.Y = (*i).first+1;
		SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
		cout << "��";
	}
}

void dispthread() {
	while (1) {
		if(s.is_alive){
			Sleep(GlobalSettings::timer_interval);
			DisplaySnake(s);
			//if (s.foods.empty())
			s.addfood();
			DisplayFood();}
	}
}
int main(void)
{
	DrawFrame();
	//snake s;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	//������
	for (auto i = s.body.begin(); i != s.body.end(); i++) {
		csbiInfo.dwCursorPosition.X = (*i).second*2+2;
		csbiInfo.dwCursorPosition.Y = (*i).first+1;
		SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
		cout << "��";
	}
	//DisplaySnake(s);
	thread t(dispthread);
	while (1) {
		if (_kbhit()) {//����а������£���_kbhit()����������
			int ch = _getch();//ʹ��_getch()������ȡ���µļ�ֵ
			//cout << ch;
			switch (ch) {
			case 'w':
				s.goup();
				break;
			case 's':
				s.godown();
				break;
			case 'a':
				s.goleft();
				break;
			case 'd':
				s.goright();
				break;
			case 'u':
				if (!s.is_alive){
					//����
					CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
					HANDLE hConsoleOut;
					hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
					GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
					for (int i = 0; i <= GlobalSettings::area_height + 1; i++){
						csbiInfo.dwCursorPosition.X = 0;
						csbiInfo.dwCursorPosition.Y = i;
						SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
						for (int j = 0; j <= 2*GlobalSettings::area_height + 2; j++) {
							cout << " ";
					}}
					//�ػ���
					csbiInfo.dwCursorPosition.X = 0;
					csbiInfo.dwCursorPosition.Y = 0;
					SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
					DrawFrame();
					s.reset();
				}
				break;
			case 'p':
				if (!s.is_alive) {
					s.body.pop_front();
					s.is_alive = true;
				}
				break;
			}
			//Sleep(100);//��ֹ����̫��		
		}
	}
	return 0;
}
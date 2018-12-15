#pragma once
#include<deque>
#include<set>
using namespace std;
class snake {
public:
	snake();
	deque<pair<int, int>> body;
	set<pair<int, int>> foods;
	int direction=2;//1,2,3,4,иообвСср
	void goup();
	void godown();
	void goleft();
	void goright();
	void move();
	void addfood();
	bool is_alive=true;
	bool judgealive();
	void reset();
	int proper_foodnum=35;
};
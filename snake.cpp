#include"snake.h"
#include"GlobalSettings.h"
#include<ctime>

snake::snake() {
	reset();
}
void snake::goup() {
	pair<int, int> first=body.front(),
		first2= *(body.begin() + 1);
	if (first.first == first2.first + 1)
		return;
	direction = 1;
}
void snake::godown() {
	pair<int, int> first = body.front(),
		first2 = *(body.begin() + 1);
	if (first.first == first2.first -1 )
		return;
	direction = 2;
}
void snake::goright() {
	pair<int, int> first = body.front(),
		first2 = *(body.begin() + 1);
	if (first.second == first2.second- 1)
		return;
	direction = 4;
}
void snake::goleft() {
	pair<int, int> first = body.front(),
		first2 = *(body.begin() + 1);
	if (first.second == first2.second+ 1)
		return;
	direction = 3;
}
void snake::move() {
	pair<int,int> t = body.front();
	switch (direction)	{
	case 3:
		t.second--;
		break;
	case 4:
		t.second++;
		break;
	case 1:
		t.first--;
		break;
	case 2:
		t.first++;
		break;
	}
	body.push_front(t);
	auto it = foods.find(t);
	//≥‘ ≥≤ø∑÷
	if(it!=foods.end())
		foods.erase(it);
	else
		body.pop_back();
	//if(t.first<0 || )
}
void snake::addfood() {
	srand(int(time(0)));
	for (int i = foods.size(); i < proper_foodnum;i++){
		int x=rand() % GlobalSettings::area_height;
		int y = rand() % GlobalSettings::area_width;
		foods.insert(pair<int, int>(x, y));}
}
bool snake::judgealive() {
	pair<int, int> head = body.front();
	if (head.first < 0 || head.first >= GlobalSettings::area_height ||
		head.second < 0 || head.second >= GlobalSettings::area_width){ 
		is_alive = false;
		return false;}
	for (auto i = body.begin()+1; i != body.end(); i++) {
		if (head.first == (*i).first && head.second == (*i).second){
			is_alive = false;
			return false;}
	}
	return true;
}
void snake::reset() {
	body.clear();
	int y = GlobalSettings::area_width / 2,
		x = GlobalSettings::area_height / 2;
	body.push_back(pair<int, int>(x, y));
	body.push_back(pair<int, int>(x - 1, y));
	body.push_back(pair<int, int>(x - 2, y));
	
	direction = 2;
	foods.clear();
	is_alive = true;
	//proper_foodnum = GlobalSettings::area_height*GlobalSettings::area_width/160;
}
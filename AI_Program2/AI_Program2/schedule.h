#pragma once
#include <string>
#include <functional>
using namespace std;

class schedule {
public:
	schedule(string c, string t, string p, string r);
	string courseNum;
	string time;
	string professor;
	string room;
	string get_course();
	string get_time();
	string get_professor();
	string get_room();
	void set_course(string c);
	void set_time(string t);
	void set_professor(string p);
	void set_room(string r);

};
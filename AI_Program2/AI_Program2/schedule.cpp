#include "schedule.h"

schedule::schedule(string c, string t, string p, string r) {
	courseNum = c;
	time = t;
	professor = p;
	room = r;
}

//getters and setters for all the course information
string schedule::get_course() { return courseNum; }
string schedule::get_time() { return time; }
string schedule::get_professor() { return professor; }
string schedule::get_room() { return room; }
void schedule::set_course(string c) { courseNum = c; }
void schedule::set_time(string t) { time = t; }
void schedule::set_professor(string p) { professor = p; }
void schedule::set_room(string r) { room = r; }

#include "fitnessFunction.h"
#include <iostream>
using namespace std;

//default constructor that takes in a vector of schedules
//and calls all the fitness functions using that schedule to set the fitness score
fitnessFunction::fitnessFunction(vector<schedule> s) {
	validProfessor(s);
	validRoomSize(s);
	professorSameClassTimes(s);
	tooManyClasses(s);
	sameSemesterClasses(s);
	multisectionedClasses(s);
}

//returns true if the string s is found in the vector v
bool fitnessFunction::inVector(vector<string> v, string s) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == s) {
			return true;
		}
	}
	return false;
}

//returns the index of s for where it is found in v
int fitnessFunction::findIndex(vector<string> v, string s) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == s) {
			return i;
		}
	}
	return -1;
}

//checks to make sure that each class is taught by a professor that is able to teach that class
//if this is true then it adds 3 to the fitness score (or it adds 1 if it is taught by the staff)
void fitnessFunction::validProfessor(vector<schedule> s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i].get_professor() == "Hare") {
			if (inVector(Hare, s[i].get_course())) {
				fitnessScore += 3;
			}
		}
		else if (s[i].get_professor() == "Bingham") {
			if (inVector(Bingham, s[i].get_course())) {
				fitnessScore += 3;
			}
		}
		else if (s[i].get_professor() == "Kuhail") {
			if (inVector(Kuhail, s[i].get_course())) {
				fitnessScore += 3;
			}
		}
		else if (s[i].get_professor() == "Mitchell") {
			if (inVector(Mitchell, s[i].get_course())) {
				fitnessScore += 3;
			}
		}
		else if (s[i].get_professor() == "Rao") {
			if (inVector(Rao, s[i].get_course())) {
				fitnessScore += 3;
			}
		}
		else if (s[i].get_professor() == "Staff") {
			fitnessScore += 1;
		}
	}
}

//this function makes sure that no classes are in the same room at the same time as another class
//then it checks to make sure that each class is in a room that is big enough to accomodate it, but that the room is not too big
void fitnessFunction::validRoomSize(vector<schedule> s) {
	for (int i = 0; i < s.size(); i++) {
		int roomCount = 0;
		for (int j = 0; j < s.size(); j++) {
			if (s[i].get_room() == s[j].get_room() && s[i].get_time() == s[j].get_time()) {
				roomCount += 1;
			}
		}
		if (roomCount == 1) {
			fitnessScore += 5;
		}
	}
	for (int i = 0; i < s.size(); i++) {
		int courseIndex = findIndex(courses, s[i].get_course());
		int roomIndex = findIndex(rooms, s[i].get_room());
		if (courseCapacity[courseIndex] < roomCapacity[roomIndex]) {
			fitnessScore += 5;
			if ((courseCapacity[courseIndex]) * 2 >= roomCapacity[roomIndex]) {
				fitnessScore += 2;
			}
		}
	}
}

//checks to make sure that there are no classes being taught by the same professor at the same time
void fitnessFunction::professorSameClassTimes(vector<schedule> s) {
	for (int i = 0; i < s.size(); i++) {
		int profCount = 0;
		for (int j = 0; j < s.size(); j++) {
			if (s[i].get_professor() == s[j].get_professor() && s[i].get_time() == s[j].get_time()) {
				profCount += 1;
			}
		}
		if (profCount == 1) {
			fitnessScore += 5;
		}
	}
}

//checks if any professors are teaching more than 4 classes
//then it checks if Rao or Mitchell are teaching more classes than either Bingham or Hare
void fitnessFunction::tooManyClasses(vector<schedule> s) {
	int hareNum = 0;
	int bingNum = 0;
	int kuhailNum = 0;
	int mitchNum = 0;
	int raoNum = 0;
	int staffNum = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i].get_professor() == "Hare") {
			hareNum += 1;
		}
		else if (s[i].get_professor() == "Bingham") {
			bingNum += 1;
		}
		else if (s[i].get_professor() == "Kuhail") {
			kuhailNum += 1;
		}
		else if (s[i].get_professor() == "Mitchell") {
			mitchNum += 1;
		}
		else if (s[i].get_professor() == "Rao") {
			raoNum += 1;
		}
		else if (s[i].get_professor() == "Staff") {
			staffNum += 1;
		}
	}
	if (hareNum > 4) {
		fitnessScore -= ((hareNum - 4) * 5);
	}
	if (bingNum > 4) {
		fitnessScore -= ((bingNum - 4) * 5);
	}
	if (kuhailNum > 4) {
		fitnessScore -= ((kuhailNum - 4) * 5);
	}
	if (mitchNum > 4) {
		fitnessScore -= ((mitchNum - 4) * 5);
	}
	if (raoNum > 4) {
		fitnessScore -= ((raoNum - 4) * 5);
	}
	if (staffNum > 4) {
		fitnessScore -= ((staffNum - 4) * 5);
	}

	if (raoNum > hareNum || raoNum > bingNum || mitchNum > hareNum || bingNum) {
		fitnessScore -= 10;
	}
}

//checks if classes that are usually taken the same semester are scheduled at the same time or adjacent times
void fitnessFunction::sameSemesterClasses(vector<schedule> s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i].get_course() == "CS101A" || s[i].get_course() == "CS101B") { //iterates through each class until it finds CS101A or CS101B
			int iCourseTimeIndex = findIndex(times, s[i].get_time()); //keeps track of what that index is
			for (int j = 0; j < s.size(); j++) { //then iterates through each class again until it finds CS191A or CS191B
				if (s[j].get_course() == "CS191A" || s[j].get_course() == "CS191B") {
					if (s[i].get_time() == s[j].get_time()) { //if theyre at the same time subtract 15 from the score
						fitnessScore -= 15;
					}
					int jCourseTimeIndex = findIndex(times, s[j].get_time()); //keep track of the second class index
					if (iCourseTimeIndex == jCourseTimeIndex + 1 || iCourseTimeIndex == jCourseTimeIndex - 1) { 
						fitnessScore += 5; //if the index is 1 more or 1 less then they are adjacent times and add 5 to the score
						if (s[i].get_room() == s[j].get_room()) { //if theyre in the same building add 5 again
							fitnessScore += 5;
						}
						if ((s[i].get_room() == "Katz209" && s[j].get_room() != "Katz209") || 
							(s[j].get_room() == "Katz209" && s[i].get_room() != "Katz209")) {
							fitnessScore -= 3; //if one is in Katz and the other is not then subtract 3
						}
						if ((s[i].get_room() == "Bloch0009" && s[j].get_room() != "Bloch0009") ||
							(s[j].get_room() == "Bloch0009" && s[i].get_room() != "Bloch0009")) {
							fitnessScore -= 3; //if one is in Bloch and the other is not subtract 3
						}
					}
				}
			}
		}
	}
	//repeat the same process but with CS201A/CS201B and CS291A/CS291B
	for (int i = 0; i < s.size(); i++) {
		if (s[i].get_course() == "CS201A" || s[i].get_course() == "CS201B") {
			int iCourseTimeIndex = findIndex(times, s[i].get_time());
			for (int j = 0; j < s.size(); j++) {
				if (s[j].get_course() == "CS291A" || s[j].get_course() == "CS291B") {
					if (s[i].get_time() == s[j].get_time()) {
						fitnessScore -= 15;
					}
					int jCourseTimeIndex = findIndex(times, s[j].get_time());
					if (iCourseTimeIndex == jCourseTimeIndex + 1 || iCourseTimeIndex == jCourseTimeIndex - 1) {
						fitnessScore += 5;
						if (s[i].get_room() == s[j].get_room()) {
							fitnessScore += 5;
						}
						if ((s[i].get_room() == "Katz209" && s[j].get_room() != "Katz209") ||
							(s[j].get_room() == "Katz209" && s[i].get_room() != "Katz209")) {
							fitnessScore -= 3;
						}
						if ((s[i].get_room() == "Bloch0009" && s[j].get_room() != "Bloch0009") ||
							(s[j].get_room() == "Bloch0009" && s[i].get_room() != "Bloch0009")) {
							fitnessScore -= 3;
						}
					}
				}
			}
		}
	}
}

//checks if the classes with multiple sections are scheduled far apart or not
//it tells how far apart they are based on the index of the time for each class
void fitnessFunction::multisectionedClasses(vector<schedule> s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i].get_course() == "CS101A") {
			int iTimeIndex = findIndex(times, s[i].get_time());
			for (int j = 0; j < s.size(); j++) {
				if (s[j].get_course() == "CS101B") {
					int jTimeIndex = findIndex(times, s[j].get_time());
					if (abs(iTimeIndex - jTimeIndex) >= 3) {
						fitnessScore += 5;
					}
				}
			}
		}
	 }
	for (int i = 0; i < s.size(); i++) {
		if (s[i].get_course() == "CS191A") {
			int iTimeIndex = findIndex(times, s[i].get_time());
			for (int j = 0; j < s.size(); j++) {
				if (s[j].get_course() == "CS191B") {
					int jTimeIndex = findIndex(times, s[j].get_time());
					if (abs(iTimeIndex - jTimeIndex) >= 3) {
						fitnessScore += 5;
					}
				}
			}
		}
	}
}
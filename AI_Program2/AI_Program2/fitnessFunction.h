#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "schedule.h"
using namespace std;

class fitnessFunction {
public:
	fitnessFunction(vector<schedule> s);
	int fitnessScore = 0;
	vector<string> Hare = { "CS101A", "CS101B", "CS201A", "CS201B", "CS291A", "CS291B", "CS303", "CS449", "CS461" };
	vector<string> Bingham = { "CS101A", "CS101B", "CS201A", "CS201B", "CS191A", "CS191B", "CS291A", "CS291B", "CS449" };
	vector<string> Kuhail = { "CS303", "CS431" };
	vector<string> Mitchell = { "CS191A", "CS191B", "CS291A", "CS291B", "CS303", "CS341" };
	vector<string> Rao = { "CS291A", "CS291B", "CS303", "CS341", "CS461" };
	vector<string> times = { "10A", "11A", "12P", "1P", "2P", "3P", "4P" };
	vector<string> rooms = { "Haag301", "Haag206", "Royall204", "Katz209", "Flarsheim310", "Flarsheim260", "Bloch0009" };
	vector<int> roomCapacity = { 70, 30, 70, 50, 80, 25, 30 };
	vector<string> courses = { "CS101A", "CS101B", "CS201A", "CS201B", "CS191A", "CS191B",
								"CS291B", "CS291A", "CS303", "CS341", "CS449", "CS461" };
	vector<int> courseCapacity = { 40, 25, 30, 30, 60, 20, 40, 20, 50, 40, 55, 40 };
	
	bool inVector(vector<string> v, string s); //returns true if s is in v, else false
	int findIndex(vector<string> v, string s); //returns the index of s if it is in v

	void validProfessor(vector<schedule> s); //bullet points 1 and 2 on the assignment description
	void validRoomSize(vector<schedule> s); //bullet points 3 and 4 on the assignment description
	void professorSameClassTimes(vector<schedule> s); //bullet point 5 on the assignment description
	void tooManyClasses(vector<schedule> s); //bullet points 6 and 7 on the assignment description
	void sameSemesterClasses(vector<schedule> s); //bullet point 8 on the assignment description
	void multisectionedClasses(vector<schedule> s); //bullet points 9 and 10 on the assignment description
};
#pragma once
#include "schedule.h"
#include "fitnessFunction.h"
#include <string>
#include <vector>
using namespace std;

class testClass {
public:
	testClass() {
		testValidProfessor();
		testValidRoomSize();
		testProfessorSameClassTimes();
		testTooManyClasses();
		testSameSemesterClasses();
		testMultisectionedClasses();
	}
	bool testValidProfessor() {
		vector<schedule> testVector;
		schedule testStaff("CS101A", "11A", "Hare", "Haag301");
		testVector.push_back(testStaff);
		fitnessFunction t(testVector);
		t.fitnessScore = 0;
		t.validProfessor(testVector);

		if (t.fitnessScore == 3) {
			cout << "validProfessor() is correct: " << t.fitnessScore << endl;
			return true;
		}
		cout << "validProfessor() is incorrect: " << t.fitnessScore << endl;
		return false;
	}

	bool testValidRoomSize() {
		vector<schedule> testVector;
		schedule testStaff("CS101A", "11A", "Hare", "Haag301");
		testVector.push_back(testStaff);
		schedule testStaff1("CS449", "12P", "Hare", "Haag301");
		testVector.push_back(testStaff1);
		fitnessFunction t(testVector);
		t.fitnessScore = 0;
		t.validRoomSize(testVector);

		if (t.fitnessScore == 24) {
			cout << "validRoomSize() is correct: " << t.fitnessScore << endl;
			return true;
		}
		cout << "validRoomSize() is incorrect: " << t.fitnessScore << endl;
		return false;
	}

	bool testProfessorSameClassTimes() {
		vector<schedule> testVector;
		schedule testStaff("CS101A", "11A", "Hare", "Haag301");
		testVector.push_back(testStaff);
		schedule testStaff1("CS449", "11A", "Bingham", "Royall204");
		testVector.push_back(testStaff1);
		fitnessFunction t(testVector);
		t.fitnessScore = 0;
		t.professorSameClassTimes(testVector);
		
		if (t.fitnessScore == 10) {
			cout << "professorSameClassTimes() is correct: " << t.fitnessScore << endl;
			return true;
		}
		cout << "professorSameClassTimes() is incorrect: " << t.fitnessScore << endl;
		return false;
	}
	

	bool testTooManyClasses() {
		vector<schedule> testVector;
		schedule testStaff("CS101A", "11A", "Rao", "Haag301");
		testVector.push_back(testStaff);
		schedule testStaff1("CS449", "12P", "Rao", "Haag301");
		testVector.push_back(testStaff1);
		schedule testStaff2("CS101A", "11A", "Rao", "Haag301");
		testVector.push_back(testStaff2);
		schedule testStaff3("CS449", "12P", "Mitchell", "Haag301");
		testVector.push_back(testStaff3);
		schedule testStaff4("CS449", "12P", "Hare", "Haag301");
		testVector.push_back(testStaff4);
		schedule testStaff5("CS449", "12P", "Hare", "Haag301");
		testVector.push_back(testStaff5);
		fitnessFunction t(testVector);
		t.fitnessScore = 0;
		t.tooManyClasses(testVector);

		if (t.fitnessScore == -10) {
			cout << "tooManyClasses() is correct: " << t.fitnessScore << endl;
			return true;
		}
		cout << "tooManyClasses() is incorrect: " << t.fitnessScore << endl;
		return false;
	}
	bool testSameSemesterClasses() {
		vector<schedule> testVector;
		schedule testStaff("CS291B", "11A", "Hare", "Bloch0009");
		testVector.push_back(testStaff);
		schedule testStaff1("CS201A", "12P", "Hare", "Katz209");
		testVector.push_back(testStaff1);
		fitnessFunction t(testVector);
		t.fitnessScore = 0;
		t.sameSemesterClasses(testVector);

		if (t.fitnessScore == -1) {
			cout << "sameSemesterClasses() is correct: " << t.fitnessScore << endl;
			return true;
		}
		cout << "sameSemesterClasses() is incorrect: " << t.fitnessScore << endl;
		return false;
	}
	bool testMultisectionedClasses() {
		vector<schedule> testVector;
		schedule testStaff("CS101B", "2P", "Hare", "Haag301");
		testVector.push_back(testStaff);
		schedule testStaff1("CS101A", "1P", "Bingham", "Royall204");
		testVector.push_back(testStaff1);
		schedule testStaff2("CS191B", "2P", "Hare", "Haag301");
		testVector.push_back(testStaff2);
		schedule testStaff3("CS191A", "10A", "Bingham", "Royall204");
		testVector.push_back(testStaff3);
		fitnessFunction t(testVector);
		t.fitnessScore = 0;
		t.multisectionedClasses(testVector);

		if (t.fitnessScore == 5) {
			cout << "multisectionedClasses() is correct: " << t.fitnessScore << endl;
			return true;
		}
		cout << "multisectionedClasses() is incorrect: " << t.fitnessScore << endl;
		return false;
	}
};

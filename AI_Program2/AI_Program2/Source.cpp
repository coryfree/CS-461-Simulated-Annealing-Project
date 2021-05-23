//Cory Free
//Program 2
//March 1, 2020

#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "schedule.h"
#include "fitnessFunction.h"
#include "testClass.h"
using namespace std;

int main() {
	srand(time(NULL));
	ofstream fout("output.txt");
	string outputString;
	vector<string> Hare = { "CS101A", "CS101B", "CS201A", "CS201B", "CS291A", "CS291B", "CS303", "CS449", "CS461" };
	vector<string> Bingham = { "CS101A", "CS101B", "CS201A", "CS201B", "CS191A", "CS191B", "CS291A", "CS291B", "CS449" };
	vector<string> Kuhail = { "CS303", "CS431" };
	vector<string> Mitchell = { "CS191A", "CS191B", "CS291A", "CS291B", "CS303", "CS341" };
	vector<string> Rao = { "CS291A", "CS291B", "CS303", "CS341", "CS461" };
	vector<string> professors = { "Hare", "Bingham", "Kuhail", "Mitchell", "Rao", "Staff" };
	vector<string> times = { "10A", "11A", "12P", "1P", "2P", "3P", "4P" };
	vector<string> rooms = { "Haag301", "Haag206", "Royall204", "Katz209", "Flarsheim310", "Flarsheim260", "Bloch0009" };
	vector<int> roomCapacity = { 70, 30, 70, 50, 80, 25, 30 };
	vector<string> courses = { "CS101A", "CS101B", "CS201A", "CS201B", "CS191A", "CS191B",
								"CS291B", "CS291A", "CS303", "CS341", "CS449", "CS461" };
	vector<int> courseCapacity = { 40, 25, 30, 30, 60, 20, 40, 20, 50, 40, 55, 40 };
	
	//create a vector that will store the twelve different classes along with their times, professors, etc.
	vector<schedule> classes;
	for (int i = 0; i < 12; i++) {
		int randProf = rand() % professors.size(); //choose a random professor
		int randTime = rand() % times.size(); //choose a random time
		int randRoom = rand() % rooms.size(); //choose a random room

		schedule temp(courses[i], times[randTime], professors[randProf], rooms[randRoom]);
		classes.push_back(temp); //create an object with these randomly selected items and push it into the vector
	}

	int totalAttempts = 0; //keeps track of the total attempts, regardless of if a change is made
	int attempts = 0; //keeps track of how attempts have been made without a succesful change
	int changes = 0; //keeps track of the number of changes made
	double temperature = 1; //used in the annealing function
	//int finalScore = 0; //

	//testClass t; This was only used for testing to make sure the fitness functions were working properly

	//keeps looking for new attempts until the temperature becomes less than 0.001 or it is broken
	while (temperature > .001) {
		totalAttempts += 1; 
		double randVal = ((double)rand() / (double)(RAND_MAX)); //choose a random value between 0 and 1
		fitnessFunction original(classes); //create an object of the fitnessFunction class to compare fitness scores
		int randValue = rand() % 3 + 1; //this value will determine what the program will try to change to make the score better
		int randCourseNum = rand() % 12; //chooses which class will be changed
		
		//create a temporary schedule that will have one different value to see if it is better than the original
		vector<schedule> newSched;
		for (int i = 0; i < 12; i++) {
			schedule temp(courses[i], classes[i].get_time(), classes[i].get_professor(), classes[i].get_room());
			newSched.push_back(temp);
		}

		if (randValue == 1) { //changes a random value in the professors
			int randP = rand() % professors.size();
			newSched[randCourseNum].set_professor(professors[randP]);
			fitnessFunction tempS(newSched);
			
			//if the new schedules score is better or it passes the annealing function then you make the change
			if ((tempS.fitnessScore > original.fitnessScore || randVal <= exp(-(original.fitnessScore - tempS.fitnessScore) / temperature)) 
				&& tempS.fitnessScore != original.fitnessScore) {
				classes[randCourseNum].set_professor(professors[randP]);
				changes += 1; //incrememnt the number of changes, because a successful one was made
				attempts = 0; //make attempts 0 again
			}
			else {
				attempts += 1; //the attempt was unsuccessful, so increment attempts
			}
		}

		//same as last section, but it changes a random time instead
		else if (randValue == 2) { //changes a random value in the times
			int randT = rand() % times.size();
			newSched[randCourseNum].set_time(times[randT]);
			fitnessFunction tempS(newSched);
			if ((tempS.fitnessScore > original.fitnessScore || randVal <= exp(-(original.fitnessScore-tempS.fitnessScore)/temperature)) 
				&& tempS.fitnessScore != original.fitnessScore) {
				classes[randCourseNum].set_time(times[randT]);
				changes += 1;
				attempts = 0;
			}
			else {
				attempts += 1;
			}
		}

		//same as last section except it changes a random room instead
		else if (randValue == 3) { //changes a random value in the rooms
			int randR = rand() % rooms.size();
			newSched[randCourseNum].set_room(rooms[randR]);
			fitnessFunction tempS(newSched);
			if ((tempS.fitnessScore > original.fitnessScore || randVal <= exp(-(original.fitnessScore - tempS.fitnessScore) / temperature))
				&& tempS.fitnessScore != original.fitnessScore) {
				classes[randCourseNum].set_room(rooms[randR]);
				changes += 1;
				attempts = 0;
			}
			else {
				attempts += 1;
			}
		}

		//checks if the number of changes is >= to 400, or if totalAttempts is >= 4000
		//if one of these is true, lower the temperature and make these values 0 again
		if (changes >= 400 || totalAttempts >= 4000) {
			temperature *= .9;
			cout << "Lowering temperature: " << temperature << endl;
			changes = 0;
			totalAttempts = 0;
		}

		//checks if attempts > 4000, or if temperature < 0.001
		//if one of these is true, it outputs the current schedule and exits the program
		if (attempts > 4000 || temperature < 0.001) {
			//finalScore = original.fitnessScore;
			for (int i = 0; i < 12; i++) {
				fout << classes[i].courseNum << ", " << classes[i].professor << ", " << classes[i].room << ", " << classes[i].time << "\n";
			}
			fout << "Fitness Score: " << original.fitnessScore << endl;
			break;
		}	
	}
	system("pause");
	return 0;
}
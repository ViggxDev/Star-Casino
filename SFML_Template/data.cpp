#include "data.h"
#include "layout.h"

#include <fstream>
#include <iostream>

data::data()
{

}

//Function to sort the top scores and return the top <= 25 scores
std::vector<int> data::sortTopScores(std::vector<int> arr)
{
	//Sort the top scores
	std::sort(arr.begin(), arr.end());
	std::reverse(arr.begin(), arr.end());

	//Return the 25 scores highest in the sort, remove the lowest if over 25
	std::vector<int> result;
	int size = std::min(25, static_cast<int>(arr.size()));
	for (int i = 0; i < size; ++i) {
		result.push_back(arr[i]);
	}

	return result;
}

//Function to get the scores saved from before in txt file
std::vector<int> data::getScores()
{
	std::vector<int> arr;

	std::ifstream scores("scores.txt");

	if (scores.is_open()) {
		std::string line;
		while (std::getline(scores, line)) {
			if (line != "") {
				arr.push_back(stoi(line));
			}
		}
	}
	else {
		std::cout << "Unable to open scores file!" << std::endl;
	}
	
	return arr;
}

//Function that updates and adds newScore to txt file
void data::updateScores(int newScore)
{
	std::vector<int> scores = getScores();
	scores.push_back(newScore);
	scores = sortTopScores(scores);

	std::ofstream myfile("scores.txt");

	if (myfile.is_open())
	{
		for (int score : scores) {
			myfile << score << "\n";
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void data::newScore()
{
}

void data::setCurrentName(tgui::String name)
{
	currentName = name;
}

void data::setScore(int newScore)
{
	layout Layout;

	score = newScore;
	Layout.updateScoreUI();
}

tgui::String data::getCurrentName()
{
	return currentName;
}

int data::getScore()
{
	return score;
}
#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class data
{
public:
	data();

	std::vector<int> getScores();
	std::vector<int> sortTopScores(std::vector<int> arr);

	void updateScores(int newScore);
	void newScore();

	void setCurrentName(tgui::String name);
	void setScore(int newScore);

	tgui::String getCurrentName();
	int getScore();

private:
	tgui::String currentName;
	int score = 0;
};


#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "layout.h"

class data
{
public:
	data();

	std::vector<int> getScores();
	std::vector<int> sortTopScores(std::vector<int> arr);

	void updateScores(int newScore);
	
	int getHighScore();

	void setCurrentName(tgui::String name);
	void resetScore();

	tgui::String getCurrentName();
	int getCurrentScore();

	void updateCurrentScore(int toAdd, layout* Layout);

private:
	tgui::String currentName;
	int score = 0;
};


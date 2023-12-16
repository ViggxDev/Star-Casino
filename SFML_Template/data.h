#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

class data
{
public:
	data();

	void addNewScore();

	void setCurrentName(tgui::String name);
	void setScore(int newScore);

	tgui::String getCurrentName();
	int getScore();

private:
	tgui::String currentName;
	int score = 0;
};


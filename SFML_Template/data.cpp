#include "data.h"
#include "layout.h"

data::data()
{

}

void data::addNewScore()
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

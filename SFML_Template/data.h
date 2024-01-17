#pragma once

#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "layout.h"

class data
{
public:
	data();

	void start();

	std::string getInfo(int line);

	std::vector<std::string> getFullData();
	
	void updateValue(int line, std::string value);

	void setCurrentName(tgui::String name);
	void resetUser();
	void createUserData();

	tgui::String getCurrentName();

private:
	tgui::String currentName;
	int score = 0;
};


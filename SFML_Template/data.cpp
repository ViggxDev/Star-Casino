#include "data.h"
#include "layout.h"

#include <fstream>
#include <iostream>
#include <string>

//Info about the data text file
//Line: What it is
//1 -> Username

data::data()
{

}

void data::start()
{
	currentName = getInfo(1);

	std::cout << currentName << std::endl;
}

std::string data::getInfo(int pointerLine)
{
	std::string value;

	std::ifstream info("scores.txt");

	if (info.is_open()) {
		std::string line;
		int i = 0;
		while (std::getline(info, line)) {
			if (i == pointerLine) {
				value = line;
				break;
			}
			i++;
		}
	}

	return value;
}

//Get the info
std::vector<std::string> data::getFullData()
{
	std::vector<std::string> arr;

	std::ifstream info("scores.txt");

	if (info.is_open()) {
		std::string line;
		while (std::getline(info, line)) {
			arr.push_back(line);
		}
	}

	return arr;
}

//Function that updates and adds newScore to txt file
void data::updateValue(int line, std::string value)
{
	std::vector<std::string> info = getFullData();

	std::ofstream myfile("scores.txt");

	if (myfile.is_open())
	{
		int l = 0;
		for (std::string i : info) {
			if (l != line-1) {
				myfile << i << "\n";
			}
			else {
				myfile << value << "\n";
			}
			l++;
		}
		myfile.flush();
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file";
	}
}

void data::setCurrentName(tgui::String name)
{
	std::string sName = name.toStdString();
	updateValue(1, sName);
}

void data::resetUser()
{
	std::ofstream myfile("scores.txt");

	if (myfile.is_open()) {
		myfile.flush();
		myfile.close();
	}
}

void data::createUserData()
{

}

tgui::String data::getCurrentName()
{
	return getInfo(1);
}
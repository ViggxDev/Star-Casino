#include "layout.h"
#include "data.h"
#include "gameController.h"

#include <iostream>
#include <string>
#include <TGUI/TGUI.hpp>
#include <Windows.h>

void StartApplication() {
	layout Layout;
	data Data;
	gameController gc;

	//gc.dealersCards();

	Data.start();
	Layout.start();

	//Add some way of breaking when quitting, like a variable that turns false when user quits
	while (true) {
		Sleep(100);
		Layout.update();
	}
}

void test() {
	gameController gc;
	for (int i = 0; i < 100; i++)
	{
		gc.getRouletteNumber();
	}
	std::string test;
	std::cin >> test;
}

//main entry
int main()
{
	StartApplication();
}
#include "layout.h"
#include "data.h"

#include <iostream>
#include <string>
#include <TGUI/TGUI.hpp>
#include <Windows.h>

void StartApplication() {
	layout Layout;
	data Data;

	Data.resetUser();

	Data.start();
	Layout.start();

	//Add some way of breaking when quitting, like a variable that turns false when user quits
	while (true) {
		Sleep(100);
		Layout.update();
	}
}

//main entry
int main()
{
	StartApplication();
}
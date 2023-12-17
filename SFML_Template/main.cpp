#include "layout.h"
#include "data.h"

#include<iostream>
#include<string>
#include <TGUI/TGUI.hpp>

void StartApplication() {
	layout Layout;

	Layout.start();

	data Data;

	Data.updateScores(500);
}

//main entry
int main()
{
	StartApplication();
}
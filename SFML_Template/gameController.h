#pragma once

#include <iostream>
#include <vector>
#include <map>

class gameController
{
public:
	gameController();

#pragma region BlackJack21
	//Black Jack game controller
	int totalCounter();
	std::string randomCard();
	int getCardValue21(std::string card);
	std::vector<std::string> dealersCards();

#pragma endregion BlackJack21

private:
	//General
	std::vector<std::string> cards = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
	//Change so ace could be both 1 and 11
	std::map<std::string, int> cardsWorthBlackJack = { {"Ace", 1}, {"2", 2},{"3", 3} ,{"4", 4} ,{"5", 5} ,{"6", 6} ,{"7", 7} ,{"8", 8} ,{"9", 9} ,{"10", 10} ,{"Jack", 11} ,{"Queen", 11} ,{"King", 11} };
};


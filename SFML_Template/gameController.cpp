#include "gameController.h"
#include "data.h"
#include "layout.h"

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

int gameController::currentBet = 0;

gameController::gameController() {
}

int randomNum(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);

    return uni(rng);
}

int gameController::totalCounter()
{
    return 0;
}

std::string gameController::randomCard()
{
    int numOfCards = cards.size()-1;

    return cards[randomNum(0, numOfCards)];
}

int gameController::getCardValue21(std::string card)
{
    return cardsWorthBlackJack[card];
}

std::vector<std::string> gameController::dealersCards()
{
    //Rules
    //Hit on 16 or less
    //Stand on 17 or more

    std::vector<std::string> dealerCard;

    int totalDealer = 0;

    while (totalDealer <= 16) {
        std::string card = randomCard();
        int to_add = cardsWorthBlackJack[card];
        dealerCard.push_back(card);
        if (card == "Ace" && totalDealer + to_add <= 21) {
            to_add = 11;
        }
        totalDealer += to_add;
    }

    std::cout << "Total::" << totalDealer << std::endl;

    std::cout << "-----" << std::endl;
    for (std::string i : dealerCard) {
        std::cout << i << std::endl;
    }
    std::cout << "-----" << std::endl;

    return std::vector<std::string>();
}

std::string gameController::getRouletteNumber()
{
    int numbers = 38;
    std::vector<int> green = { 1, 2 };
    int number = randomNum(1, numbers);

    //std::cout << number << std::endl;

    if (std::find(green.begin(), green.end(), number) != green.end()) {
        return "green";
    }
    else if (number % 2 == 0) {
        return "red";
    }
    else {
        return "black";
    }
}

int gameController::getCurrentBet()
{
    return gameController::currentBet;
}

void gameController::changeCurrentBet(int increment)
{
    data Data;

    //Check if it is bigger than what the player has
    if (gameController::currentBet + increment > std::stoi(Data.getInfo(1))) {
        gameController::currentBet = std::stoi(Data.getInfo(1));
    }
    else if (gameController::currentBet < 0) {
        gameController::currentBet = 0;
    }
    else {
        gameController::currentBet += increment;
    }

    std::cout << gameController::currentBet << std::endl;
}

void gameController::resetBet()
{
    std::cout << "reset" << std::endl;
    gameController::currentBet = 0;
}

void gameController::allIn()
{
    data Data;
    currentBet = std::stoi(Data.getInfo(1));
}

std::string gameController::bet(std::string color)
{
    data Data;

    std::string betClr = getRouletteNumber();

    // Update the player's total balance by subtracting the current bet
    int balance = std::stoi(Data.getInfo(1));
    Data.updateValue(2, std::to_string(balance - currentBet));

    // Check if the bet was a win or a loss
    if (color == betClr) {
        // Win
        int winAmount = 0;
        if (color == "black" || color == "red") {
            winAmount = gameController::currentBet * smallWin;
        }
        else if (color == "green") {
            winAmount = gameController::currentBet * bigWin;
        }
        // Update the player's total balance by adding the win amount
        Data.updateValue(2, std::to_string(balance + winAmount));
    }

    // Reset the current bet to 0 after the bet has been processed
    gameController::currentBet = 0;

    return betClr;
}
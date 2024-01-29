#include "gameController.h"

#include <iostream>
#include <vector>
#include <random>

gameController::gameController()
{
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


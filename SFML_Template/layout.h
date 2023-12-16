#pragma once
#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

class layout
{
public:
    layout();

    void start();
    void update();

    void DisplayWindow();
    void btnPress(std::string text);
    float getPos(std::string y, bool isWidth);
    void makeButton(std::string btnName, std::string buttonText, const std::tuple<float, float, float, std::string, std::string, sf::Color, sf::Color>& sizeAndPos);
    void makeLabel(std::string text, const std::tuple<float, std::string, std::string, sf::Color> properties);
    tgui::EditBox::Ptr makeInput(std::string inputName, const std::tuple<float, float, float, std::string, std::string, sf::Color, sf::Color>& sizeAndPos);

    
    bool RunGUI();
    void setBackgroundGradient();

    void clearGui();

    void createMainMenu();
    void createLoginFrame();
private:
    tgui::GuiSFML* gui;
    sf::RenderWindow* window;

    std::string WindowTitle = "Casino";

    int i = 0;
};
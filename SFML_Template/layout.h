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

    void playBtnPress();

    float getPos(std::string y, bool isWidth);
    void makeButton(std::string btnName, std::string buttonText, const std::tuple<float, float, float, std::string, std::string>& sizeAndPos);
    tgui::Label::Ptr makeLabel(std::string text, const std::tuple<float, std::string, std::string, sf::Color> properties);
    tgui::EditBox::Ptr makeInput(const std::tuple<float, float, float, std::string, std::string, std::string, int>& sizeAndPos);

    void updateScoreUI(int score);

    bool RunGUI();
    void setBackgroundGradient();

    void clearGui();

    void forceQuit();

    void createMainMenu();
    void createOrResetUser();
    void createGameFrame();
private:
    tgui::GuiSFML* gui;
    sf::RenderWindow* window;

    //UI's
    //Input fields
    tgui::EditBox::Ptr nameBox;
    tgui::String tempName;

    //Labels
    tgui::Label::Ptr scoreUI;

    //BG color (0) = Gradient, (!0) = Black
    int bg;

    std::string WindowTitle = "Casino";
};
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
    void makeButton(std::string btnName, std::string buttonText, const std::tuple<float, float, float, std::string, std::string>& sizeAndPos);
    void makeLabel(std::string text, const std::tuple<float, std::string, std::string, sf::Color> properties);
    tgui::EditBox::Ptr makeInput(const std::tuple<float, float, float, std::string, std::string>& sizeAndPos);

    
    bool RunGUI();
    void setBackgroundGradient();

    void clearGui();

    void createMainMenu();
    void createCreateUserFrame();
private:
    tgui::GuiSFML* gui;
    sf::RenderWindow* window;

    //Input fields
    tgui::EditBox::Ptr nameBox;
    
    tgui::String tempName;

    std::string WindowTitle = "Casino";
};
#include "layout.h"
#include "data.h"
#include "gameController.h"

#include <string>

//Runs at start of program from main.cpp
void layout::start()
{
    DisplayWindow();
}

//Runs while window is open
void layout::update()
{
    gameController gc;
    data Data;
    //std::cout << Data.getMode() << std::endl;
    try {
        if (scoreUI) {
            scoreUI->setText("Cash: $" + Data.getInfo(1));
        }
        if (currentBet) {
            //std::cout << gc.getCurrentBet() << std::endl;
            currentBet->setText("$" + std::to_string(gc.getCurrentBet()));
        }
    }
    catch (std::exception& e) {
        std::cout << "scoreUI... raised an exception: " << e.what() << '\n';
    }
    
}

//Main part of the layout
#pragma region main

//Define window and gui in header file
layout::layout()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window = new sf::RenderWindow(desktop, WindowTitle, sf::Style::Fullscreen);
    gui = new tgui::GuiSFML(*window);
}

//Print Something on the Concole
void layout::btnPress(std::string text)
{
    data Data;
    gameController gc;

    //Function of buttons
    if (text == "LoadGameBtn") {
        if (Data.getInfo(1) == "") {
            Data.resetAndCreateUserData();
            createOrResetUser();
        }
        else {
            createGameFrame();
        }
    }
    else if (text == "NewProfileBtn") {
        Data.resetAndCreateUserData();
        createOrResetUser();
    }
    else if (text == "PlayGameButton") {
        playBtnPress();
    }
    else if (text == "RouletteMode") {
        createRouletteFrame();
    }
    //Increment/ decrement bet
    else if (text == "Decrement1") {
        gc.changeCurrentBet(-1);
    }
    else if (text == "Decrement5") {
        gc.changeCurrentBet(-5);
    }
    else if (text == "Increment1") {
        gc.changeCurrentBet(1);
    }
    else if (text == "Increment5") {
        gc.changeCurrentBet(5);
    }
    //Big changes (bet)
    else if (text == "ResetBet") {
        gc.resetBet();
    }
    else if (text == "AllIn") {
        gc.allIn();
    }
    //Bets
    else if (text == "greenBtn") {
        updateColor(gc.bet("green"));
    }
    else if (text == "redBtn") {
        updateColor(gc.bet("red"));
    }
    //Return back
    else if (text == "blackBtn") {
        updateColor(gc.bet("black"));
    }
    else if (text == "BackButton") {
        createGameFrame();
    }
    else {
        createMainMenu();
    }
}

void layout::playBtnPress()
{
    data Data;

    tempName = nameBox->getText();
    //Check so that the input field is empty or not
    if (tempName == "") {
        makeLabel("PLEASE ENTER A NAME", { 30.f, "50%", "50%", sf::Color::Red });
        return;
    }
    //Name was found
    Data.setCurrentName(tempName);
    Data.updateValue(2, "100");
    createGameFrame();
};

float layout::getPos(std::string p, bool isWidth) {
    float pos;
    std::string posStr = p;
    if (posStr.back() == '%') {
        posStr.pop_back();
        if (isWidth) {
            pos = std::stof(posStr) / 100.f * window->getSize().x;
        }
        else {
            pos = std::stof(posStr) / 100.f * window->getSize().y;
        }
    }
    else {
        pos = std::stof(posStr);
    }
    return pos;
}

//Create a Button and Call the btnPress func.
//Tuple<size.x, size.y, position.x, position.y>
tgui::Button::Ptr layout::makeButton(std::string btnName, std::string buttonText, const std::tuple<float, float, float, std::string, std::string>& sizeAndPos) {
    auto button = tgui::Button::create(buttonText);

    button->setTextSize(std::get<0>(sizeAndPos));

    button->setSize({ std::get<1>(sizeAndPos), std::get<2>(sizeAndPos) });
    button->setPosition({ getPos(std::get<3>(sizeAndPos), true), getPos(std::get<4>(sizeAndPos), false)});

    button->setOrigin(0.5f, 0.5f);

    //Assign renderer & set text & border styles
    auto renderer = button->getRenderer();

    renderer->setTextStyle(sf::Text::Bold);
    renderer->setBorders({ 5,5,5,5 });

    renderer->setBorderColorFocused(renderer->getBorderColor());

    gui->add(button);

    button->onPress.connect([this, btnName]() { this->btnPress(btnName); });

    return button;
}

//Function to create label
tgui::Label::Ptr layout::makeLabel(std::string text, const std::tuple<float, std::string, std::string, sf::Color> properties) {
    auto label = tgui::Label::create();
    label->setText(text);
    label->setTextSize(std::get<0>(properties));

    //Set position of label
    label->setPosition(getPos(std::get<1>(properties), true), getPos(std::get<2>(properties), false));

    label->setOrigin(0.5f, 0.5f);

    label->getRenderer()->setTextColor(std::get<3>(properties)); // Set text color

    label->onMousePress.connect([this, text]() {this->btnPress(text); });

    // Add the label to the gui
    gui->add(label);

    return label;
};

// Modify this function in layout.cpp
tgui::EditBox::Ptr layout::makeInput(const std::tuple<float, float, float, std::string, std::string, std::string, int>& sizeAndPos)
{
    auto input = tgui::EditBox::create();
    input->setSize({ std::get<1>(sizeAndPos), std::get<2>(sizeAndPos) });
    input->setPosition({ getPos(std::get<3>(sizeAndPos), true), getPos(std::get<4>(sizeAndPos), false) });

    input->setTextSize(std::get<0>(sizeAndPos));
    input->setDefaultText(std::get<5>(sizeAndPos));

    // Set the alignment of the text to center
    input->setAlignment(tgui::EditBox::Alignment::Center);
    input->setMaximumCharacters(std::get<6>(sizeAndPos));

    input->setOrigin(0.5f, 0.5f);

    gui->add(input);

    return input;
}

//Change the UI that is displayed on the screen
void layout::updateScoreUI(int score)
{
    //Chceck to see if the scoreUI has been created yet, if not. Skip this
    if (scoreUI != nullptr) {
        scoreUI->setText("Score: " + std::to_string(score));
    }
}

// Set the background gradient
void layout::setBackgroundGradient(sf::Color colorLeft, sf::Color colorRight) {
    // Create a vertex array for the background
    sf::VertexArray background(sf::Quads, 4);

    // Define the gradient colors
    //sf::Color colorLeft(157, 197, 187);
    //sf::Color colorRight(94, 128, 127);

    // Set the gradient colors and positions for each vertex
    for (int i = 0; i < 4; ++i) {

        for (int i = 0; i < 4; ++i) {
            float x = (i == 1 || i == 2) ? window->getSize().x : 0;
            float y = (i == 2 || i == 3) ? window->getSize().y : 0;
            background[i].position = sf::Vector2f(x, y);
        }

        // Interpolate color between colorLeft and colorRight based on the x-position
        float factor = background[i].position.x / window->getSize().x;

        background[i].color = sf::Color(
            static_cast<sf::Uint8>((1.0f - factor) * colorLeft.r + factor * colorRight.r),
            static_cast<sf::Uint8>((1.0f - factor) * colorLeft.g + factor * colorRight.g),
            static_cast<sf::Uint8>((1.0f - factor) * colorLeft.b + factor * colorRight.b)
        );
    }

    window->draw(background);
}

//For a easy debugging will show if a file counld not be opened in the console.
bool layout::RunGUI()
{
    //Try and create the main frame
    try
    {
        createMainMenu();
        return true;
    }
    catch (const tgui::Exception& e)
    {
        std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
        return false;
    }
}

//Quits the program & closes the UI
void layout::forceQuit()
{
    window->close();
}

//Main function to display the window
void layout::DisplayWindow()
{
    data Data;

    RunGUI();

    //Run while window is open
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            gui->handleEvent(event);

            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                forceQuit();
        }

        window->clear();

        update();

        //Check what bg to use
        switch (bg) {
        case 0:
            setBackgroundGradient(sf::Color(157, 197, 187), sf::Color(94, 128, 127));
            break;
        default:
            setBackgroundGradient(sf::Color(108, 42, 173), sf::Color(173, 42, 156));
        }

        //Display window
        gui->draw();
        window->display();
    }
}

#pragma endregion main

//Different frame inits to create layouts
#pragma region frames

void layout::clearGui()
{
    gui->removeAllWidgets();
}

void layout::createMainMenu()
{
    clearGui();
    makeLabel("STAR CASINO", { 100.f, "50%", "10%", sf::Color::White });
    makeButton("LoadGameBtn", "CONTINUE", { 80.f, 600.f, 150.f, "50%", "50%"});
    makeButton("NewProfileBtn", "RESTART", { 80.f, 600.f, 150.f, "50%", "70%" });

    bg = 0;
}

void layout::createOrResetUser()
{
    clearGui();
    makeLabel("USER", { 100.f, "50%", "10%", sf::Color::White });
    makeLabel("ENTER NAME", { 30.f, "50%", "30%", sf::Color::White });

    makeButton("PlayGameButton", "PLAY", { 75.f, 500.f, 100.f, "50%", "60%" });
    makeButton("MainMenuBtn", "BACK", { 75.f, 500.f, 100.f, "50%", "75%" });

    nameBox = makeInput({ 75.f, 500.f, 100.f, "50%", "40%", "Enter Name", 10});

    bg = 0;
}

void layout::createGameFrame()
{
    clearGui();
    scoreUI = makeLabel("Cash: $0", { 75.f, "12%", "9%", sf::Color::White });

    //Black Jack BTN
    //makeLabel("BLACKJACK", {100.f, "25%", "40%", sf::Color::White});
    //makeButton("EnterBlackJack", "ENTER", { 75.f, 450.f, 150.f, "25%", "55%" });

    //Slot Machine BTN
    makeLabel("ROULETTE", { 100.f, "50%", "40%", sf::Color::White });
    makeButton("RouletteMode", "ENTER", { 75.f, 450.f, 150.f, "50%", "55%" });

    makeButton("BackToLobby", "BACK", { 50.f, 200.f, 100.f, "50%", "75%" });

    bg = 1;
}

#pragma region UnusedBlackjackFrame
void layout::createBlackJackFrame()
{
    clearGui();
    makeLabel("BLACKJACK", { 50.f, "50%", "9%", sf::Color::White });

    scoreUI = makeLabel("Cash: $0", { 75.f, "12%", "9%", sf::Color::White });
}

#pragma endregion UnusedBlackjackFrame

void layout::createRouletteFrame()
{
    gameController gc;
    gc.resetBet();

    clearGui();

    //Title
    makeLabel("ROULETTE", { 50.f, "50%", "9%", sf::Color::White });

    //Bet result
    colorUI = makeLabel("WAITING FOR BET", {75.f, "50%", "30%", sf::Color::White});

    //Decrement
    makeButton("Decrement1", "-1", { 50.f, 150.f, 150.f, "35%", "65%" });
    makeButton("Decrement5", "-5", { 50.f, 150.f, 150.f, "25%", "65%" });

    //Current bet display
    currentBet = makeLabel("$0", { 60.f, "50%", "50%", sf::Color::White});

    //Increment
    makeButton("Increment1", "+1", {50.f, 150.f, 150.f, "65%", "65%"});
    makeButton("Increment5", "+5", { 50.f, 150.f, 150.f, "75%", "65%" });

    //Big bet changes
    makeButton("AllIn", "ALL IN", { 50.f, 250.f, 150.f, "50%", "65%" });
    makeButton("ResetBet", "RESET", { 50.f, 250.f, 150.f, "50%", "85%" });

    //Choose what to bet on btns
    tgui::Button::Ptr greenBtn = makeButton("greenBtn", "BET", {50.f, 150.f, 150.f, "65%", "85%"});
    greenBtn->getRenderer()->setBackgroundColor(tgui::Color::Green);
    greenBtn->getRenderer()->setBackgroundColorHover(tgui::Color::Green);

    tgui::Button::Ptr redBtn = makeButton("redBtn", "BET", { 50.f, 150.f, 150.f, "35%", "85%" });
    redBtn->getRenderer()->setBackgroundColor(tgui::Color::Red);
    redBtn->getRenderer()->setBackgroundColorHover(tgui::Color::Red);

    tgui::Button::Ptr blackBtn = makeButton("blackBtn", "BET", { 50.f, 150.f, 150.f, "25%", "85%" });
    blackBtn->getRenderer()->setBackgroundColor(tgui::Color::Black);
    blackBtn->getRenderer()->setBackgroundColorHover(tgui::Color::Black);
    blackBtn->getRenderer()->setTextColor(tgui::Color::White);
    blackBtn->getRenderer()->setTextColorHover(tgui::Color::White);

    //Back btn
    makeButton("BackButton", "BACK", { 50.f, 150.f, 150.f, "75%", "85%" });

    scoreUI = makeLabel("Cash: $0", { 75.f, "12%", "9%", sf::Color::White });
}

void layout::updateColor(std::string color)
{
    gui->remove(colorUI);

    // Convert color to uppercase
    std::transform(color.begin(), color.end(), color.begin(),
        [](unsigned char c) { return std::toupper(c); });

    colorUI = makeLabel(color, { 75.f, "50%", "30%", sf::Color::White });

    if (color == "GREEN") {
        colorUI->getRenderer()->setTextColor(tgui::Color::Green);
    }
    else if (color == "RED") {
        colorUI->getRenderer()->setTextColor(tgui::Color::Red);
    }
    else if (color == "BLACK") {
        colorUI->getRenderer()->setTextColor(tgui::Color::Black);
    }
}

#pragma endregion frames
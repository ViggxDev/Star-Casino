#include "layout.h"
#include "data.h"

//Runs at start of program from main.cpp
void layout::start()
{
    DisplayWindow();
}

//Runs while window is open
void layout::update()
{
    
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

    //Function of buttons
    if (text == "PlayBtn") {
        createCreateUserFrame();
    }
    else if (text == "PlayGameButton") {
        tempName = nameBox->getText();
        //Check so that the input field is empty or not
        if (tempName == "") { 
            makeLabel("PLEASE ENTER A NAME", { 30.f, "50%", "50%", sf::Color::Red });
            return;
        }
        //Name was found
        Data.setCurrentName(tempName);
        std::cout << Data.getCurrentName() << std::endl;
        createGameFrame();
    }
    else {
        createMainMenu();
    }
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
void layout::makeButton(std::string btnName, std::string buttonText, const std::tuple<float, float, float, std::string, std::string>& sizeAndPos) {
    auto button = tgui::Button::create(buttonText);

    button->setTextSize(std::get<0>(sizeAndPos));

    button->setSize({ std::get<1>(sizeAndPos), std::get<2>(sizeAndPos) });
    button->setPosition({ getPos(std::get<3>(sizeAndPos), true), getPos(std::get<4>(sizeAndPos), false)});

    button->setOrigin(0.5f, 0.5f);

    //Assign renderer & set text & border styles
    auto renderer = button->getRenderer();

    renderer->setTextStyle(sf::Text::Bold);
    renderer->setBorders({ 5,5,5,5 });

    gui->add(button);

    button->onPress.connect([this, btnName]() { this->btnPress(btnName); });
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
tgui::EditBox::Ptr layout::makeInput(const std::tuple<float, float, float, std::string, std::string>& sizeAndPos)
{
    auto input = tgui::EditBox::create();
    input->setSize({ std::get<1>(sizeAndPos), std::get<2>(sizeAndPos) });
    input->setPosition({ getPos(std::get<3>(sizeAndPos), true), getPos(std::get<4>(sizeAndPos), false) });

    input->setTextSize(std::get<0>(sizeAndPos));
    input->setDefaultText("Enter Name");

    // Set the alignment of the text to center
    input->setAlignment(tgui::EditBox::Alignment::Center);
    input->setMaximumCharacters(10);

    input->setOrigin(0.5f, 0.5f);

    gui->add(input);

    return input;
}

void layout::updateScoreUI()
{
    data Data;

    scoreUI->setText("Score: " + Data.getCurrentScore());
}

// Set the background gradient
void layout::setBackgroundGradient() {
    // Create a vertex array for the background
    sf::VertexArray background(sf::Quads, 4);

    // Define the gradient colors
    sf::Color colorLeft(117, 58, 136);
    sf::Color colorRight(174, 50, 111);

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

//Main function to display the window
void layout::DisplayWindow()
{
    data Data;

    RunGUI();

    std::cout << Data.getHighScore() << std::endl;

    //Run while window is open
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            gui->handleEvent(event);

            if (event.type == sf::Event::Closed)
                forceQuit();
            if (event.key.code == sf::Keyboard::Escape)
                forceQuit();
        }

        window->clear();

        update();

        //Check what bg to use
        switch (bg) {
        case 0:
            setBackgroundGradient();
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

void layout::forceQuit()
{
    window->close();
}

void layout::createMainMenu()
{
    clearGui();
    makeLabel("STAR EXPLORER", { 100.f, "50%", "10%", sf::Color::White });
    makeButton("PlayBtn", "PLAY", { 80.f, 600.f, 150.f, "50%", "50%"});
    makeButton("LeaderBoardBtn", "LEADERBOARD", { 75.f, 600.f, 150.f, "50%", "70%"});

    bg = 0;
}

void layout::createCreateUserFrame()
{
    clearGui();
    makeLabel("USER", { 100.f, "50%", "10%", sf::Color::White });
    makeLabel("ENTER NAME", { 30.f, "50%", "30%", sf::Color::White });

    makeButton("PlayGameButton", "PLAY", { 75.f, 500.f, 100.f, "50%", "60%" });
    makeButton("MainMenuBtn", "BACK", { 75.f, 500.f, 100.f, "50%", "75%" });

    nameBox = makeInput({ 75.f, 500.f, 100.f, "50%", "40%" });

    bg = 0;
}

void layout::createGameFrame()
{
    clearGui();
    scoreUI = makeLabel("Score: 0", { 100.f, "50%", "10%", sf::Color::White });

    bg = 1;
}

#pragma endregion frames
#include "layout.h"

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
    window = new sf::RenderWindow({ 1200, 800 }, WindowTitle);
    gui = new tgui::GuiSFML(*window);
}

//Print Something on the Concole
void layout::btnPress(std::string text)
{
    if (text == "LoginPageRedirect") {
        createLoginFrame();
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
void layout::makeButton(std::string btnName, std::string buttonText, const std::tuple<float, float, float, std::string, std::string, sf::Color, sf::Color>& sizeAndPos) {
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
void layout::makeLabel(std::string text, const std::tuple<float, std::string, std::string, sf::Color> properties) {
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
};

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

// Modify this function in layout.cpp
tgui::EditBox::Ptr layout::makeInput(std::string inputName, const std::tuple<float, float, float, std::string, std::string, sf::Color, sf::Color>& sizeAndPos)
{
    auto input = tgui::EditBox::create();
    input->setSize({ std::get<1>(sizeAndPos), std::get<2>(sizeAndPos) });
    input->setPosition({ getPos(std::get<3>(sizeAndPos), true), getPos(std::get<4>(sizeAndPos), false) });

    input->setTextSize(std::get<0>(sizeAndPos));

    // Set the alignment of the text to center
    input->setAlignment(tgui::EditBox::Alignment::Center);

    input->setOrigin(0.5, 0.5);

    gui->add(input);

    return input;
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
    RunGUI();

    //Run while window is open
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            gui->handleEvent(event);

            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();

        update();
        setBackgroundGradient();

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
    makeLabel("STAR EXPLORER", {100.f, "50%", "10%", sf::Color::White});
    makeButton("LoginPageRedirect", "LOGIN", { 75.f, 500.f, 100.f, "50%", "50%", sf::Color::White, sf::Color::Blue});
    makeButton("LoginPageRedirect", "REGISTER", { 75.f, 500.f, 100.f, "50%", "70%", sf::Color::White, sf::Color::Blue });

    makeInput("UsernameInput", { 35.f, 500.f, 100.f, "50%", "30%", sf::Color::White, sf::Color::Blue });
}

void layout::createLoginFrame()
{
    clearGui();
    makeLabel("Login", { 100.f, "50%", "10%", sf::Color::White });
    makeButton("MainFrameRedirect", "Main Menu", { 75.f, 500.f, 100.f, "50%", "50%", sf::Color::White, sf::Color::Blue });
}

#pragma endregion frames
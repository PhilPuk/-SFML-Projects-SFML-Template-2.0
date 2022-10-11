#include "Game.h"

void Game::initWindow(sf::RenderWindow* window)
{
    this->window = window;

    this->winSize.x = this->window->getSize().x;
    this->winSize.y = this->window->getSize().y;
}

//Initialization
void Game::initVariables(sf::RenderWindow* window)
{
    this->endGame = false;
    this->endApplication = false;
}

void Game::initGeneration()
{
    this->gen = new Generation(ARRAY_START_SIZE, ARRAY_START_SIZE, true, false);

    /*
    std::cout << "Unsorted Array\n\n";
    for (int i = 0; i < 30; i++)
    {
        std::cout<<this->gen->array[i]<<"\n";
    }
    */
}

void Game::initAlgorithms(sf::Font& font)
{
    this->algo = new Algorithms(this->winSize, this->gen->array, font, true);
}

Game::Game(sf::RenderWindow* window, sf::Font& font)
{
    this->initWindow(window);
    this->initVariables(window);
    this->initGeneration();
    this->initAlgorithms(font);
}

Game::~Game()
{
    delete this->gen;
}

void Game::CloseApplication()
{
    this->endGame = true;
    this->endApplication = true;
}

void Game::resetVariables()
{
    this->initVariables(this->window);
}

const bool& Game::getEndGame() const
{
    return this->endGame;
}

const bool& Game::getEndApplication() const
{
    return this->endApplication;
}


void Game::run()
{
    //Main loop of the game

    while (!endGame)
    {
        this->update();

        this->render();
    }
}

void Game::pollEvents()
{
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
        case sf::Event::Closed:
            this->CloseApplication();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                this->endGame = true;
            break;
        }
    }
}

void Game::update()
{
    this->pollEvents();

    this->algo->currentSelectedAlgo(this->gen->array, *this->window);
}

void Game::render()
{
    this->window->clear(sf::Color(150,150,150,255));

    this->algo->render(*this->window);

    this->window->display();
}

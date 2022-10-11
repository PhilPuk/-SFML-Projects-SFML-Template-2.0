#include "BrickManager.h"

void BrickManager::initVariables()
{

}

void BrickManager::initBricksLine(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font)
{
	//Calculation for positioning
	float fac = 0.75f;
	float y = static_cast<float>(winSize.y) / 2.f;
	float sizeX = static_cast<float>(winSize.x) / static_cast<float>(array.size());
	std::cout << array.size() << "\n";
	sf::Vector2f pos(sizeX / 2.f, y);
	sf::Vector2f size(sizeX, 40.f);

	//Creating the bricks
	for (size_t i = 0; i < array.size(); i++)
	{
		this->bricks.push_back(new Brick(font, pos, size));
		this->bricks[i]->setTextInt(array[i]);
		pos.x += sizeX;
	}
}

void BrickManager::initBricksFullScreen(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font)
{
	float sizeX = 55.f;
	float sizeY = 50.f;
	sf::Vector2f size(sizeX, sizeY);
	float xSpacing = sizeX * 1.25f;
	float ySpacing = sizeY * 1.5f;
	sf::Vector2f pos(sizeX, sizeY);

	float xStart = sizeX;

	for (size_t i = 0; i < array.size(); i++)
	{
		this->bricks.push_back(new Brick(font, pos, size));
		this->bricks[i]->setTextInt(array[i]);
		pos.x += xSpacing;

		//Check if end of screen horizontaly is reached
		if (this->bricks[i]->shape.getPosition().x + this->bricks[i]->shape.getGlobalBounds().width >= static_cast<float>(winSize.x))
		{
			//Jumps to next line
			pos.y += ySpacing;
			//Beginning of screen horizontaly
			pos.x = xStart;
		}
	}

}

BrickManager::BrickManager(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font, bool UsefullScreen)
{
	this->initVariables();
	if (UsefullScreen)
		this->initBricksFullScreen(winSize, array, font);
	else
		this->initBricksLine(winSize, array, font);
}

BrickManager::~BrickManager()
{
	//Delete all bricks
	for (size_t i = 0; i < this->bricks.size(); i++)
	{
		delete this->bricks[i];
		this->bricks.erase(this->bricks.begin(), this->bricks.end());
	}
}

void BrickManager::update(std::vector<int>* array)
{

}

void BrickManager::renderBricks(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->bricks.size(); i++)
	{
		this->bricks[i]->render(target);
	}
}

void BrickManager::render(sf::RenderTarget& target)
{
	this->renderBricks(target);
}

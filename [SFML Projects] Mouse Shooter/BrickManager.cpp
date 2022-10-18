#include "BrickManager.h"

void BrickManager::initVariables()
{

}

///<summary>
///Sets the bricks in a straight line in the center of the screen.
///Ignores going beyond the window border.
///</summary>
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

///<summary>
///Places bricks starting at the top left of the screen.
///Goes to the left until the edge of the window is reached.
///Then jumps into the the total left of the next line.
///</summary>
void BrickManager::initBricksFullScreen(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font)
{
	//To-do
	//calculate scaled size in reference to the window

	//Old working
	//float sizeX = 55.f;
	//float sizeY = 50.f;

	//New not tested!
	float sizeX = static_cast<float>(winSize.x) / static_cast<float>(array.size()) - (static_cast<float>(winSize.x) * 0.01f);
	float sizeY = static_cast<float>(winSize.x) / static_cast<float>(array.size()) - (static_cast<float>(winSize.x) * 0.01f);
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

void initBricksAsDiagramm(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font)
{
	float spacing = static_cast<float>(winSize.x) / (static_cast<float>(array.size()) * 3.f);
	float sizeX = static_cast<float>(winSize.x) / static_cast<float>(array.size()) - spacing;
	float sizeY;
	sf::Vector2f size(sizeX, sizeY);
	float baseLineY = static_cast<float>(winSize.Y) - 30.f;
	sf::Vector2f pos(spacing, baseLineY);

	//Sets all elements of the diagramm almost on the bottom of the screen.
	//Substracts that value - its size so it doesnt go to the bottom of the screen.
	for(size_t i = 0; i < array.size(); i++)
	{
		size.Y = static_cast<float>(array[i]); 
		pos.y = baseLineY - size.Y;
		this->bricks.push_back(new Brick(font , pos, size));
		this->bricks[i].setTextInt(&array[i]);
		pos.x += spacing;
	}
}

BrickManager::BrickManager(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font, bool UsefullScreen, bool UseBricks)
{
	this->initVariables();
	if(!UseBricks)
		this->initBricksAsDiagramm(winSize, array, font);
	else if (UsefullScreen)
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

///<summary>
///Swop the sizes of the given indexes
///
///</summary>
void BrickManager::swopDiagrammElements(float sizeYOne, float sizeYTwo, int indexOne, int indexTwo)
{
	this->bricks[indexOne].setSize(this->bricks[indexOne].getSize().x, sizeYTwo);
	this->bricks[indexTwo].setSize(this->bricks[indexTwo].getSize().x, sizeYOne);
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

#pragma once

#include"Brick.h"
#include<vector>

class BrickManager
{
private:
	

	void initVariables();
	void initBricksLine(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font);
	void initBricksFullScreen(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font);
	void initBricksAsDiagramm(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font);
public:
	BrickManager(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font, bool UsefullScreen, bool UseBricks);
	virtual ~BrickManager();

	std::vector<Brick*> bricks;

	void update(std::vector<int>* array);

	void renderBricks(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};


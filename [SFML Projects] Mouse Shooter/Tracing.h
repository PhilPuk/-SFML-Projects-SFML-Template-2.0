#pragma once

#include<iostream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

//To-DO
//Create vectors instead of boxes between straight lines.
//Delete left overs.
//Curves stay as boxes.
//Preallocate memory = better performance : downside harder to implement with deleting
// for the 2d vector trace boxes:
// 	//Calculate size.x in addition of all boxes that are laying in one line.
	//set box size for new 2DVector traces box to it.
	//Calculate angle for the vector via the positions of the single boxes used in the addition.
	//set angle of the vector.
	//Set pos

class Tracing
{
private:
	sf::RectangleShape box;

	float msgTimeMax;
	float msgTime;

	void initVariables();
	void initBox();
public:
	Tracing();
	virtual ~Tracing();

	std::vector<sf::RectangleShape*> traces;
	std::vector<sf::RectangleShape*> TwoDvectortraces;

	void createNewTraceBox(const sf::Vector2f& pos);
	void createNew2DVectorTraceBox(const sf::Vector2f& pos, float& angle);

	void deleteSpecificTrace(int& index);

	void updateCMDMessages();
	void updateOpacity(int& i);
	void updateTraceDeletion(int& i);
	bool updateVectorChecking(int& i);
	void updateVectorCreation(int& i);
	void updateForLoop();
	void update();

	void renderTraces(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};


#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

class Navigation
{
private:

	void initVariables();
public:
	Navigation();
	virtual~Navigation();

	void update();

	void render(sf::RenderTarget& target);
};

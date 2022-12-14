#include "Mouse.h"


void Mouse::initVariables()
{
	this->mouse_click_puffer = 30.f / 5.f; // 200ms
	this->mouse_click_time_reach = 0.f;

	this->mouse_Held = false;
}

//Constructor / Destructor
Mouse::Mouse()
{
	this->initVariables();
}

Mouse::~Mouse()
{

}

void Mouse::set_Mouse_Click_Time_Reach(float current_Application_Time)
{
	this->mouse_click_time_reach = current_Application_Time + this->mouse_click_puffer;
}

void Mouse::set_Mouse_Held()
{
	this->mouse_Held = true;
}

const sf::Vector2i Mouse::getMousePosWindow() const
{
	return this->mousePosWindow;
}

const sf::Vector2f Mouse::getMousePosView() const
{
	return this->mousePosView;
}

const bool& Mouse::getMouseLeftClicked() const
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

const float& Mouse::get_Mouse_Click_Time_Reach() const
{
	return this->mouse_click_time_reach;
}

const bool& Mouse::getMouseHeld() const
{
	return mouse_Held;
}

//Functions
	//Update
void Mouse::updateMousePositions(sf::RenderWindow& window, bool debug)
{
	this->mousePosWindow = sf::Mouse::getPosition(window);
	this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);

	if (debug)
	{
		//To debug mouse positions
		system("cls");
		std::cout << "MOUSEPOSVIEW:		Mouse X: " << this->mousePosView.x << "	Mouse Y: " << this->mousePosView.y << "\n";
		std::cout << "MOUSEPOSWINDOW:	Mouse X: " << this->mousePosWindow.x << "	Mouse Y: " << this->mousePosWindow.y << "\n";
	}
}

void Mouse::updateMouseHeld()
{
	if (!this->getMouseLeftClicked())
	{
		this->mouse_Held = false;
	}
}

void Mouse::update(sf::RenderWindow& window, bool debug)
{
	this->updateMouseHeld();
	this->updateMousePositions(window, debug);
}

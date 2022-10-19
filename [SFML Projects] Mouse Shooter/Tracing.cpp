#include "Tracing.h"

void Tracing::initVariables()
{
	this->msgTimeMax = 60.f;
	this->msgTime = this->msgTimeMax;
}

void Tracing::initBox()
{
	this->box.setFillColor(sf::Color(255,0,0,100));
	this->box.setSize(sf::Vector2f(10.f, 10.f));
	//this->box.setRadius(5.f);

	this->box.setPosition(sf::Vector2f(-100.f, -100.f));

	this->box.setOrigin
	(
		this->box.getLocalBounds().left + this->box.getLocalBounds().width / 2.0f,
		this->box.getLocalBounds().top + this->box.getLocalBounds().height / 2.0f
	);
}

Tracing::Tracing()
{
	this->initVariables();
	this->initBox();
}

Tracing::~Tracing()
{
	//Boxes deleting
	for (int i = 0; i < this->traces.size(); i++)
	{
		delete this->traces[i];
		this->traces.erase(this->traces.begin(), this->traces.end());
	}

	//2d vector boxes deleting
	for(int i = 0; i < this->TwoDvectortraces.size(); i++)
	{
		delete this->TwoDvectortraces[i];
		this->TwoDvectortraces.erase(this->TwoDvectortraces.begin(), this->TwoDvectortraces.end());
	}

	std::cout << "Traces vector size: " << this->traces.size() << "\n";
	std::cout << "2D Vector Traces vector size: " << this->TwoDvectortraces.size() << "\n";
}

void Tracing::createNewTraceBox(const sf::Vector2f& pos)
{
	this->traces.push_back(new sf::RectangleShape(box));
	this->traces[this->traces.size() - 1]->setPosition(pos);
}

void createNew2DVectorTraceBox(const sf::Vector2f& pos, float& angle)
{
	this->TwoDvectortraces.push_back(new sf::RectangleShape(box));
	this->TwoDvectortraces[this->TwoDvectortraces.size() - 1].setPosition(pos);
	this->TwoDvectortraces[this->TwoDvectortraces.size() - 1].setRotation(angle);
}

void Tracing::deleteSpecificTrace(int& index)
{
	delete this->traces[index];
	this->traces.erase(this->traces.begin() + index);
}

void Tracing::updateCMDMessages()
{
	if (this->msgTime < this->msgTimeMax)
	{
		this->msgTime++;
	}
	else
	{
		this->msgTime = 0.f;
		std::cout << "Traces vector size: " << this->traces.size() << "\n";
		std::cout << "2D Vector Traces vector size: " << this->TwoDvectortraces.size() << "\n";
	}
}

void Tracing::updateOpacity(int& i)
{
	//RGB Circles
	//this->traces[i]->setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, this->traces[i]->getFillColor().a - 1));
	//Red
	this->traces[i]->setFillColor(sf::Color(255, 0, 0, this->traces[i]->getFillColor().a - 1));
}

void Tracing::updateTraceDeletion(int& i)
{
	if (this->traces[i]->getFillColor().a <= 0)
		this->deleteSpecificTrace(i);
}

bool updateVectorChecking(int& i)
{
	if(this->traces[i].getPosition() = sf::Vector2f
	(
			this->traces[i + 1].getPosition().x - this->traces[i + 1].getSize().x,
		 	this->traces[i + 1].getPosition().y - this->traces[i + 1].getSize().y
	))
	return true;
	else
	return false;

}

void updateVectorCreation(int& i)
{
	//sf::Vector2f pos(this->traces[i].getPosition());
	// to do calculate angle between the boxes//float angle = ;
	this->createNew2DVectorTraceBox(this->traces[i].getPosition(), angle):

	this->deleteSpecificTrace(i);
}

void Tracing::updateForLoop()
{
	for (int i = 0; i < this->traces.size(); i++)
	{
		this->updateOpacity(i);
		this->updateTraceDeletion(i);

		if(this->updateVectorChecking(i))
		this->updateVectorCreation();
	}
}

void Tracing::update()
{
	this->updateCMDMessages();
	this->updateForLoop();

}

void Tracing::renderTraces(sf::RenderTarget& target)
{
	for (int i = 0; i < this->traces.size(); i++)
	{
		target.draw(*this->traces[i]);
	}
}

void Tracing::render(sf::RenderTarget& target)
{
	this->renderTraces(target);
}


#include "FieldManager.h"

void FieldManager::initVariables()
{
	//Colors
	this->color_GreenMark = sf::Color(100, 255, 100, 255);
	this->color_RedMark = sf::Color(255, 100, 100, 255);
	this->color_baseColor = sf::Color(255, 255, 255, 255);

	this->anyCropisMarked = false;
}

void FieldManager::initTextures(sf::Texture* t_Field, sf::Texture* t_Crop)
{
	this->t_Field = *t_Field;
	this->t_Crop = *t_Crop;
}

void FieldManager::initBeginnerField(sf::Vector2u& winSize)
{
	sf::Vector2f pos = {
		static_cast<float>(winSize.x) / 1.4f,
		static_cast<float>(winSize.y) / 1.35f
	};
	this->fields.push_back(new Field(this->t_Crop, this->t_Field, pos));
}

FieldManager::FieldManager(sf::Vector2u& winSize, sf::Texture* t_Field, sf::Texture* t_Crop)
{
	this->initVariables();
	this->initTextures(t_Field, t_Crop);
	this->initBeginnerField(winSize);
}

FieldManager::~FieldManager()
{
	for (auto& i : fields)
	{
		this->fields.erase(this->fields.begin(), this->fields.end());
	}
	std::cout << "Size of fields vector array: " << this->fields.size() << " - SHOULD BE 0!\n";
}

void FieldManager::updateMarking(int& i, int& j, Mouse& mouse, static const bool&(&func)(Mouse& mouse, sf::FloatRect object), ShopEngine& shop_e, int indexOfSeed)
{
	//Check for intersection between mouse and the crop
	if (func(mouse, this->fields[i]->crops[j]->s_crop.getGlobalBounds()))
	{
		//check if its already marked green and if enough money is in the bank
		if (indexOfSeed < 0 || indexOfSeed >= 15)std::cout << "ERROR::FIELDMANAGER::UPDATEMARKING::indexOfSeed to big or small: " << indexOfSeed << "\n";
		if (!this->fields[i]->crops[i]->getHasSeed() && shop_e.getBuyIsPossible(shop_e.getPriceOfSeed(indexOfSeed)))
		{
			if (!this->fields[i]->crops[i]->getIsMarked())
				this->fields[i]->crops[j]->s_crop.setColor(this->color_GreenMark);
		}
		else // If it already got a seed mark red
		{
			if (!this->fields[i]->crops[i]->getIsMarked())
			this->fields[i]->crops[j]->s_crop.setColor(this->color_RedMark);
		}
		//Set that the crop is marked with a color
		this->fields[i]->crops[j]->setIsMarked();
		this->anyCropisMarked = true;
	}
	else if (this->fields[i]->crops[j]->s_crop.getColor() != this->color_baseColor)
	{
		this->fields[i]->crops[j]->s_crop.setColor(this->color_baseColor);
		this->fields[i]->crops[j]->resetIsMarked();
	}
}

void FieldManager::update()
{

}

void FieldManager::renderFields(sf::RenderTarget& target)
{
	for (auto& i : fields)
	{
		i->render(target);
	}
}
void FieldManager::render(sf::RenderTarget& target)
{
	this->renderFields(target);
}

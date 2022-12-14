#pragma once

#include<vector>

#include"Crops.h"

class Field
{
private:
	enum CROPAMOUNT { ONE = 1, TWO = 2, FOUR = 4, SIX = 6 };
	uint8_t currentCropAmount;
	bool FieldFilled;

	void initVariables();
	void initFirstCrop(sf::Texture& t_Crop, sf::Vector2f pos);
	void initField(sf::Texture& t_Field, sf::Vector2f pos);
public:
	Field(sf::Texture& t_Crop, sf::Texture& t_Field, sf::Vector2f pos);
	virtual ~Field();

	std::vector<Crops*> crops;
	sf::Sprite s_Field;

	void newCrop();
	void updateUpgradedCropTexture(sf::Texture& texture);
	void upgradeCrop();
	void placeSeedOnCrop(int indexOfSeed);

	void update();

	void renderField(sf::RenderTarget& target);
	void renderCrops(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};


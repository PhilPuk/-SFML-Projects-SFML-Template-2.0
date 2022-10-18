#include "Algorithms.h"

void Algorithms::initVariables()
{
	this->algoFinished = false;
}

void Algorithms::initBrickManager(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font, bool UsefullScreen)
{
	this->bricks = new BrickManager(winSize, array, font, true);
}

Algorithms::Algorithms(sf::Vector2u& winSize, std::vector<int>& array, sf::Font& font, bool UsefullScreen, bool UseBricks)
{
	this->initVariables();
	this->initBrickManager(winSize, array, font, UsefullScreen);
}

Algorithms::~Algorithms()
{
	delete this->bricks;
}

//Utility

void Algorithms::setBricksColorRed(int i, int j)
{
	this->bricks->bricks[i]->shape.setOutlineColor(MARKED_COLOR);
	this->bricks->bricks[j]->shape.setOutlineColor(MARKED_COLOR);
}

void Algorithms::setBrickToBaseColor(int index)
{
	this->bricks->bricks[index]->shape.setOutlineColor(BASE_COLOR);
}

void Algorithms::setBricksColorBlack(int i, int j)
{
	this->bricks->bricks[i]->shape.setOutlineColor(BASE_COLOR);
	this->bricks->bricks[j]->shape.setOutlineColor(BASE_COLOR);
}

void Algorithms::setBrickToMarkedColor(int index)
{
	this->bricks->bricks[index]->shape.setOutlineColor(MARKED_COLOR);
}

void Algorithms::swopTwoInt(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Algorithms::swopTwoDiagrammElements(int indexOne, int indexTwo, std::vector<int>& array)
{
	this->bricks->swopDiagrammElements
	(
		this->bricks->bricks[indexOne].getSize().y,
	 	this->bricks->bricks[indexTwo].getSize().y,
	 	indexOne,
	 	indexTwo
	 );
	 this->swopTwoInt(&array[indexOne], &array[indexTwo]);
	 this->bricks->bricks[indexOne].setTextInt(&array[indexOne]);
	 this->bricks->bricks[indexOne].setTextInt(&array[indexTwo]);
}

void Algorithms::resetAlgoFinished()
{
	this->algoFinished = false;
}

const bool& Algorithms::getAlgoFinished() const
{
	return this->algoFinished;
}

void Algorithms::Bubble_Sort(std::vector<int>& array, sf::RenderWindow& window)
{
		for (int i = 0; i < array.size(); i++)
		{
			for (int j = i + 1; j < array.size(); j++)
			{
				if (array[i] > array[j])
				{
					//Swop values
					int tmp = array[i];
					array[i] = array[j];
					array[j] = tmp;

					//Set the text to the new values.
					this->bricks->bricks[i]->setTextInt(array[i]);
					this->bricks->bricks[j]->setTextInt(array[j]);
					//Color current compared bricks red.
					this->setBricksColorRed(i, j);

					//Render it to the window
					this->render(window);
					sf::sleep(sf::milliseconds(200));
				}
				//Reset last compared bricks to color black
				this->setBricksColorBlack(i, j);
			}
		}
}

void Algorithms::Selection_Sort(std::vector<int>& array, sf::RenderWindow& window)
{
		//First element of array is the min number in the beginning, that doesn't has to be true, it's just for comparsion.
		for (int i = 0; i < array.size() - 1; i++)
		{
			int min_i = i;
			for (int j = i + 1; j < array.size(); j++)
			{
				this->setBricksColorRed(min_i, j);
				if (array[min_i] > array[j])
				{
					this->setBrickToBaseColor(min_i);
					min_i = j;
					this->setBrickToMarkedColor(min_i);
				}
				this->render(window);
				sf::sleep(sf::milliseconds(20));
				this->setBrickToBaseColor(j);
			}
			//Swop values.
			this->swopTwoInt(&array[min_i], &array[i]);
			this->setBricksColorRed(i, min_i);
			//Reset last compared bricks to color black
			this->render(window);
			sf::sleep(sf::milliseconds(300));
			this->setBricksColorBlack(i, min_i);
			this->bricks->bricks[min_i]->setTextInt(array[min_i]);
			this->bricks->bricks[i]->setTextInt(array[i]);
		}
}

void Algorithms::merge(sf::RenderWindow& window, std::vector<int>& array, int left_index, int mid_index, int right_index)
{
	//Creating indexes
	int i, j, k;

	//Calculating size of the arrays
	int left_size = mid_index - left_index + 1;
	int right_size = right_index - mid_index;

	//Creating subvectors
	std::vector<int> left_vector, right_vector;

	//Fill left vector
	for (i = 0; i < left_size; i++)
	{
		left_vector.push_back(array[static_cast<std::vector<int, std::allocator<int>>::size_type>(left_index) + i]);
	}
	//Fill right vector
	for (j = 0; j < right_size; j++)
	{
		right_vector.push_back(array[static_cast<std::vector<int, std::allocator<int>>::size_type>(mid_index) + 1 + j]);
	}

	//Reset indexes
	i = 0, j = 0, k = left_index;

	//Filling until one side is empty
	while (i < left_size && j < right_size)
	{
		if (left_vector[i] <= right_vector[j])
		{
			array[k] = left_vector[i];
			this->bricks->bricks[k]->setTextInt(array[k]);
			this->renderWithBreak(window, PAUSE_TIMER);
			i++;
		}
		else
		{
			array[k] = right_vector[j];
			this->bricks->bricks[k]->setTextInt(array[k]);
			this->renderWithBreak(window, PAUSE_TIMER);
			j++;
		}
		k++;
	}

	//Filling the left leftovers
	while (i < left_size)
	{
		array[k] = left_vector[i];
		this->bricks->bricks[k]->setTextInt(array[k]);
		this->renderWithBreak(window, PAUSE_TIMER);
		i++;
		k++;
	}

	//Filling the right leftovers
	while (j < right_size)
	{
		array[k] = right_vector[j];
		this->bricks->bricks[k]->setTextInt(array[k]);
		this->renderWithBreak(window, PAUSE_TIMER);
		j++;
		k++;
	}
}

void Algorithms::Merge_Sort(sf::RenderWindow& window, std::vector<int>& array, int left_index, int right_index)
{
	int mid_index;

	//Divide
	if (left_index < right_index)
	{
		mid_index = left_index + (right_index - left_index) / 2;

		Merge_Sort(window, array, left_index, mid_index);
		Merge_Sort(window, array, mid_index + 1, right_index);

		merge(window, array, left_index, mid_index, right_index);
	}
}

//For quick sort
int partition(sf::RenderWindow& window, std::vector<int>& array, int low, int high)
{
	int pivot = array[array.size()];

	int i = low - 1;

	for(int j = low ; j < high; j++)
	{
		if(array[j] <= pivot)
		{
			this->setBricksColorRed(i,j);
			this->renderWithBreak(window, 200);
			this->swap(&array[i], &array[j]);
			this->bricks.bricks[i].setTextInt(array[i]);
			this->bricks.bricks[j].setTextInt(array[j]);
			this->renderWithBreak(window, 200);
			this->setBricksColorBlack(i, j);
			i++;
		}
	}

	this->setBricksColorRed(i + 1, high);
	this->renderWithBreak(window, 200);
	this->swap(&array[i + 1], &array[high]);
	this->bricks.bricks[i + 1].setTextInt(array[i + 1]);
	this->bricks.bricks[high].setTextInt(array[high]);
	this->renderWithBreak(window, 200);
	this->setBricksColorBlack(i + 1, high);

	return i + 1;
}

void Quick_Sort(sf::RenderWindow& window, std::vector<int>& array, int low, int high)
{
	if(low < high)
	{
		int x = partition(window, array, low, high);
		//Stackoverflow ???
		Quick_Sort(window, array, low, x - 1);
		Quick_Sort(window, array, x + 1, high);
	}
}


void Algorithms::currentSelectedAlgo(std::vector<int>& array, sf::RenderWindow& window)
{
	if (!this->algoFinished)
	{
		//this->Bubble_Sort(array, window);

		//this->Selection_Sort(array, window);

		//this->Merge_Sort(window, array, 0 , static_cast<int>(array.size()) - 1);

		this->Quick_Sort(window, array, 0, array.size());

		this->algoFinished = true;
	}
}

void Algorithms::renderBrickManager(sf::RenderTarget& target)
{
	this->bricks->render(target);
}

void Algorithms::render(sf::RenderWindow& target)
{
	target.clear(sf::Color(150, 150, 150, 255));

	this->renderBrickManager(target);

	target.display();
}

void Algorithms::renderWithBreak(sf::RenderWindow& target, unsigned int milliseconds)
{
	this->render(target);
	sf::sleep(sf::milliseconds(milliseconds));
}

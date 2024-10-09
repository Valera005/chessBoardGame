#include "Utils.h"

sf::Font Utils::RobotoFont{};

void Utils::InitialiseUtils()
{
	if (!RobotoFont.loadFromFile(R"(Resources\Fonts\Roboto-Medium.ttf)"))
	{
		throw std::exception("Couldn't load the Font File");
	}
	
}

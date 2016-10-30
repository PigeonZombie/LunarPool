#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class EcranDebut
{
private:
	Text titre;
	Text instruction;
	Text credits;
	Font fontTitre;
	Font fontAutres;
	Sprite background;
	Texture tBackground;
public:
	EcranDebut();
	~EcranDebut();
	const Text& GetTitre();
	const Text& GetCredits();
	const Text& GetInstructions();
	const Sprite& GetBackground();
};


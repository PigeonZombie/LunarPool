#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class EcranFin
{
private:
	Text resultatFinPartie;
	Text question;
	Font fontPrincipal;
	Font fontAutres;
	Sprite background;
	Texture tBackground;
public:
	EcranFin();
	~EcranFin();
	const Text& GetFinPartie();
	const Text& GetQuestion();
	const Sprite& GetBackground();
	void SetFinPartie(const std::string finPartie);
};


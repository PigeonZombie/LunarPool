#include "EcranFin.h"
#include "Constantes.h"


EcranFin::EcranFin()
{
	fontPrincipal.loadFromFile("Fonts\\Starjedi.ttf");
	resultatFinPartie.setFont(fontPrincipal);
	resultatFinPartie.setString("Dommage...");
	resultatFinPartie.setPosition(60, 60);
	resultatFinPartie.setCharacterSize(70);
	resultatFinPartie.setColor(Color::Yellow);

	fontAutres.loadFromFile("Fonts\\PressStart2P-Regular.ttf");
	question.setFont(fontAutres);
	question.setString("Voulez-vous rejouer? [Y\\N]");
	question.setPosition(LARGEUR / 6, 250);
	question.setCharacterSize(22);
	question.setColor(Color::White);

	tBackground.loadFromFile("Sprites\\BackgroundLunaire.png");
	background.setTexture(tBackground);
}

EcranFin::~EcranFin()
{
}

const Text& EcranFin::GetFinPartie()
{
	return resultatFinPartie;
}
const Text& EcranFin::GetQuestion()
{
	return question;
}
const Sprite& EcranFin::GetBackground()
{
	return background;
}

void EcranFin::SetFinPartie(const std::string finPartie)
{
	resultatFinPartie.setString(finPartie.c_str());
}

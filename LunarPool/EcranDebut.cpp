#include "EcranDebut.h"
#include "Constantes.h"

EcranDebut::EcranDebut()
{
	fontTitre.loadFromFile("Fonts\\Starjedi.ttf");
	titre.setString("Lunar Pool");
	titre.setCharacterSize(70);
	titre.setPosition(LARGEUR / 4+50, 100);
	titre.setColor(Color::Yellow);
	titre.setFont(fontTitre);

	fontAutres.loadFromFile("Fonts\\PressStart2P-Regular.ttf");
	instruction.setString("Appuyez sur \"espace\" pour commencer");
	instruction.setCharacterSize(25);
	instruction.setPosition(LARGEUR / 12, 300);
	instruction.setColor(Color::White);
	instruction.setFont(fontAutres);

	credits.setString("Travail pratique 1 présenté par Alicia Lamontagne");
	credits.setPosition(150, HAUTEUR - 50);
	credits.setCharacterSize(15);
	credits.setColor(Color::White);
	credits.setFont(fontAutres);

	tBackground.loadFromFile("Sprites\\BackgroundLunaire.png");
	background.setTexture(tBackground);

}


EcranDebut::~EcranDebut()
{
}

const Text& EcranDebut::GetTitre()
{
	return titre;
}
const Text& EcranDebut::GetCredits()
{
	return credits;
}
const Text& EcranDebut::GetInstructions()
{
	return instruction;
}
const Sprite& EcranDebut::GetBackground()
{
	return background;
}

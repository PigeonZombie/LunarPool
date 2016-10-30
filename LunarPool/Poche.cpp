#include "Poche.h"
Poche::Poche()
{

}
Poche::Poche(const float _x, const float _y, const float diametre)
{
	x = _x;
	y = _y;
	tPoche.loadFromFile("Sprites\\Poche.png");
	largeur = diametre;
	hauteur = diametre;
	rectanglePoche = IntRect(x, y, largeur, hauteur);
}

Poche::~Poche()
{
}

float Poche::GetX()const
{
	return x;
}
void Poche::SetX(const float _x)
{
	x = _x;
}
float Poche::GetY()const
{
	return y;
}

void Poche::SetY(const float _y)
{
	y = _y;
}

float Poche::GetLargeur() const
{
	return largeur;
}
float Poche::GetHauteur() const
{
	return hauteur;
}
IntRect Poche::GetRectangle() const
{
	return rectanglePoche;
}


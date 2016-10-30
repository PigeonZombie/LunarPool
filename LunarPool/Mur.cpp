#include "Mur.h"

Mur::Mur()
{

}

Mur::Mur(const float _x, const float _y, const float _largeur, const float _hauteur)
{
	x = _x;
	y = _y;
	largeur = _largeur;
	hauteur = _hauteur;
	rectangleMur = IntRect(x, y, largeur, hauteur);
}


Mur::~Mur()
{
}

float Mur::GetX() const
{
	return x;
}
float Mur::GetY() const
{
	return y;
}
float Mur::GetLargeur() const
{
	return largeur;
}
float Mur::GetHauteur() const
{
	return hauteur;
}
IntRect Mur::GetRect()const
{
	return rectangleMur;
}



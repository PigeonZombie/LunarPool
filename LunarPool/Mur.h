#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;
class Mur
{
private:
	float x;
	float y;
	float largeur;
	float hauteur;
	IntRect rectangleMur;
public:
	Mur();
	Mur(const float _x, const float _y, const float largeur, const float hauteur);
	~Mur();
	float GetX() const;
	float GetY() const;
	float GetLargeur() const;
	float GetHauteur() const;
	IntRect GetRect() const;
};


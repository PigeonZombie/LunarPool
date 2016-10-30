#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;
class Poche
{
private:
	float x;
	float y;
	float largeur;
	float hauteur;
	Texture tPoche;
	IntRect rectanglePoche;
public:
	Poche();
	Poche(const float _x, const float _y, const float diametre);
	~Poche();
	float GetX() const;
	void SetX(const float _x);
	void SetY(const float _y);
	float GetY() const;
	float GetLargeur()const;
	float GetHauteur()const;
	IntRect GetRectangle()const;
};


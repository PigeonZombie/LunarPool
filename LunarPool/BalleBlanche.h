#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include "Balle.h"
#include "Mur.h"
#include "Poche.h"

using namespace sf;
class BalleBlanche
{
private:
	float x;
	float y;
	float largeur;
	float hauteur;
	float vitesseX;
	float vitesseY;
	float startX;
	float startY;
	float angle;
	IntRect rectangleBalleBlanche;
	string tBalleBlanche;
	bool arret;
	Vector2f mouvement;
	void TesterArret();
	Vector2f GetNewMouvement();
	void ResoudreCollision(Balle &autreBalle);
	Vector2f CalculerVecteurUnitaire(Vector2f normale);
	//----------------
	void AjusterChevauchement(Balle& autreBalle);
public:
	BalleBlanche();
	BalleBlanche(const float _x, const float _y);
	~BalleBlanche();
	float GetAngle() const;
	void SetAngle(const float _angle);
	float GetX() const;
	void SetX(const float _x);
	float GetY()const;
	void SetY(const float _y);
	void SetVitesse(const float _vitesse);
	Vector2f GetMouvement()const;
	void SetMouvement(const Vector2f mouvement);
	float GetLargeur()const;
	float GetHauteur()const;
	string GetTexture()const;
	IntRect GetRectangle()const;
	
	bool CollisionAvecMur(Mur mur []);
	bool CollisionAvecPoche(Poche poche [], Balle autresBalles[]);
	bool CollisionAvecBalle(Balle autreBalle []);
	void Deplacer();
	bool GetArret();
};


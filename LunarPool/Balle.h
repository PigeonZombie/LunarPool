#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>
#include "Mur.h"
#include "Poche.h"

using namespace sf;
using namespace std;
class Balle
{
private:
	float x;
	float y;
	float largeur;
	float hauteur;
	IntRect rectangleBalle;
	int numero;
	string tBalle;
	Vector2f mouvement;
	bool arret;
	float vitesseX;
	float vitesseY;
	void TesterArret();
	float angle;
	Vector2f GetNewMouvement();
	void ResoudreCollision(Balle &autreBalle);
	Vector2f CalculerVecteurUnitaire(Vector2f normale);
	void AjusterChevauchement(Balle& autreBalle);
public:
	Balle();
	//nouv param
	Balle(const float _x, const float _y, const int numero, const float diametre);
	~Balle();
	float GetX() const;
	void SetX(const float _x);
	float GetY() const;
	void SetY(const float _y);
	float GetLargeur() const;
	float GetHauteur() const;
	int GetNumero() const;
	IntRect GetRectangle() const;
	string GetTexture() const;
	// type retour, nb params
	bool CollisionAvecMur(Mur mur [], int nbElements);
	bool CollisionAvecBalle(Balle& autreBalle);
	// nb params
	bool CollisionAvecPoche(Poche poche[], int nbElements);
	Vector2f GetMouvement() const;
	void SetMouvement(const Vector2f _mouvement);
	void Deplacer();
	bool GetArret() const;
	void SetRectangle(const IntRect rect);

};


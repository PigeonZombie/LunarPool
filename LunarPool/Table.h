#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>
#include "Poche.h"
#include "BalleBlanche.h"
#include "Balle.h"
#include "Mur.h"
#include "TableauAffichage.h"

using namespace sf;
using namespace std;
class Table
{
private:
	float x;
	float y;
	float largeur;
	float hauteur;
	//Texture tTable;
	float donnees[69];
	bool ReadFromFile(std::string fichier, int nbElements);
	Poche poches[6];
	Balle balles[10];
	Mur murs[8];
	BalleBlanche blanche;
	TableauAffichage tableau;
	string son;
	int vies;
	int score;
	int sequence;
	int puissance;
	int coupsRestants;
	bool balleEntree;
	bool testSequence;
	int nbBallesArretees;
public:
	Table();
	Table(const string niveau, const int _vies, const int _score, const int _sequence, const int puissance);
	~Table();
	float GetX() const;
	float GetY() const;
	float GetLargeur() const;
	float GetHauteur() const;
//	Texture GetTexture();
	const Poche& GetPoche(const int index);
	Balle& GetBalle(const int index);
	BalleBlanche& GetBlanche();
	const Mur& GetMur(const int index);
	TableauAffichage& GetTableau();
	void VerifierToutesCollisions();
	bool NiveauTermine();
	string GetSon() const;
	void SetSon(const string _son);
	void CalculerSequence();
	void ResetSequence();
	int GetNbBallesArretees()const;
	int GetVies() const;
	int GetSequence() const;
	int GetScore() const;
	int GetPuissance() const;
};


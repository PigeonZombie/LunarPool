#pragma once
#include <string>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;
class TableauAffichage
{
private:
	int vies;
	int score;
	int sequence;
	int niveau;
	int puissance;
	int coupsRestants;
	Font font;
	Text textPuissance;
	Text textVies;
public:
	TableauAffichage();
	TableauAffichage(const int niveau, const int vies, const int score, const int sequence, const int puissance);
	~TableauAffichage();
	int GetVies()const;
	void SetVies(const int _vies);
	int GetScore()const;
	void SetScore(const int _score);
	int GetBallesRestantes()const;
	void SetBallesRestantes(const int nbBalles);
	int GetSequence()const;
	void SetSequence(const int _sequence);
	int GetNiveau()const;
	void SetNiveau(const int _niveau);
	string GetPuissance()const;
	void SetPuissance(const int _puissance);
	Text GetTextPuissance()const;
	Text GetTextVies()const;
	Text GetTextCoupsRestants()const;
	Text GetTextScore()const;
	Text GetTextSequence()const;
	Text GetTextNiveau()const;
};


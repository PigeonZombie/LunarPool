#include "TableauAffichage.h"
#include "Constantes.h"

TableauAffichage::TableauAffichage()
{

}

TableauAffichage::TableauAffichage(const int _niveau, const int _vies, const int _score, const int _sequence, const int _puissance)
{
	font.loadFromFile("Fonts\\MotorwerkOblique.ttf");
	vies = _vies;
	score = _score;
	sequence = _sequence;
	niveau = _niveau;
	puissance = _puissance;
	coupsRestants = 3;
}

TableauAffichage::~TableauAffichage()
{
}

int TableauAffichage::GetVies()const
{
	return vies;
}
void TableauAffichage::SetVies(const int _vies)
{
	vies = _vies;
}
int TableauAffichage::GetScore()const
{
	return score;
}
void TableauAffichage::SetScore(const int _score)
{
	score = _score;
}
int TableauAffichage::GetBallesRestantes()const
{
	return coupsRestants;
}
void TableauAffichage::SetBallesRestantes(const int nbCoups)
{
	coupsRestants = nbCoups;
}
int TableauAffichage::GetSequence()const
{
	return sequence;
}
void TableauAffichage::SetSequence(const int _sequence)
{
	sequence = _sequence;
}
int TableauAffichage::GetNiveau()const
{
	return niveau;
}
void TableauAffichage::SetNiveau(const int _niveau)
{
	niveau = _niveau;
}
string TableauAffichage::GetPuissance()const
{
	string force = std::to_string(puissance);
	return force;
}
void TableauAffichage::SetPuissance(const int _puissance)
{
	puissance = _puissance;
}

Text TableauAffichage::GetTextPuissance()const
{
	Text t;
	t.setString("Puissance: " + to_string(puissance));
	t.setPosition(LARGEUR-300, 40);
	t.setColor(Color::Cyan);
	t.setFont(font);
	return t;
}
Text TableauAffichage::GetTextVies()const
{
	Text t;
	t.setString("Vies: " + to_string(vies));
	t.setPosition(LARGEUR/2-60, 45);
	t.setColor(Color::Red);
	t.setFont(font);
	return t;
}
Text TableauAffichage::GetTextCoupsRestants()const
{
	Text t;
	t.setString("Coups restants: "+to_string(coupsRestants));
	t.setPosition(LARGEUR-300, 10);
	t.setColor(Color::Green);
	t.setFont(font);
	return t;
}

Text TableauAffichage::GetTextScore()const
{
	Text t;
	t.setString("Score: " + to_string(score));
	t.setPosition(30, 20);
	t.setColor(Color::Magenta);
	t.setFont(font);
	return t;
}
Text TableauAffichage::GetTextSequence()const
{
	Text t;
	t.setString("Sequence: " + to_string(sequence));
	t.setPosition(LARGEUR/2-100, 25);
	t.setColor(Color::Green);
	t.setFont(font);
	return t;
}
Text TableauAffichage::GetTextNiveau()const
{
	Text t;
	t.setString("Niveau " + to_string(niveau));
	t.setPosition(LARGEUR/2-70, 5);
	t.setColor(Color::White);
	t.setFont(font);
	return t;
}

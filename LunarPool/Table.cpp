#define _USE_MATH_DEFINES
#include "Table.h"
#include "Constantes.h"

Table::Table()
{

}
Table::Table(const string _niveau, const int _vies, const int _score, const int _sequence, const int _puissance)
{
	vies = _vies;
	score = _score;
	sequence = _sequence;
	puissance = _puissance;
	coupsRestants = 3;
	if (_niveau == "Niveaux\\niveau1.txt")
	{
		tableau = TableauAffichage(1, vies, score, sequence, puissance);
		ReadFromFile(_niveau, 52);
		x = donnees[0];
		y = donnees[1];
		int index = 2;
		int numero = 1;
		for (int i = 0; i < NB_POCHES; i++)
		{
			poches[i] = Poche(donnees[index], donnees[index + 1],50);
			index += 2;
		}
		for (int j = 0; j < NB_BALLES; j++)
		{
			balles[j] = Balle(donnees[index], donnees[index + 1], numero, DIAMETRE);
			index += 2;
			numero++;
		}
		blanche = BalleBlanche(donnees[index], donnees[index+1]);
		index += 2;
		for (int k = 0; k < NB_MURS_NIV1; k++)
		{
			murs[k] = Mur(donnees[index], donnees[index + 1], donnees[index + 2], donnees[index + 3]);
			index += 4;
		}
		for (int l = NB_MURS_NIV1; l < NB_MURS_NIV2; l++)
		{
			murs[l] = Mur(-1, -1, 0, 0);
		}
	}
	else
	{
		tableau = TableauAffichage(2, vies, score, sequence, puissance);
		ReadFromFile(_niveau, 69);
		x = donnees[0];
		y = donnees[1];
		int index = 2;
		int numero = 1;
		for (int j = 0; j < NB_POCHES; j++)
		{
			poches[j] = Poche(donnees[index], donnees[index + 1],50);
			index += 2;
		}
		for (int l = NB_POCHES; l < NB_POCHES; l++)
		{
			poches[l].SetX(-1);
			poches[l].SetY(-1);
		}
		for (int k = 0; k < NB_BALLES; k++)
		{
			balles[k] = Balle(donnees[index], donnees[index + 1], numero, DIAMETRE);
			index += 2;
			numero++;
		}
		blanche = BalleBlanche(donnees[index], donnees[index + 1]);
		index += 2;
		for (int k = 0; k < NB_MURS_NIV2; k++)
		{
			murs[k] = Mur(donnees[index], donnees[index + 1], donnees[index + 2], donnees[index + 3]);
			index += 4;
		}
	}
	balleEntree = false;
	testSequence = false;
}


Table::~Table()
{

}

float Table::GetX()const
{
	return x;
}
float Table::GetY()const
{
	return y;
}
float Table::GetLargeur()const
{
	return largeur;
}
float Table::GetHauteur()const
{
	return hauteur;
}

bool Table::ReadFromFile(std::string file, int nbElements)
{
	son = "";
	ifstream fichier(file);
	if (fichier.good())
	{
		string ligne = "";
		size_t pos;
		int index = 0;
		while (!fichier.eof())
		{
			if (index < nbElements-1)
			{
				fichier >> ligne;
				pos = ligne.find(",");
				ligne.substr(0, pos);
				istringstream(ligne) >> donnees[index];
				index++;
				ligne = ligne.substr(pos+1);
				istringstream(ligne) >> donnees[index];
				index++;
			}
			else
			{
				fichier >> ligne;
			//	if (!tTable.loadFromFile(ligne))
				//	return false;
			}
		}
		fichier.close();
		return true;
	}
	return false;
}

const Poche& Table::GetPoche(const int index)
{
	return poches[index];
}

Balle& Table::GetBalle(const int index)
{
	return balles[index];
}

BalleBlanche& Table::GetBlanche()
{
	return blanche;
}

const Mur& Table::GetMur(int index)
{
	return murs[index];
}

void Table::VerifierToutesCollisions()
{
	/// Les collisions de la balle blanche
	
	blanche.CollisionAvecMur(murs);
	if (blanche.CollisionAvecPoche(poches, balles))
	{
		son = "Chewie";
		vies--;
		tableau.SetVies(vies);
		sequence = 0;
		tableau.SetSequence(sequence);
	}
	if(blanche.CollisionAvecBalle(balles))
	{
		son = "Lightsaber";
	}
	/// Les collisions des balles
	for (int i = 0; i < NB_BALLES; i++)
	{
		balles[i].CollisionAvecMur(murs,NB_MURS_NIV2);
	}
	for (int j = 0; j < NB_BALLES - 1; j++)
	{
		for (int k = j + 1; k < NB_BALLES; k++)
		{
			if (balles[j].GetX()!=-1 && balles[j].CollisionAvecBalle(balles[k]))
			{
				//j = 0;
				//son = "Lightsaber";
			}
		}
	}
	nbBallesArretees = 0;
	for (int l = 0; l < NB_BALLES; l++)
	{
		if (balles[l].CollisionAvecPoche(poches,NB_POCHES))
		{
			sequence++;
			balleEntree = true;
			testSequence = true;
			CalculerSequence();
			score += balles[l].GetNumero() * 10 * sequence;
			tableau.SetScore(score);
			coupsRestants = 3;
			tableau.SetBallesRestantes(coupsRestants);
			son = "R2D2";
		}
		if (balles[l].GetArret())
			nbBallesArretees++;
	}
	if (nbBallesArretees == NB_BALLES && blanche.GetArret() == true)
		testSequence = true;

}

bool Table::NiveauTermine()
{
	if (vies < 0)
	{
		return true;
	}
	for (int i = 0; i < NB_BALLES; i++)
	{
		if (balles[i].GetX() != -1)
			return false;
	}
	return true;
}

TableauAffichage& Table::GetTableau()
{
	return tableau;
}

string Table::GetSon()const
{
	return son;
}

void Table::SetSon(const string _son)
{
	son = _son;
}

void Table::CalculerSequence()
{
	if (testSequence==true && balleEntree==true)
	{
		tableau.SetSequence(sequence);
		testSequence = false;
	}
	else if (testSequence==true && balleEntree == false)
	{
		sequence = 0;
		tableau.SetSequence(sequence);
	}
}

void Table::ResetSequence()
{
	balleEntree=false;

	testSequence = false;
	if (coupsRestants>0)
		coupsRestants--;
	else
	{
		vies--;
		coupsRestants = 3;
		tableau.SetVies(vies);
	}
	tableau.SetBallesRestantes(coupsRestants);
}

int Table::GetNbBallesArretees()const
{
	return nbBallesArretees;
}

int Table::GetVies()const
{
	return vies;
}
int Table::GetSequence()const
{
	return sequence;
}
int Table::GetScore()const
{
	return score;
}
int Table::GetPuissance()const
{
	return puissance;
}

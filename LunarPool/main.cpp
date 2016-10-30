#define _USE_MATH_DEFINES
#define WM_MOUSEWHEEL
#include <vld.h>
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Constantes.h"
#include "Table.h"
#include <string>
#include "TableauAffichage.h"
#include "EcranDebut.h"
#include "EcranFin.h"

using namespace sf;

RenderWindow mainWin(VideoMode(LARGEUR, HAUTEUR, 32), "Lunar Pool");
View view(mainWin.getDefaultView());
Event event;
EcranDebut ecranDebut;
Table table1;
Sprite background;
Texture tBackground;
Sprite table;
Texture tTable;
Sprite poches[NB_POCHES];
Texture tPoches;
Sprite balles[NB_BALLES];
Texture tBalles[NB_BALLES];
Sprite blanche;
Texture tBlanche;
bool clicked = false;
bool puissanceChangee = false;
int niveau = 0;
Vector2f cible;
float angle;
int puissance = SPEED;
RectangleShape murs[NB_MURS_NIV2];
// Tutoriel sur comment utiliser des sons en SFML: http://www.sfml-dev.org/tutorials/2.0/audio-sounds-fr.php
SoundBuffer buffer;
Sound son;
bool gameStarted;
bool gameOver;
EcranFin ecranFin;
bool Init();
void GetInputs();
void Update();
void Draw();
void PlaySound(string sound);

void PlaySound(string sound)
{
	if (sound == "Lightsaber")
	{
		buffer.loadFromFile("Sons\\Lightsaber.wav");
	}
	else if (sound == "Chewie")
	{
		buffer.loadFromFile("Sons\\Chewie.ogg");
	}
	else if (sound=="Theme")
	{
		buffer.loadFromFile("Sons\\Theme.ogg");
	}
	else if (sound=="R2D2")
	{
		buffer.loadFromFile("Sons\\R2D2.ogg");
	}
	else
	{
		buffer.loadFromFile("Sons\\The Choice.ogg");
	}
	son.setBuffer(buffer);
	son.play();
	table1.SetSon("");
}

int main()
{
	if (!Init())
	{
		return EXIT_FAILURE;
	}

	while (mainWin.isOpen())
	{
		GetInputs();
		Update();
		Draw();
	}

	return EXIT_SUCCESS;
}

bool Init()
{
	mainWin.setVerticalSyncEnabled(true);
	mainWin.setFramerateLimit(60);

	gameStarted = false;
	gameOver = false;
	niveau = 0;
	son.stop();

	if (!tBackground.loadFromFile("Sprites\\BackgroundLunaire.png"))
	{
		return false;
	}
	background.setTexture(tBackground);

	// Initialisation de la table 
	table1 = Table("Niveaux\\niveau1.txt", STARTING_LIVES, 0, 0, SPEED);
	niveau++;
	if (!tTable.loadFromFile("Sprites\\Table1.png"))
	{
		return false;
	}
	table.setTexture(tTable);
	table.setPosition(table1.GetX(), table1.GetY());
	// Initialisation des poches
	int index = 0;
	if (!tPoches.loadFromFile("Sprites\\Poche.png"))
	{
		return false;
	}
	for (int i = 0; i < NB_POCHES; i++)
	{
		poches[i].setTexture(tPoches);
		poches[i].setPosition(table1.GetPoche(i).GetX(), table1.GetPoche(i).GetY());
	}
	//Initialisation des balles
	for (int j = 0; j < NB_BALLES; j++)
	{
		if (!tBalles[j].loadFromFile(table1.GetBalle(j).GetTexture()))
		{
			return false;
		}
		balles[j].setTexture(tBalles[j]);
		balles[j].setPosition(table1.GetBalle(j).GetX(), table1.GetBalle(j).GetY());
	}
	//Initialisation de la blanche
	if (!tBlanche.loadFromFile(table1.GetBlanche().GetTexture()))
	{
		return false;
	}
	blanche.setTexture(tBlanche);
	blanche.setPosition(table1.GetBlanche().GetX(), table1.GetBlanche().GetY());

	return true;
}


void GetInputs()
{
	while (mainWin.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			mainWin.close();
		}
	} 
	if (gameOver == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			gameStarted = true;
			son.stop();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// Ne pas autoriser de garder le bouton de la souris enfoncé
			if (!clicked)
			{
				clicked = true;
				cible.x = sf::Mouse::getPosition(mainWin).x;
				cible.y = sf::Mouse::getPosition(mainWin).y;
				angle = atanf((cible.y - blanche.getPosition().y) / (cible.x - blanche.getPosition().x));
				if (cible.x < blanche.getPosition().x)
				{
					angle += M_PI;
				}
				table1.GetBlanche().SetAngle(angle);
				table1.GetBlanche().SetMouvement(Vector2f(cible.x, cible.y));
				table1.GetBlanche().SetVitesse(puissance);
				//ticketToTestCollisions = true;
				table1.ResetSequence();
			}
		}
		puissanceChangee = false;
		if (sf::Keyboard::isKeyPressed(Keyboard::W))
		{
			if (puissance < MAX_SPEED)
			{
				puissance++;
				puissanceChangee = true;
			}
		}
		else if (sf::Keyboard::isKeyPressed(Keyboard::S))
		{
			if (puissance > 1)
			{
				puissance--;
				puissanceChangee = true;
			}
		}
	}
	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Y))
			Init();
		else if (Keyboard::isKeyPressed(Keyboard::N))
			mainWin.close();
	}

}

void Update()
{
	//Ajustement de la puissance de la balle blanche
	if (puissanceChangee)
	{
		table1.GetBlanche().SetVitesse(puissance);
		table1.GetTableau().SetPuissance(puissance);
		puissanceChangee = false;
	}
	// Mise à jour de la balle blanche
	if (clicked)
	{
		table1.GetBlanche().Deplacer();
		int x = table1.GetBlanche().GetX();
		int y = table1.GetBlanche().GetY();
		blanche.setPosition(table1.GetBlanche().GetX(), table1.GetBlanche().GetY());
		if (table1.GetBlanche().GetArret() && table1.GetNbBallesArretees()==NB_BALLES)
			clicked = false;
		else
			clicked = true;
	}
	table1.CalculerSequence();
	table1.VerifierToutesCollisions();

	for (int i = 0; i < NB_BALLES; i++)
	{
		table1.GetBalle(i).Deplacer();
		balles[i].setPosition(table1.GetBalle(i).GetX(), table1.GetBalle(i).GetY());
	}
	if (table1.NiveauTermine())
	{
		if (table1.GetVies() < 0)
		{
			gameOver = true;
			ecranFin.SetFinPartie("Dommage...");
		}
		else if (niveau == 2)
		{
			gameOver = true;
			ecranFin.SetFinPartie("Félicitations!");
		}
		else
		{
			table1 = Table("Niveaux\\niveau2.txt", table1.GetVies(), table1.GetScore(), table1.GetSequence(), table1.GetPuissance());
			tTable.loadFromFile("Sprites\\Table2.png");
			for (int j = 0; j < NB_POCHES; j++)
			{
				poches[j].setPosition(table1.GetPoche(j).GetX(), table1.GetPoche(j).GetY());
			}
			niveau++;
		}
	}
	if (table1.GetSon() != "" && gameOver==false)
	{
		PlaySound(table1.GetSon());
	}
	//_puissance.setString("Puissance: "+table1.GetTableau().GetPuissance());

}

void Draw()
{
	///Écran de début de partie
	if (gameStarted == false)
	{
		mainWin.clear();
		if (son.getStatus() == Sound::Stopped)
			PlaySound("Theme");
		mainWin.draw(ecranDebut.GetBackground());
		mainWin.draw(ecranDebut.GetTitre());
		mainWin.draw(ecranDebut.GetInstructions());
		mainWin.draw(ecranDebut.GetCredits());
	}
	///Écran de fin de partie
	else if (gameOver == true)
	{
		mainWin.clear();
		if (son.getStatus() == Sound::Stopped)
		{
			if (ecranFin.GetFinPartie().getString() == "Dommage...")
				PlaySound("The Choice");
			else
				PlaySound("Theme");
		}
			
		mainWin.draw(ecranFin.GetBackground());
		mainWin.draw(ecranFin.GetFinPartie());
		mainWin.draw(ecranFin.GetQuestion());
	}
	else
	{
		///Écran de jeu
		mainWin.clear();
		mainWin.draw(background);
		mainWin.draw(table);
		for (int j = 0; j < NB_BALLES; j++)
		{
			if (table1.GetBalle(j).GetX() != -1)
				mainWin.draw(balles[j]);
		}
		for (int i = 0; i < NB_POCHES; i++)
		{
			if (table1.GetPoche(i).GetX() != -1)
				mainWin.draw(poches[i]);
		}
		mainWin.draw(blanche);
		mainWin.draw(table1.GetTableau().GetTextPuissance());
		mainWin.draw(table1.GetTableau().GetTextVies());
		mainWin.draw(table1.GetTableau().GetTextCoupsRestants());
		mainWin.draw(table1.GetTableau().GetTextNiveau());
		mainWin.draw(table1.GetTableau().GetTextScore());
		mainWin.draw(table1.GetTableau().GetTextSequence());
	}

	mainWin.display();
}

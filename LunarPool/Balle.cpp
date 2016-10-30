#define _USE_MATH_DEFINES
#include "Balle.h"
#include "Constantes.h"

Balle::Balle()
{

}

Balle::Balle(float _x, float _y, int _numero, const float diametre)
{
	x = _x;
	y = _y;
	numero = _numero;
	stringstream convert;
	convert << numero;
	tBalle = "Sprites\\"+convert.str() + ".png";
	largeur = diametre;
	hauteur = diametre;
	rectangleBalle = IntRect(x, y, largeur, hauteur);
	vitesseX = SPEED;
	vitesseY = SPEED;
	angle = 0;
	mouvement.x = 0;
	mouvement.y = 0;
}

Balle::~Balle()
{
}

float Balle::GetX() const
{
	return x;
}
void Balle::SetX(float _x)
{
	x = _x;
	rectangleBalle = IntRect(x, y, largeur, hauteur);
}
float Balle::GetY() const
{
	return y;
}
void Balle::SetY(float _y)
{
	y = _y;
	rectangleBalle = IntRect(x, y, largeur, hauteur);
}
float Balle::GetLargeur() const
{
	return largeur;
}
float Balle::GetHauteur() const
{
	return hauteur;
}
int Balle::GetNumero() const
{
	return numero;
}
IntRect Balle::GetRectangle() const
{
	return rectangleBalle;
}
void Balle::SetRectangle(IntRect rect)
{
	rectangleBalle = rect;
}
string Balle::GetTexture() const
{
	return tBalle;
}
bool Balle::CollisionAvecMur(Mur mur[], int nbElements)
{
	bool collision = false;
	Vector2f nouveauMouvement;
	float nouvelAngle = 0;
	for (int i = 0; i < nbElements; i++)
	{
		if (rectangleBalle.intersects(mur[i].GetRect()))
		{
			collision = true;
			if (mur[i].GetLargeur()<mur[i].GetHauteur())
			{
				nouveauMouvement.x = mouvement.x*-1;
				nouveauMouvement.y = mouvement.y;
				vitesseX *= -1;
				while (rectangleBalle.intersects(mur[i].GetRect()))
				{
					if (nouveauMouvement.x >= 0)
						x += 2;
					else
						x -= 2;
					rectangleBalle = IntRect(x, y, largeur, hauteur);
				}
			}
			else
			{
				nouveauMouvement.x = mouvement.x;
				nouveauMouvement.y = mouvement.y*-1;
				vitesseY *= -1;
				while (rectangleBalle.intersects(mur[i].GetRect()))
				{
					if (nouveauMouvement.y >= 0)
						y += 2;
					else
						y -= 2;
					rectangleBalle = IntRect(x, y, largeur, hauteur);
				}
			}
			SetMouvement(nouveauMouvement);
		}

	}
	return collision;
}
bool Balle::CollisionAvecBalle(Balle& autreBalle)
{
	bool collision = false;
	float dX = 0;
	float dY = 0;
	float distance = 0;
	//for (int i = 0; i < NB_BALLES; i++)
	{
		dX = x - autreBalle.GetX();
		dY = y - autreBalle.GetY();
		distance = sqrt(dX * dX + dY * dY);
		if (distance <= largeur)
		{
			arret = false;
			collision = true;
			ResoudreCollision(autreBalle);
			AjusterChevauchement(autreBalle);
			//break;
		}
	}
	return collision;
}
bool Balle::CollisionAvecPoche(Poche poche[],int nbElements)
{
	bool collision = false;
	for (int i = 0; i < nbElements; i++)
	{
		if (rectangleBalle.intersects(poche[i].GetRectangle()))
		{
			arret = true;
			x = -1;
			y = -1;
			mouvement.x = 0;
			mouvement.y = 0;
			vitesseX = 0;
			vitesseY = 0;
			rectangleBalle = IntRect(x, y, largeur, hauteur);
			return true;
		}
	}
	return collision;
}
Vector2f Balle::GetMouvement() const
{
	return mouvement;
}

void Balle::SetMouvement(Vector2f _mouvement)
{
	mouvement = _mouvement;
}

void Balle::Deplacer()
{
	//mouvement.x = cos(angle) * vitesseX;
	//mouvement.y = sin(angle) * vitesseY;
	if (x != -1)
	{
		arret = false;
		x += GetNewMouvement().x;
		y += GetNewMouvement().y;
		TesterArret();
		rectangleBalle = IntRect(x, y, largeur, hauteur);
	}
}

void Balle::TesterArret()
{
	/*//Calcul de la vitesse actuelle actuelle (pythagore)
	float vitesseTotale = sqrt(mouvement.x * mouvement.x + mouvement.y * mouvement.y);

	//Si plus petite qu'un certain point, on arrête la balle
	if (!arret &&vitesseTotale < 0.6f)
	{
		arret = true;
		mouvement.x = 0.0f;
		mouvement.y = 0.0f;
		vitesseX = SPEED;
		vitesseY = SPEED;
	}*/
	if (abs(mouvement.x) < 0.6f)
	{
		mouvement.x = 0.0f;
	}

	if (abs(mouvement.y) < 0.6f)
	{
		mouvement.y = 0.0f;
	}

	//Si plus petite qu'un certain point, on arrête la balle
	if (mouvement.x == 0.0f && mouvement.y == 0.0f)
	{
		arret = true;
	}
}

Vector2f Balle::GetNewMouvement()
{
	mouvement.x *= FRICTION;
	mouvement.y *= FRICTION;
	vitesseX *= FRICTION;
	vitesseY *= FRICTION;
	return mouvement;
}

void Balle::ResoudreCollision(Balle &autreBalle)
{
	Vector2f vect1 = Vector2f(autreBalle.GetX(), autreBalle.GetY());
	Vector2f vect2 = Vector2f(x, y);
	Vector2f normale = vect1 - vect2;
	Vector2f vecteurUnitaire = CalculerVecteurUnitaire(normale);
	Vector2f tangenteUnitaire(-vecteurUnitaire.y, vecteurUnitaire.x);

	Vector2f vitesseNormale1 = (vecteurUnitaire.x * autreBalle.GetMouvement().x + vecteurUnitaire.y * autreBalle.GetMouvement().y) * vecteurUnitaire;
	Vector2f vitesseTangente1 = (tangenteUnitaire.x * this->GetMouvement().x + tangenteUnitaire.y * this->GetMouvement().y) * tangenteUnitaire;
	Vector2f vitesseNormale2 = (vecteurUnitaire.x * this->GetMouvement().x + vecteurUnitaire.y * this->GetMouvement().y) * vecteurUnitaire;
	Vector2f vitesseTangente2 = (tangenteUnitaire.x * autreBalle.GetMouvement().x + tangenteUnitaire.y * autreBalle.GetMouvement().y) * tangenteUnitaire;

	Vector2f nouveauMouvementBalle1 = Vector2f(vitesseNormale1.x + vitesseTangente1.x, vitesseNormale1.y + vitesseTangente1.y);
	if (mouvement.x < 0)
		angle -= normale.x;
	else
		angle += normale.x;
	SetMouvement(nouveauMouvementBalle1);
	//x += mouvement.x;
	//y += mouvement.y;
	rectangleBalle = IntRect(x, y, largeur, hauteur);
	Vector2f nouveauMouvementBalle2 = Vector2f(vitesseNormale2.x + vitesseTangente2.x, vitesseNormale2.y + vitesseTangente2.y);
	autreBalle.SetMouvement(nouveauMouvementBalle2);
	//autreBalle.SetX(autreBalle.GetX() + (nouveauMouvementBalle2.x));
	//autreBalle.SetY(autreBalle.GetY() + (nouveauMouvementBalle2.y));
	autreBalle.SetRectangle(IntRect(autreBalle.GetX(), autreBalle.GetY(), largeur, hauteur));
	/*while (rectangleBalle.intersects(autreBalle.GetRectangle()))
	{
		x += mouvement.x;
		y += mouvement.y;
		rectangleBalle = IntRect(x, y, largeur, hauteur);
		autreBalle.SetX(autreBalle.GetX() + (nouveauMouvementBalle2.x));
		autreBalle.SetY(autreBalle.GetY() + (nouveauMouvementBalle2.y));
		autreBalle.SetRectangle(IntRect(autreBalle.GetX(), autreBalle.GetY(), largeur, hauteur));
	}*/
}

Vector2f Balle::CalculerVecteurUnitaire(Vector2f normale)
{
	float pente = sqrt(normale.x * normale.x + normale.y * normale.y);

	//Si 0, ça provique une division par 0.
	if (pente != 0.0f)
	{
		return Vector2f(normale.x / pente, normale.y / pente);
	}

	return Vector2f(0.0f, 0.0f);
}

bool Balle::GetArret() const
{
	return arret;
}

void Balle::AjusterChevauchement(Balle& autreBalle)
{
	//AVEC CES TROIS LIGNES DE CODE ON CALCULE LA DISTANCE ENTRE LES DEUX BALLES
	float dX = x - autreBalle.GetX();
	float dY = y - autreBalle.GetY();
	float distance = sqrt(dX * dX + dY * dY);

	//S'IL Y A CHEVAUCHEMENT...
	if (distance < RAYON + RAYON)
	{
		//AVEC CES TROIS LIGNES DE CODE ET LE IF QUI SUIT ON CALCULE 
		//L'ANGLE ENTRE LES DEUX BALLES
		float diffX = autreBalle.GetX() - x;
		float diffY = autreBalle.GetY() - y;
		float angle = atanf(diffY / diffX);

		if (autreBalle.GetX() < x)
		{
			angle += M_PI;
		}
		//--FIN DU CALCUL DE L'ANGLE--//

		//ON OBTIENT LA DIFFÉRENCE ENTRE LA DISTANCE ACTUELLE DES DEUX BALLES
		//ET CELLE ENTRE LES DEUX BALLES QUAND ELLES SE TOUCHENT SANS SE CHEVAUCHER
		float difference = (RAYON + RAYON) - distance;

		//ON AUGMENTE LA DISTANCE EN DÉPLACANT LÉGÈREMENT AUTREBALLE SUIVANT L'AXE DE L'ANGLE ENTRE LES DEUX BALLES
		//autreBalle.setPosition(autreBalle.getPosition().x + difference * cos(angle), autreBalle.getPosition().y + difference * sin(angle));
		autreBalle.SetX(autreBalle.GetX() + difference*cos(angle));
		autreBalle.SetY(autreBalle.GetY() + difference*sin(angle));
	}
}

#define _USE_MATH_DEFINES
#include "BalleBlanche.h"
#include "Constantes.h"
BalleBlanche::BalleBlanche()
{
	
}

BalleBlanche::BalleBlanche(float _x, float _y)
{
	angle = 0;
	x = _x;
	y = _y;
	startX = _x;
	startY = _y;
	tBalleBlanche = "Sprites\\0.png";
	Texture temp;
	temp.loadFromFile(tBalleBlanche);
	largeur = temp.getSize().x;
	hauteur = temp.getSize().y;
	rectangleBalleBlanche = IntRect(_x, _y, largeur, hauteur);
	arret = true;
	vitesseX = SPEED;
	vitesseY = SPEED;
}

BalleBlanche::~BalleBlanche()
{
}

float BalleBlanche::GetX() const
{
	return x;

}
void BalleBlanche::SetX(const float _x)
{
	x = _x;
}
float BalleBlanche::GetY() const
{
	return y;
}
void BalleBlanche::SetY(const float _y)
{
	y = _y;
}
void BalleBlanche::SetVitesse(const float _vitesse)
{
	vitesseX = _vitesse;
	vitesseY = _vitesse;
	if (_vitesse > 0)
		arret = false;
	/*if (vitesseX < 0 || vitesseY <0)
	{
		if (vitesseX<0)
			vitesseX = -_vitesse;
		if (vitesseY < 0)
			vitesseY = -_vitesse;
	}
	else
	{
		vitesseX = _vitesse;
		vitesseY = _vitesse;
	}*/
}
float BalleBlanche::GetLargeur() const
{
	return largeur;
}
float BalleBlanche::GetHauteur() const
{
	return hauteur;
}
string BalleBlanche::GetTexture() const
{
	return tBalleBlanche;
}
IntRect BalleBlanche::GetRectangle() const
{
	return rectangleBalleBlanche;
}
bool BalleBlanche::CollisionAvecMur(Mur mur[])
{
	Vector2f nouveauMouvement;
	float nouvelAngle = 0;
	for (int i = 0; i < NB_MURS_NIV2; i++)
	{
		if (rectangleBalleBlanche.intersects(mur[i].GetRect()))
		{
			if (mur[i].GetLargeur()<mur[i].GetHauteur())
			{
				nouveauMouvement.x = mouvement.x*-1;
				nouveauMouvement.y = mouvement.y;
				vitesseX *= -1;
				while (rectangleBalleBlanche.intersects(mur[i].GetRect()))
				{
					x += nouveauMouvement.x;
					rectangleBalleBlanche = IntRect(x, y, largeur, hauteur);
				}

			}
			else
			{
				nouveauMouvement.x = mouvement.x;
				nouveauMouvement.y = mouvement.y*-1;
				vitesseY *= -1;
				while (rectangleBalleBlanche.intersects(mur[i].GetRect()))
				{
					y += nouveauMouvement.y;
					rectangleBalleBlanche = IntRect(x, y, largeur, hauteur);
				}
			}
			SetMouvement(nouveauMouvement);
			return 	rectangleBalleBlanche.intersects(mur[i].GetRect());
		}
		
	}
	return 	rectangleBalleBlanche.intersects(mur[0].GetRect());
}
bool BalleBlanche::CollisionAvecPoche(Poche poche [], Balle autresBalles[])
{
	for (int i = 0; i < NB_POCHES; i++)
	{
		if (rectangleBalleBlanche.intersects(poche[i].GetRectangle()))
		{
			arret = true;
			x = startX;
			y = startY;
			for (int i = 0; i < NB_BALLES; i++)
			{
				if (rectangleBalleBlanche.intersects(autresBalles[i].GetRectangle()))
				{
					bool respawn = false;
					while (!respawn)
					{
						respawn = true;
						x += largeur + 1;
						rectangleBalleBlanche.left = x;
						for (int j = 0; j < NB_BALLES; j++)
						{
							if (rectangleBalleBlanche.intersects(autresBalles[j].GetRectangle()))
							{
								respawn = false;
								break;
							}
						}
					}
					break;
				}
			}
			mouvement.x = 0;
			mouvement.y = 0;
			vitesseX = 0;
			vitesseY = 0;
			return true;
		}
	}
	return false;
}
bool BalleBlanche::CollisionAvecBalle(Balle autreBalle[])
{
	float dX = 0;
	float dY = 0;
	float distance = 0;
	for (int i = 0; i < NB_BALLES; i++)
	{
		dX = x - autreBalle[i].GetX();
		dY = y - autreBalle[i].GetY();
		distance = sqrt(dX * dX + dY * dY);
		if (distance <= largeur)
		{
			arret = false;
			ResoudreCollision(autreBalle[i]);
			AjusterChevauchement(autreBalle[i]);
			return true;
		}
	}
	return false;
}

void BalleBlanche::Deplacer()
{
	mouvement = GetNewMouvement();
	arret = false;
	x += GetNewMouvement().x;
	y += GetNewMouvement().y;
	TesterArret();
	rectangleBalleBlanche = IntRect(x, y, largeur, hauteur);
}

void BalleBlanche::SetMouvement(Vector2f _mouvement)
{
	_mouvement.x = cos(angle) * vitesseX;
	_mouvement.y = sin(angle) * vitesseY;
	mouvement = _mouvement;
}

Vector2f BalleBlanche::GetNewMouvement()
{
	mouvement.x *= FRICTION;
	mouvement.y *= FRICTION;
	vitesseX *= FRICTION;
	vitesseY *= FRICTION;
	return mouvement;
}

Vector2f BalleBlanche::GetMouvement() const
{
	return mouvement;
}

void BalleBlanche::TesterArret()
{
	//Calcul de la vitesse actuelle actuelle (pythagore)
	float vitesseTotale = sqrt(mouvement.x * mouvement.x + mouvement.y * mouvement.y);

	//Si plus petite qu'un certain point, on arrête la balle
	if (!arret &&vitesseTotale < 0.6f)
	{
		arret = true;
		mouvement.x = 0.0f;
		mouvement.y = 0.0f;
		//vitesseX = 1;
		//vitesseY = 1;
	}
	/*if (abs(mouvement.x) < 0.6f)
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
	}*/
}
/// <summary>
/// Retourne l'arret
/// </summary>
/// <returns>Vrai si la balle est arretée, faux sinon</returns>
bool BalleBlanche::GetArret()
{
	return arret;
}
/// <summary>
/// Retourne l'angle de la balle
/// </summary>
/// <returns>Retourne l'angle</returns>
float BalleBlanche::GetAngle() const
{
	return angle;
}
/// <summary>
/// Ajuster l'angle de la balle.
/// </summary>
/// <param name="_angle">Le nouvel angle</param>
void BalleBlanche::SetAngle(float _angle)
{
	angle = _angle;
}
/// <summary>
/// Fait l'ensemble des traitements lorsque la balle est en collision avec une autre balle
/// </summary>
/// <param name="autreBalle">L'autre balle.</param>
void BalleBlanche::ResoudreCollision(Balle &autreBalle)
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

	Vector2f nouveauMouvementBlanche = Vector2f(vitesseNormale1.x + vitesseTangente1.x, vitesseNormale1.y + vitesseTangente1.y);
	/*if (mouvement.x < 0)
		angle -= normale.x;
	else
		angle += normale.x;*/
	SetMouvement(nouveauMouvementBlanche);
	//x += mouvement.x;
	//y += mouvement.y;
	rectangleBalleBlanche = IntRect(x, y, largeur, hauteur);
	Vector2f nouveauMouvementBalle = Vector2f(vitesseNormale2.x + vitesseTangente2.x, vitesseNormale2.y + vitesseTangente2.y);
	autreBalle.SetMouvement(nouveauMouvementBalle);
	//autreBalle.SetX(autreBalle.GetX() + (nouveauMouvementBalle.x));
	//autreBalle.SetY(autreBalle.GetY() + (nouveauMouvementBalle.y));
}
/// <summary>
/// Calculer le vecteur unitaire pour résoudre les collisions entre balles
/// </summary>
/// <param name="normale">La normale </param>
/// <returns>Le vecteur unitaire </returns>
Vector2f BalleBlanche::CalculerVecteurUnitaire(Vector2f normale)
{
	float pente = sqrt(normale.x * normale.x + normale.y * normale.y);

	//Si 0, ça provique une division par 0.
	if (pente != 0.0f)
	{
		return Vector2f(normale.x / pente, normale.y / pente);
	}

	return Vector2f(0.0f, 0.0f);
}
/// <summary>
/// Ajuster le chevauchement possible entre les balles.
/// </summary>
/// <param name="autreBalle">L'autre balle en collision</param>
void BalleBlanche::AjusterChevauchement(Balle& autreBalle)
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

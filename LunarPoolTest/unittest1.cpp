#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LunarPool/Balle.h"
#include "../LunarPool/Mur.h"
#include "../LunarPool/Poche.h"
#include "../LunarPool/Constantes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LunarPoolTest
{
	TEST_CLASS(UnitTest1)
	{
	public:
		////////////  COLLISION BALLE ET MUR  /////////////
		// Cas où on a clairement pas de collision
		TEST_METHOD(CollisionBalleMur_PasDeCollision)
		{
			Balle balle(80, 80, 1, DIAMETRE);
			Mur mur[1] {Mur(0, 0, 60, 5)};
			Assert::IsFalse(balle.CollisionAvecMur(mur,1));
		}
		// Cas où une balle est tout près d'une collision avec un mur
		TEST_METHOD(CollisionBalleMur_PasDeCollisionLimite)
		{
			Balle balle(80, 81, 1, DIAMETRE);
			Mur mur[1] {Mur(0, 0, 100, 80)};
			Assert::IsFalse(balle.CollisionAvecMur(mur, 1));
		}
		// Cas où une balle est en collision à la limite du mur
		TEST_METHOD(CollisionBalleMur_CollisionLimite)
		{
			Balle balle(80, 79, 1, DIAMETRE);
			Mur mur[1] {Mur(0, 0, 100, 80)};
			Assert::IsTrue(balle.CollisionAvecMur(mur, 1));
		}
		// Cas où une balle est en collision franche avec un mur
		TEST_METHOD(CollisionBalleMur_CollisionFranche)
		{
			Balle balle(80, 77, 1, DIAMETRE);
			Mur mur[1] {Mur(0, 0, 100, 80)};
			Assert::IsTrue(balle.CollisionAvecMur(mur, 1));
		}

		//////// COLLISION BALLE ET BALLE ////////////
		// Cas où on a clairement pas de collision
		TEST_METHOD(CollisionBalleBalle_PasDeCollision)
		{
			Balle balle(80, 80, 1, DIAMETRE);
			Balle balle2(200, 200, 2, DIAMETRE);
			Assert::IsFalse(balle.CollisionAvecBalle(balle2));
		}
		// Cas où une balle est tout près d'une collision avec une autre balle
		TEST_METHOD(CollisionBalleBalle_PasDeCollisionLimite)
		{
			Balle balle(80, 80, 1, DIAMETRE);
			Balle balle2(80 + 40 + 1, 80, 2, DIAMETRE);
			Assert::IsFalse(balle.CollisionAvecBalle(balle2));
		}
		// Cas où une balle est en collision limite avec une autre balle
		TEST_METHOD(CollisionBalleBalle_CollisionLimite)
		{
			Balle balle(80, 80, 1, DIAMETRE);
			Balle balle2(80 + 40, 80, 2, DIAMETRE);
			Assert::IsTrue(balle.CollisionAvecBalle(balle2));
		}
		// Cas où une balle est en collision franche avec une autre balle
		TEST_METHOD(CollisionBalleBalle_CollisionFranche)
		{
			Balle balle(80, 80, 1, DIAMETRE);
			Balle balle2(80 + 40, 80, 2, DIAMETRE);
			Assert::IsTrue(balle.CollisionAvecBalle(balle2));
		}

		//////// COLLISION BALLE ET POCHE //////////
		// Cas où on a clairement pas de collision
		TEST_METHOD(CollisionBallePoche_PasDeCollision)
		{
			Balle balle(0, 0, 1, DIAMETRE);
			Poche poche[1]{Poche(100, 100,50)};
			Assert::IsFalse(balle.CollisionAvecPoche(poche,1));
		}
		// Cas où une balle est tout près d'une collision avec une poche
		TEST_METHOD(CollisionBallePoche_PasDeCollisionLimite)
		{
			Poche poche[1]{Poche(0, 0,50)};
			Balle balle(poche[0].GetLargeur() + 1, 0, 1, DIAMETRE);
			Assert::IsFalse(balle.CollisionAvecPoche(poche,1));
		}
		// Cas où une balle est en collision limite avec une poche
		TEST_METHOD(CollisionBallePoche_CollisionLimite)
		{
			Poche poche[1]{Poche(0, 0,50)};
			Balle balle(poche[0].GetLargeur()-1, 0, 1, DIAMETRE);
			Assert::IsTrue(balle.CollisionAvecPoche(poche,1));
		}
		// Cas où une balle est en collision franche avec une poche
		TEST_METHOD(CollisionBallePoche_CollisionFranche)
		{
			Poche poche[1]{Poche(0, 0,50)};
			Balle balle(poche[0].GetLargeur() - 3, 0, 1, DIAMETRE);
			Assert::IsTrue(balle.CollisionAvecPoche(poche,1));
		}
		///////  COLLISION BLANCHE ET MUR ///////////
		// Cas où on a clairement pas de collision
		TEST_METHOD(CollisionBlancheMur_PasDeCollision)
		{
			Mur mur[1] {Mur(0, 0, 40, 5)};
			Balle balle(20, 100, 1,40);
			Assert::IsFalse(balle.CollisionAvecMur(mur, 1));
		}
		// Cas où on est tout près d'une collision entre la blanche et un mur
		TEST_METHOD(CollisionBlancheMur_PasDeCollisionLimite)
		{
			Mur mur[1] {Mur(0, 0, 40, 5)};
			Balle balle(20, 41, 1,40);
			Assert::IsFalse(balle.CollisionAvecMur(mur, 1));
		}
		// Cas où on a une collision limite entre la blanche et un mur
		TEST_METHOD(CollisionBlancheMur_CollisionLimite)
		{
			Mur mur[1] {Mur(0, 0, 40, 5)};
			Balle balle(0, 4, 1,40);
			Assert::IsTrue(balle.CollisionAvecMur(mur, 1));
		}
		// Cas où on a une collision franche entre la blanche et un mur
		TEST_METHOD(CollisionBlancheMur_CollisionFranche)
		{
			Mur mur[1] {Mur(0, 0, 40, 5)};
			Balle balle(10, 2, 1,40);
			Assert::IsTrue(balle.CollisionAvecMur(mur, 1));
		}
		///////// COLLISION BLANCHE ET BALLE ////////////
		TEST_METHOD(CollisionBlancheBalle_PasDeCollision)
		{
			Mur mur[1] {Mur(0, 0, 40, 5)};
			Balle balle(10, 2, 1,40);
			Assert::IsTrue(balle.CollisionAvecMur(mur, 1));
		}
	};
}
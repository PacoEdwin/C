#pragma once
//#include "BombLoaded.h"
//#include "BombReload.h"
//#include "NoBonb.h"
#include "Weapon.h"
#include <vector>
#include<iostream>
#include <memory>
using namespace std;
#define AILA_H

class BombLoaded;
class BombReload;
class NoBomb;

class AILa :
	public std::enable_shared_from_this<AILa>
{
	shared_ptr<Weapon> bombLoaded;
	shared_ptr<Weapon> bombReload;
	shared_ptr<Weapon> noBomb;

	shared_ptr<Weapon> currentBombState;
	int bombs;
public:
	void fireWeapon()
	{
		currentBombState->fire();
	}
	void setCurrentBombState(shared_ptr<Weapon> newBombState)
	{
		currentBombState = newBombState;
	}
	void setBombs(const int& newBombs)
	{
		bombs = newBombs;
	}
	int getBombs()
	{
		return bombs;
	}
	void initialize();
	shared_ptr<Weapon> getBombLoaded() { return bombLoaded; }
	shared_ptr<Weapon> getBombReload() { return bombReload; }
	shared_ptr<Weapon> getNoBomb() { return noBomb; }
};

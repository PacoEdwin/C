#pragma once
#define BOMBLOADED_H
#include "Weapon.h"
#include "AILa.h"
#include<iostream>
#include <vector>
using namespace std;

class BombLoaded : public Weapon
{
	weak_ptr<AILa> plane_;
public:
	BombLoaded(shared_ptr<AILa> newPlane)
	{
		plane_ = newPlane;
	}

	virtual void fire()
	{
		cout << "Bomb dropped." << endl;
		if (auto Plane = plane_.lock())
		{
			Plane->setBombs(Plane->getBombs() - 1);
			if (Plane->getBombs() <= 0)
				Plane->setCurrentBombState(Plane->getNoBomb());
			else
			{
				auto reload = Plane->getBombReload();
				reload->fire();
				Plane->setCurrentBombState(reload);
			}
		}
		else
			cout << "Plane destroyed." << endl;
	}
};
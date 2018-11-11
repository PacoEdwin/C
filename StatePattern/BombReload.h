#pragma once
#define RELOADWEAPON_H
#include "Weapon.h"
#include <thread>
#include "AILa.h"
#include<iostream>
#include <vector>
using namespace std;
extern void Timer(BombReload &);
class BombReload : public Weapon
{
	weak_ptr<AILa> plane_;
	bool reload = false;
public:

	BombReload(shared_ptr<AILa> newPlane)
	{
		plane_ = newPlane;
	}

	virtual void fire()
	{
		if (!reload)
		{
			reload = true;
			thread t(Timer, std::ref(*this));
			t.detach();
		}
		cout << "Reloading..."<<endl;
	}
	void finished_reload()
	{
		if (auto Plane = plane_.lock())
		{
			Plane->setCurrentBombState(Plane->getBombLoaded());
			reload = false;
		}
		else
			cout << "Plane destroyed." << endl;
	}
};

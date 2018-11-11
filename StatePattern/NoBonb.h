#pragma once
#define NOBOMB_H
#include "Weapon.h"
#include "AILa.h"
#include<iostream>
#include <vector>
using namespace std;

class NoBomb : public Weapon
{
	weak_ptr<AILa>  plane_;
public:
	NoBomb(shared_ptr<AILa> newPlane)
	{
		plane_ = newPlane;
	}

	virtual void fire()
	{
		cout << "No Ammo." << endl;
	}
};
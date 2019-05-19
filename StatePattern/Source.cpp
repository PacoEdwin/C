#include<iostream>
#include<vector>
#include<string>
#include<thread>
#include "NoBonb.h"
#include "BombLoaded.h"
#include "BombReload.h"
#include "AILa.h"
#include<memory>
using namespace std;

int main()
{
	auto p = make_shared<AILa>();
	p->initialize();
	p->setBombs(0);
	p->fireWeapon();
	for (int i = 0; i < 12; i++)
	{
		std::this_thread::sleep_for(1s);
		p->fireWeapon();
	}
	system("pause");
	return 0;
}


#include "BombReload.h"
#include <iostream>
#include <thread>
void Timer(BombReload &bombReload)
{
	std::this_thread::sleep_for(3s);
	bombReload.finished_reload();
}
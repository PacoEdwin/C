#include "AILa.h"
#include "BombLoaded.h"
#include "BombReload.h"
#include "NoBonb.h"
void AILa::initialize()
{
	bombs = 0;
	auto p = shared_from_this();
	bombLoaded = make_shared<BombLoaded>(p);
	bombReload = make_shared<BombReload>(p);
	noBomb = make_shared<NoBomb>(p);
	currentBombState = bombLoaded;
	if (bombs <= 0)
		currentBombState = noBomb;
}
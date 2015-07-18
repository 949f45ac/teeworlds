#ifndef GAME_SERVER_GAMEMODES_EDM_H
#define GAME_SERVER_GAMEMODES_EDM_H
#include <game/server/gamecontroller.h>
#include "dm.h"

class CGameControllerEDM : public IGameController
{
public:
	CGameControllerEDM(class CGameContext *pGameServer);
	virtual void Tick();
	virtual bool OnEntity(int Index, vec2 Pos);
};
#endif

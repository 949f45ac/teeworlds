#include "edm.h"
#include <game/mapitems.h>

#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include <game/server/entities/pickup.h>

CGameControllerEDM::CGameControllerEDM(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "EDM";
}

void CGameControllerEDM::Tick()
{
	IGameController::Tick();
}

bool CGameControllerEDM::OnEntity(int Index, vec2 Pos)
{
	if(IGameController::OnEntity(Index, Pos))
		return true;
	
	if(Index == ENTITY_WEAPON_SHAFT)
	{
		CPickup *pPickup = new CPickup(&GameServer()->m_World, POWERUP_WEAPON, WEAPON_SHAFT);
		pPickup->m_Pos = Pos;
		return true;
	}
	
	return false;
}

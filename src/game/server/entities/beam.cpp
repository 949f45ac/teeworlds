
#include <game/generated/protocol.h>
#include <game/server/gamecontext.h>
#include "beam.h"

CBeam::CBeam(CGameWorld *pGameWorld, vec2 Pos, vec2 Direction, int Owner)
: CEntity(pGameWorld, CGameWorld::ENTTYPE_BEAM)
{
	m_Pos = Pos;
	m_Owner = Owner;
	m_Dir = Direction;
	m_EvalTick = Server()->Tick();
	m_Cooled = true;
	GameWorld()->InsertEntity(this);
}


bool CBeam::HitCharacter(vec2 From, vec2 To)
{
	vec2 At;
	CCharacter *pOwnerChar = GameServer()->GetPlayerChar(m_Owner);
	CCharacter *pHit = GameServer()->m_World.IntersectCharacter(m_From, To, 5.0f, At, pOwnerChar);
	if(!pHit)
		return false;

	m_From = From;
	m_Pos = At;
	pHit->TakeDamage(vec2(0.f, 0.f), GameServer()->Tuning()->m_ShaftDamage, m_Owner, WEAPON_SHAFT);
	return true;
}

void CBeam::AdjustPosition(vec2 NewFrom, vec2 NewDir, bool Cooled)
{
	m_Cooled = m_Cooled || Cooled;

	m_From = NewFrom;
	m_Pos = (m_From + NewDir * GameServer()->Tuning()->m_ShaftReach);
	GameServer()->Collision()->IntersectLine(m_From, m_Pos, &m_Pos, 0x0);
	GameServer()->m_World.IntersectCharacter(m_From, m_Pos, 5.0f, m_Pos, GameServer()->GetPlayerChar(m_Owner));
}

void CBeam::Reset()
{
	GameServer()->m_World.DestroyEntity(this);
}

void CBeam::Tick()
{
	GameServer()->CreateSound(m_From, SOUND_SHAFT_FIRE);
	GameServer()->CreateSound(m_Pos, SOUND_SHAFT_FIRE);
	// only lose cooled status if we hit anything
	// effect = always cause at least 1 damage when glancing a character
	m_Cooled = m_Cooled && !HitCharacter(m_From, m_Pos);
}

void CBeam::TickPaused()
{
	++m_EvalTick;
}

void CBeam::Snap(int SnappingClient)
{
	if(NetworkClipped(SnappingClient))
		return;

	CNetObj_Beam *pObj = static_cast<CNetObj_Beam *>(Server()->SnapNewItem(NETOBJTYPE_BEAM, m_ID, sizeof(CNetObj_Beam)));
	if(!pObj)
		return;

	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_FromX = (int)m_From.x;
	pObj->m_FromY = (int)m_From.y;
	pObj->m_Owner = m_Owner;
	pObj->m_StartTick = m_EvalTick;
}

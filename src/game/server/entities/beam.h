

#ifndef GAME_SERVER_ENTITY_SPARKLE_H
#define GAME_SERVER_ENTITY_SPARKLE_H

#include <game/server/entity.h>

class CBeam : public CEntity
{
public:
	CBeam(CGameWorld *pGameWorld, vec2 Pos, vec2 Direction, int Owner);

	virtual void Reset();
	virtual void Tick();
	virtual void TickPaused();
	virtual void Snap(int SnappingClient);
	virtual void AdjustPosition(vec2 NewFrom, vec2 NewDir, bool Cooled);

protected:
	bool HitCharacter(vec2 From, vec2 To);

private:
	vec2 m_From;
	vec2 m_Dir;
	bool m_Cooled;
	int m_EvalTick;
	int m_Owner;
	
	inline void Intersect();
};

#endif

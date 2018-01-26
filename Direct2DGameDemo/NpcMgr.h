#pragma once
#include "NPC.h"

class NpcMgr
{
protected:
	typedef list<NPC*> NpcList;
	NpcList m_lNpc;
public:
	NpcMgr() {}
	~NpcMgr() {}
	virtual bool AddNpc(NPC *npc);
	virtual void Render();
	virtual bool CollisionDetec(RECT rect);
	virtual void RenderLine();
	void CleanUp();
};
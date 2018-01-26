#include "NpcMgr.h"

bool NpcMgr::AddNpc(NPC * npc)
{
	if (!npc)
		return false;
	m_lNpc.push_back(npc);
	return true;
}

void NpcMgr::Render()
{
	if (m_lNpc.empty())
		return;
	static list<NPC*>::iterator ite;
	for (ite=m_lNpc.begin(); ite!=m_lNpc.end(); ite++)
	{
		(*ite)->Render();
	}
}
//Åö×²¼ì²â
bool NpcMgr::CollisionDetec(RECT rect)
{
	if (m_lNpc.empty())
		return false;
	static list<NPC*>::iterator ite;
	static RECT rect1;
	for (ite = m_lNpc.begin(); ite != m_lNpc.end(); ite++)
	{
		if (IntersectRect(&rect1, &rect, &(*ite)->GetRange()))
		{
			(*ite)->SetCollision(true);
			return true;
		}
		else (*ite)->SetCollision(false);
	}
	return false;
}

//»æÖÆÅö×²¾ØÐÎ
void NpcMgr::RenderLine()
{
	if (m_lNpc.empty())
		return;
	static list<NPC*>::iterator ite;
	for (ite = m_lNpc.begin(); ite != m_lNpc.end(); ite++)
	{
		(*ite)->RenderLine();
	}
}

void NpcMgr::CleanUp()
{
	static list<NPC*>::iterator ite,cur;
	for (ite = m_lNpc.begin(); ite != m_lNpc.end(); )
	{
		cur = ite++;
		(*cur)->CleanUp();
		m_lNpc.erase(cur);
	}
}

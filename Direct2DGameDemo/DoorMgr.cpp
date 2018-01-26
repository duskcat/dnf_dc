#include "DoorMgr.h"
#include "Town.h"

bool DoorMgr::AddDoor(Door * door)
{
	m_lDoors.push_back(door);
	return true;
}

void DoorMgr::Render()
{
	if (m_lDoors.empty())
		return;
	static list<Door*>::iterator ite;
		for (ite = m_lDoors.begin(); ite != m_lDoors.end();ite++)
		{
			if (monsterInst->MonsterCount() == 0)
				(*ite)->DoorState(true);
			(*ite)->Render();
		}
}

bool DoorMgr::CollisionDetec(RECT rect)
{
	if (m_lDoors.empty())
		return false;
	static list<Door*>::iterator ite;
	static RECT m_rect;
	for (ite = m_lDoors.begin(); ite != m_lDoors.end(); ite++)
	{
		if (IntersectRect(&m_rect, &rect, &(*ite)->GetRange()))
		{
			if (!(*ite)->IsOpen())
				return false;
			(*ite)->SetCollision(true);
			DoorInfo di = (*ite)->GetDoorInfo();
			townInst->CleanUp();
			townInst->Init(di.xml);
			roleInst->Position(di.rolePosX, di.rolePosY);
			mapPosX = di.mapx;
			return true;
		}
		else (*ite)->SetCollision(false);
	}

	return false;
}

void DoorMgr::CleanUp()
{
	static list<Door*>::iterator ite, cur;
	for (ite = m_lDoors.begin(); ite != m_lDoors.end(); )
	{
		cur = ite++;
		(*cur)->CleanUp();
		m_lDoors.erase(cur);
	}
}

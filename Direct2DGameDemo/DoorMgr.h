#pragma once

#include "Door.h"

class DoorMgr
{
protected:
	typedef list<Door *> DoorList;
	DoorList m_lDoors;
public:
	DoorMgr() {}
	~DoorMgr() { CleanUp(); }
	virtual bool AddDoor(Door *door);
	virtual void Render();
	virtual bool CollisionDetec(RECT rect);
	virtual void CleanUp();
private:

};

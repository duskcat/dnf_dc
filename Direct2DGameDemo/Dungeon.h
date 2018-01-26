#pragma once
#include "GUIControls.h"
class Dungeon
{
protected:

public:
	Dungeon(LPCWSTR path);
	~Dungeon() { CleanUp(); }
	virtual bool Init();
	virtual void Render();
	virtual void CleanUp();
};


#pragma once

#include "Monster.h"

class MonsterMgr
{
protected:
	typedef map<string, Monster*> MonsterType;
	typedef list<Monster*> MonsterList;
	MonsterList m_LMonsters;
	int m_Dir;
	int m_nMonsterCount;
public:
	MonsterMgr() {}
	static MonsterMgr* Instance() { static MonsterMgr mm; return &mm; }
	~MonsterMgr() { CleanUp(); }
	void AddMonster(Monster *monster,int count);
	void AddMonster(int count);
	bool Render();
	int MonsterCount(){return m_nMonsterCount;}
	bool CollisionDetec(RECT rect);
	void Update();
	void CleanUp();
};
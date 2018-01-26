#include "MonsterMgr.h"
#include "Role.h"
#include "SkillMgr.h"

void MonsterMgr::AddMonster(Monster *monster,int count)
{
	for (int i = 0; i < count; i++)
	{
		m_LMonsters.push_back(monster);
	}
		
}


//自定义list排序规则
bool CompareRults(Monster *monOne, Monster *monTwo)
{
	if (monOne->OffSetY() < monTwo->OffSetY())
		return true;
	return false;
}

void MonsterMgr::AddMonster(int count)
{
	m_nMonsterCount = count;
	srand(GetTickCount());
	for (int i = 0; i < count; i++)
	{
		Monster *monster = new Monster();
		monster->Init(rand() % 1792, rand() % 180 + MIN_POS_Y, L"image//monster//怪物头像-ACT1哥布林.png");
		m_LMonsters.push_back(monster);
	}
}

bool MonsterMgr::Render()
{
	if (m_LMonsters.empty())
	{
		m_nMonsterCount=0; return false;
	}
	m_LMonsters.sort(CompareRults);
	static list<Monster*>::iterator ite, cur;
	for (ite = m_LMonsters.begin(); ite != m_LMonsters.end();)
	{
		cur = ite++;
		(*cur)->Update();
		(*cur)->Render();
		if ((*cur)->IsDead())
		{
			m_LMonsters.erase(cur);
			m_nMonsterCount--;
		}
	}
	return false;
}

bool MonsterMgr::CollisionDetec(RECT rect)
{
	if (m_LMonsters.empty())
		return false;
	static list<Monster*>::iterator ite,cur;
	static RECT rect1;
	static Monster* pMonster;
	for (ite = m_LMonsters.begin(); ite != m_LMonsters.end();ite++)
	{
		(*ite)->SetCollision(IntersectRect(&rect1, &rect, &(*ite)->GetRange()));
		if ((*ite)->GetCollision())
		{
			pMonster = (*ite);
		}
		if (!skillMgrInst->IsEmpty())
		{
			static list<Skill*>::iterator skillIte;
			static list<Skill*> mlskill = skillMgrInst->Skills();
			for (skillIte = mlskill.begin(); skillIte != mlskill.end(); skillIte++)
			{
				(*ite)->SetCollision(IntersectRect(&rect1, &(*skillIte)->Region(), &(*ite)->GetRange()));
				if ((*ite)->GetCollision())
				{
					pMonster = (*ite);
				}
			}
		}
	}
	if(pMonster)
		pMonster->RenderStateBar();
	return false;
}

void MonsterMgr::Update()
{
	if (m_LMonsters.empty())
		return;
	static list<Monster*>::iterator ite, cur;
	for (ite = m_LMonsters.begin(); ite != m_LMonsters.end(); ite++)
	{

	}
	
}

void MonsterMgr::CleanUp()
{
	if (m_LMonsters.empty())
		return;
	m_LMonsters.clear();
}

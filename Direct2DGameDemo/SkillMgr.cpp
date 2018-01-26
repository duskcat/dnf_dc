#include "SkillMgr.h"


void SkillMgr::CreateSkill(string name, Skill * skill)
{
	m_mgrSkill[name] = skill;
}

void SkillMgr::AddSkill(Skill * skill)
{
	m_lSkills.push_back(skill);
}

void SkillMgr::RenderSkill()
{
	if (m_lSkills.empty())
		return;
	list<Skill*>::iterator ite, cur;	
		for (ite = m_lSkills.begin(); ite != m_lSkills.end();)
		{
			cur = ite++;
			(*cur)->Update();
			(*cur)->Render();
			if ((*cur)->IsPlayed())
				m_lSkills.erase(cur);
		}
}

void SkillMgr::Update(int dir)
{
	m_Dir = dir;
}

void SkillMgr::CleanUp()
{

}

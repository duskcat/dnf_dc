#pragma once
#include "stdafx.h"
#include "Skill.h"

#define skillMgrInst SkillMgr::Instance()

class SkillMgr
{
protected:
	typedef map<string, Skill*> SkillType;
	SkillType m_mgrSkill;
	typedef list<Skill*> SkillList;
	SkillList m_lSkills;
	int m_Dir;
public:
	SkillMgr(){}
	~SkillMgr() { CleanUp(); }
	virtual void CreateSkill(string name,Skill *skill);
	virtual void AddSkill(Skill * skill);
	virtual Skill* GetSkill(string name) { if (!m_mgrSkill[name])return NULL; return m_mgrSkill[name]; }
	virtual void RenderSkill();
	virtual void Update(int dir);
	virtual void CleanUp();
	bool IsEmpty() { return m_lSkills.empty(); }
	SkillList Skills() { if (!m_lSkills.empty()) return m_lSkills; }
	static SkillMgr* Instance() { static SkillMgr sm; return &sm; }
private:
};

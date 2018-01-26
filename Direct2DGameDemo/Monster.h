#pragma once
#include "stdafx.h"
#include "StateMachine.h"
#include "Role.h"
#include "Animation.h"
#include "AnimationMgr.h"

#define MONSTER_STATE_ATTACK	1
#define MONSTER_STATE_WALK		2
#define MONSTER_STATE_STAND		3
#define MONSTER_STATE_RUN		4

class Monster
{
protected:
	int HP;
	int MaxHp;
	int MP;
	bool m_bIsCollision=false;
	LPDIRECT3DTEXTURE9 m_pTexHead;		//Í·ÏñÎÆÀí
	float m_fPosX, m_fPosY;
	float m_fSkillOffX, m_fSkillOffY;
	int m_nWidth, m_nHight;
	ImageInfo imgInfo;
	bool m_bIsDead=false;
	bool m_bSkill = false;
	Direction mDir=Dir_Left;
	int curDir=0;
	float m_fDamage = 10;
	int monsterState = MONSTER_STATE_WALK;
	float curTime, lastTime = 0;
	Animation *MonsterAni;
	RECT monsterRange;
	RECT m_rWarningRegion;
	RECT m_rAttackRegion;
	RECT m_rMonsterSkillRegion;
	StateMachine<Monster>* m_pStateMachine;
public:
	Monster();
	~Monster() { CleanUp(); }
	virtual void Init(int x, int y, LPCWSTR texHead);
	virtual void Render();
	void RenderStateBar();
	void Walk();
	void Attack();
	void Runaway();
	void Trace();
	void GetHurt(int damage) { HP -= damage;}
	RECT WarningRegion() { return m_rWarningRegion;}
	RECT AttackRegion() { return m_rAttackRegion; }
	void Dead();
	void SetCurAni(string name);
	void SetCollision(bool b) { m_bIsCollision = b; }
	bool GetCollision() { return m_bIsCollision; }
	virtual float OffSetX() { return m_fPosX-mapPosX; }
	virtual float OffSetY() { return m_fPosY; }
	void SkillOffSetPos();
	float Width() { return m_nWidth; }
	float Hight() { return m_nHight; }
	int GetHp() { return HP; }
	RECT GetRange() { return monsterRange; }
	RECT SkillRegion() { return m_rMonsterSkillRegion; }
	virtual bool IsDead() { return m_bIsDead; }
	virtual void Update();
	virtual void CleanUp();
	float Damage() { return m_fDamage=10;}
	StateMachine<Monster>* GetFSM() { return m_pStateMachine; }
};

class State_Walk :public State<Monster>
{
public:
	void Execute(Monster *monster);
	void Exit(Monster * monster);
	void Enter(Monster *monster);
	static State_Walk* Instance() { static State_Walk sw; return &sw;}
};

class State_Attack :public State<Monster>
{
public:
	void Execute(Monster *monster);
	void Exit(Monster * monster){}
	void Enter(Monster *monster);
	static State_Attack* Instance() { static State_Attack sa; return &sa; }
};

class State_Runaway :public State<Monster>
{
public:
	void Execute(Monster *monster);
	void Exit(Monster * monster) {}
	void Enter(Monster *monster) {}
	static State_Runaway* Instance() { static State_Runaway sw; return &sw; }
};
//dead
class State_Dead :public State<Monster>
{
public:
	void Execute(Monster *monster);
	void Exit(Monster * monster) {}
	void Enter(Monster *monster){}
	static State_Dead* Instance() { static State_Dead sd; return &sd; }

};

class State_GetHurt :public State<Monster>
{
public:
	void Execute(Monster *monster);
	void Exit(Monster * monster) {}
	void Enter(Monster *monster);
	static State_GetHurt* Instance() { static State_GetHurt sh; return &sh; }
};

class State_Trace :public State<Monster>
{
public:
	void Execute(Monster *monster);
	void Exit(Monster * monster) {}
	void Enter(Monster *monster);
	static State_Trace* Instance() { static State_Trace st; return &st; }
};
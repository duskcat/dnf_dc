#pragma once

//渲染底部状态栏（HP，MP，SKILL）等

#include "Animation.h"
#include "GUIControls.h"
#include "stdafx.h"

//角色状态宏定义
#define ROLE_STATE_STAND  1
#define ROLE_STATE_WALK   2
#define ROLE_STATE_RUN	  3
#define ROLE_STATE_ATTACK 4
#define ROLE_STATE_SKILL  5
#define ROLE_STATE_HURT	  6
#define ROLE_SPEED 0.4f

//角色种族宏（剑士，枪手）
#define ROLE_TYPE_SWORDMAN 1
#define ROLE_TYPE_MARKSMAN 2

//碰撞类型
#define COLLISION_TYPE_MONSTER	1
#define COLLISION_TYPE_NPC		2

//角色single
#define roleInst Role::Instance()

class Role
{
protected:
	Animation *m_pAniCurTex;						//角色当前动作纹理
	LPDIRECT3DTEXTURE9 m_pBottomBar = NULL;			//底部状态栏
	RECT m_RoleRange;								//角色范围（用于碰撞检测）
	int m_nWidthBar, m_nHightBar;					
	int CurRoleState;								//当前角色状态
	int Hp, Mp;
	float m_fPosX, m_fPosY;							//角色位置
	float m_fDamage=40;
	float m_fHurtDamage = 0;
	int m_nWidth, m_nHight;
	bool m_bIsInited;
	bool m_bIsAtTown;
	bool m_bIsRender;
	bool m_bIsPlayed = false;
	bool m_bIsMoved = true;
	bool m_bIsAttack=false;
	D3DXMATRIX m_pMax;
	int mCollisionType=1;
	bool m_bIsHurt=false;
	float curTime, lastTime;
	D3DXVECTOR2 *m_pLineArr=NULL;
	bool m_bIsCollision = false;
	int m_nLevel=1;
	bool m_nExp=0;
	Animation *m_pTitlel;
	LPDIRECT3DTEXTURE9 m_pName;
	LPDIRECT3DTEXTURE9 m_pInfo;
	bool m_bInfo;
	Animation *m_pAniEquip;
	GUIClass *m_pGuiOption;
public:
	Direction m_dDir = Dir_Right;					//角色面向
	Role();
	~Role();
	static Role* Instance();
	virtual bool Init();
	virtual void Render();
	virtual void SetLineArr();
	virtual void RenderLine();
	virtual void CleanUp();
	virtual bool CreateRole(float x,float y);
	virtual void Update();
	float GetPosX() { return m_fPosX; }
	float GetPosY() { return m_fPosY; }
	bool IsAttack() { return m_bIsAttack; }
	void SetMoved(bool isMoved) { m_bIsMoved = isMoved; }
	int GetHp() { return Hp; }
	int GetMp() { return Mp; }
	RECT GetRoleRange() { return m_RoleRange; }
	virtual void SetCollision(bool b) { m_bIsCollision = b; }
	virtual bool GetCollision() { return m_bIsCollision; }
	void SetCollisionType(int type) { mCollisionType = type; }
	float Damage() { return m_fDamage; }
	void IsHurt(bool b) { m_bIsHurt = b; }
	void Hurt(float dmg);
	void Position(float x, float y) { m_fPosX = x; m_fPosY = y; };
	void IsRender(bool b) { m_bIsRender = b;}
private:

};

#pragma once

#include "stdafx.h"
#include "Animation.h"

class Skill
{
protected:
	LPDIRECT3DTEXTURE9 *m_pTexSkill=NULL;	//技能纹理
	Animation *m_pAni = NULL;				//技能动画
	D3DXMATRIX m_Max;						//用于技能的旋转缩放
	D3DXVECTOR2 m_dScaling;					//技能的缩放
	float m_fPosX, m_fPosY;					//技能位置，与角色位置关联
	float m_curMapX;
	ImageInfo imageInfo;
	float m_nWidth, m_nHight;
	float m_nOffsetX, m_nOffsetY;
	float m_fMoveX=0, m_fMoveY=0;
	float m_fDamage;						//技能伤害
	string m_sName;							//技能名称
	int curFrame = 0;						//技能当前帧
	int m_nSkillFrame = 0;					//技能帧数
	float curTime=0, lastTime=0;			//计算间隔时间
	RECT m_rRegion;
	bool m_bIsPlayed=false;
	Direction m_roleDir =Dir_Right;

public:
	Skill(LPCTSTR fileName,LPCTSTR fileType,int count,float x,float y, D3DXVECTOR2 scaling);

	Skill(LPCTSTR fileName, LPCTSTR fileType, int count, float x, float y, D3DXVECTOR2 scaling,Animation *ani);
	~Skill() { CleanUp(); }
	virtual void Render();
	virtual void Update();
	void Scaling(D3DXVECTOR2 scaling) { m_dScaling = scaling; }
	virtual void SetMax(D3DXMATRIX max) {m_Max = max; g_pSprite->SetTransform(&m_Max);}
	virtual void CleanUp();
	virtual bool IsPlayed() { return m_bIsPlayed; }
	RECT Region() { return m_rRegion; }
private:

};


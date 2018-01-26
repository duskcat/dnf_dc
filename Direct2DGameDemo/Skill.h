#pragma once

#include "stdafx.h"
#include "Animation.h"

class Skill
{
protected:
	LPDIRECT3DTEXTURE9 *m_pTexSkill=NULL;	//��������
	Animation *m_pAni = NULL;				//���ܶ���
	D3DXMATRIX m_Max;						//���ڼ��ܵ���ת����
	D3DXVECTOR2 m_dScaling;					//���ܵ�����
	float m_fPosX, m_fPosY;					//����λ�ã����ɫλ�ù���
	float m_curMapX;
	ImageInfo imageInfo;
	float m_nWidth, m_nHight;
	float m_nOffsetX, m_nOffsetY;
	float m_fMoveX=0, m_fMoveY=0;
	float m_fDamage;						//�����˺�
	string m_sName;							//��������
	int curFrame = 0;						//���ܵ�ǰ֡
	int m_nSkillFrame = 0;					//����֡��
	float curTime=0, lastTime=0;			//������ʱ��
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


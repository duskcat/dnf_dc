#include "Skill.h"
#include "Role.h"

Skill::Skill(LPCTSTR fileName, LPCTSTR fileType, int count, float x, float y, D3DXVECTOR2 scaling)
{

	m_pTexSkill=CreateTextures(fileName, fileType, count,imageInfo);
	m_fPosX = x;
	m_fPosY = y;
	m_fMoveX = 2.0f;
	m_fMoveY = 1.0f;
	m_nSkillFrame = count;
	m_roleDir = roleInst->m_dDir;
	m_Max = g_pMax;
	m_curMapX = mapPosX;
	m_dScaling = scaling;
}

Skill::Skill(LPCTSTR fileName, LPCTSTR fileType, int count, float x, float y, D3DXVECTOR2 scaling, Animation * ani)
{
	m_pTexSkill = CreateTextures(fileName, fileType, count, imageInfo);
	m_fPosX = x;
	m_fPosY = y;
	m_fMoveX = 2.0f;
	m_fMoveY = 1.0f;
	m_nSkillFrame = count;
	m_roleDir = roleInst->m_dDir;
	m_pAni = ani;
	m_Max = g_pMax;
	m_curMapX = mapPosX;
	m_dScaling = scaling;
}

void Skill::Render()
{
	if(m_pAni)
	{
		m_pAni->Update(0, m_fPosY, m_roleDir);
		m_pAni->Render();
		if (!m_pAni->IsPlayed())
			return;
	}
	if (!m_pTexSkill)
		return;
	if (curFrame == m_nSkillFrame)
	{
		CleanUp();
		curFrame = 0;
		m_bIsPlayed = true;
	}
	m_nWidth = imageInfo.m_imageInfo[curFrame].width;
	m_nHight= imageInfo.m_imageInfo[curFrame].hight;
	m_nOffsetX = m_fPosX - (mapPosX - m_curMapX);
	m_nOffsetY = m_fPosY - m_nHight;

	g_pSprite->SetTransform(&m_Max);
	SPRITE_DRAW(m_pTexSkill[curFrame], m_nOffsetX,m_nOffsetY);
	SetRect(&m_rRegion, m_nOffsetX, m_fPosY, m_nOffsetX + m_nWidth, m_fPosY + m_nHight);
	//g_pSprite->Draw(m_pTexSkill[curFrame], NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	curTime = GetTickCount();
	if (curTime - lastTime >= 60)
	{
		curFrame++;
		m_fPosX += m_fMoveX;
		lastTime = curTime;
	}
	g_pSprite->SetTransform(&g_pMax);
}

void Skill::Update()
{
	D3DXMatrixTransformation2D(&m_Max, &D3DXVECTOR2(m_fPosX - (mapPosX - m_curMapX), m_fPosY), 0, &D3DXVECTOR2(m_dScaling.x, m_dScaling.y), 0, 0,0);

	if (m_roleDir == Dir_Left)
	{
		D3DXMatrixTransformation2D(&m_Max, &D3DXVECTOR2(m_fPosX - (mapPosX - m_curMapX), m_fPosY), 0, &D3DXVECTOR2(-m_dScaling.x, m_dScaling.y), 0, 0, 0);
		//g_pSprite->SetTransform(&m_Max);
		m_fMoveX = -2.0f;
	}
}

void Skill::CleanUp()
{
	for (int i=0;i<m_nSkillFrame;i++)
	{
		Safe_Release(m_pTexSkill[i]);
	}
}

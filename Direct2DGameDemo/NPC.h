#pragma once

#include "stdafx.h"
#include "Animation.h"

class NPC
{
protected:
	LPDIRECT3DTEXTURE9 *m_pTex;
	LPDIRECT3DTEXTURE9 m_pTexDiaBox;
	LPCSTR m_sNpcName;
	RECT m_npcRange;
	float m_fPosX, m_fPosY;
	int m_nWidth, m_nHight;
	float curTime, lastTime;
	int m_nFrameCount,curFrame=0;
	int m_FrameSpeed=100;
	ImageInfo ii;
	D3DXVECTOR2 *m_pLineArr;
	bool m_bIsCollision=false;
public:
	NPC() {}
	NPC(LPCTSTR tex, LPCTSTR type, int count, float x, float y, LPCTSTR name);
	~NPC() { CleanUp(); }
	virtual void Init();
	virtual void Render();
	virtual void CleanUp();
	virtual void RenderLine();
	virtual RECT GetRange() { return m_npcRange; }
	virtual void SetFrameSpeed(int n) { m_FrameSpeed = n; }
	virtual void SetCollision(bool b) { m_bIsCollision = b; }

private:

};


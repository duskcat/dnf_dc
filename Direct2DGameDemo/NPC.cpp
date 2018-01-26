#include "NPC.h"

NPC::NPC(LPCTSTR tex,LPCTSTR type,int count,float x,float y,LPCTSTR name)
{
	m_pTex = CreateTextures(tex, type, count, ii);
	m_nWidth = ii.width;
	m_nHight = ii.hight;
	m_fPosX = x;
	m_fPosY = y;
	m_nFrameCount = count;
	m_pLineArr = new D3DXVECTOR2[5];
	int w, h;
	m_pTexDiaBox = CreateTexture(L"image//speak.png", w,h);
}

void NPC::Init()
{
}

void NPC::Render()
{
	if (m_bIsCollision)
		SPRITE_DRAW(m_pTexDiaBox, 0, 0);
	//äÖÈ¾¶àÍ¼Æ¬¶¯»­
	if (m_pTex)
	{
		curTime = GetTickCount();
		SPRITE_DRAW(m_pTex[curFrame], m_fPosX-mapPosX, m_fPosY-ii.m_imageInfo[curFrame].hight);
		if (curTime - lastTime >= m_FrameSpeed)
		{
			curFrame++;
			lastTime = curTime;
		}
		if (curFrame == m_nFrameCount)
		{
			curFrame = 0;
		}
	}
	SetRect(&m_npcRange, m_fPosX - mapPosX, m_fPosY- ii.m_imageInfo[curFrame].hight, m_fPosX + ii.m_imageInfo[curFrame].width-mapPosX, m_fPosY);

	m_pLineArr[0].x = m_fPosX - mapPosX;
	m_pLineArr[0].y = m_fPosY - ii.m_imageInfo[curFrame].hight;
	m_pLineArr[1].x = m_fPosX + ii.m_imageInfo[curFrame].width - mapPosX;
	m_pLineArr[1].y = m_fPosY - ii.m_imageInfo[curFrame].hight;
	m_pLineArr[3].x = m_fPosX - mapPosX;
	m_pLineArr[3].y = m_fPosY;
	m_pLineArr[2].x = m_fPosX + ii.m_imageInfo[curFrame].width - mapPosX;
	m_pLineArr[2].y = m_fPosY;
	m_pLineArr[4].x = m_fPosX - mapPosX;
	m_pLineArr[4].y = m_fPosY - ii.m_imageInfo[curFrame].hight;
}

void NPC::CleanUp()
{
	for (int i=0;i<m_nFrameCount;i++)
	{
		Safe_Release(m_pTex[i]);
	}
}

void NPC::RenderLine()
{
	g_pLine->Draw(m_pLineArr, 5, D3DCOLOR_XRGB(255, 0, 0));
}

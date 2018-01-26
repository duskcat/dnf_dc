#include "Animation.h"
//#include "cDNF.h"

Animation::Animation()
{
	curFrame = 0;

}

Animation::Animation(LPCTSTR fileName, float x, float y, int row, int list, bool isLoop)
{
	m_pAniTextureSingle = (CreateTexture(fileName, m_nWidth, m_nHight));

	if (!m_pAniTextureSingle)
		MessageBox(NULL, fileName, L"asd", NULL);
	m_fPosX = x;
	m_fPosy = y-m_nHight/row;
	m_bIsLoop = isLoop;
	m_nRow = row;
	m_nList = list;
}

Animation::Animation(LPCTSTR fileName, LPCTSTR fileType, int count, float x, float y,int speed,bool isLoop)
{
	curFrame = 0;
	if(speed>0)
		m_nFrameSpeed = speed;
	m_pAniTextures = CreateTextures(fileName, fileType,count,imageInfo);
	if (!m_pAniTextures)
	{
		MessageBox(NULL, L"wrong", L"ErrorAni！", NULL);
	}
	m_nAniFrameCount = count;
	m_fPosX = x;
	m_fPosy = y-imageInfo.m_imageInfo[curFrame].hight;
	m_bIsLoop = isLoop;
	m_nWidth = imageInfo.width;
	m_nHight = imageInfo.hight;
}

Animation::Animation(LPCTSTR fileName, int count, float x, float y, int speed, D3DXVECTOR2 scaling)
{
	curFrame = 0;
	if (speed > 0)
		m_nFrameSpeed = speed;
	m_pAniTextures = CreateTextures(fileName,L"png", count, imageInfo);
	if (!m_pAniTextures)
	{
		MessageBox(NULL, L"wrong", L"ErrorAni！", NULL);
	}
	m_nAniFrameCount = count;
	m_fPosX = x;
	m_fPosy = y - imageInfo.m_imageInfo[curFrame].hight;
	m_bIsLoop = true;
	m_nWidth = imageInfo.width;
	m_nHight = imageInfo.hight;
	m_vSacling = scaling;
}

bool Animation::Init()
{
	return false;
}

void Animation::Render()
{
	if (!m_bIsRender)
		return;
	//渲染多图片动画
	if (m_pAniTextures)
	{
		curTime = GetTickCount();
		SPRITE_DRAW(m_pAniTextures[curFrame], m_fPosX, m_fPosy);
		if(curTime-lastTime>=m_nFrameSpeed)
		{
			curFrame++;
			lastTime = curTime;
		}
		if (curFrame == m_nAniFrameCount)
		{
			curFrame = 0;  m_bIsplayed = true; if (!m_bIsLoop) { m_bIsRender = false; CleanUp();}
		}
		else
			m_bIsplayed = false;
		if (curTime - lastTime >= 1000)
		{
			curFrame = 0;
		}
	}
	//渲染单图动画
	if (m_pAniTextureSingle)
	{
		curTime = GetTickCount();		
		static RECT rect;
		SetRect(&rect, (m_nWidth / m_nList)*curFrame, (m_nHight / m_nRow)*mdir, (m_nWidth / m_nList)*(curFrame +1), (m_nHight / m_nRow)*(mdir+1));
		SPRITE_DRAWEX(m_pAniTextureSingle, &rect, m_fPosX, m_fPosy);
		if(curTime-lastTime>=m_nFrameSpeed)
		{
			curFrame++;
			lastTime = curTime;
		}
		if (curFrame == m_nList)
		{
			curFrame = 0; if (!m_bIsLoop) { m_bIsRender = false; CleanUp(); }
		}

	}
}

void Animation::RenderScaling()
{
	if (m_pAniTextures)
	{
		static D3DXMATRIX pMax;
		D3DXMatrixTransformation2D(&pMax,&D3DXVECTOR2(m_fPosX-mapPosX,m_fPosy), 0, &m_vSacling, 0, 0, 0);
		g_pSprite->SetTransform(&pMax);	
		SPRITE_DRAW(m_pAniTextures[curFrame], m_fPosX-mapPosX, m_fPosy);
		curTime = GetTickCount();
		if (curTime - lastTime >= m_nFrameSpeed)
		{
			curFrame++;
			lastTime = curTime;
		}
		if (curFrame == m_nAniFrameCount)
			curFrame = 0;
		g_pSprite->SetTransform(&g_pMax);
	}
}

void Animation::Render(float x, float y,Direction dir)
{
	Update(x,y,dir);
	if (m_pAniTextures)
	{	
		SPRITE_DRAW(m_pAniTextures[curFrame], m_fPosX, m_fPosy);
		IntervalTime(SKILL_ANI_INTERVAL_TIME, curFrame);
		if (curFrame == m_nAniFrameCount)
			curFrame = 0;
	}

	if (m_pAniTextureSingle)
	{
		static RECT rect;
		SetRect(&rect, (m_nWidth / m_nList)*curFrame, (m_nHight / m_nRow)*mdir, (m_nWidth / m_nList), (m_nHight / m_nRow));
		SPRITE_DRAWEX(m_pAniTextureSingle, &rect, m_fPosX, m_fPosy);
		IntervalTime(ROLE_ANI_INTERVAL_TIME, curFrame);
		if (curFrame == m_nList)
			curFrame = 0;
	}

}

void Animation::CleanUp()
{
	for (int i=0;i<m_nAniFrameCount;i++)
	{
		Safe_Release(m_pAniTextures[i]);
	}
	Safe_delete(m_pAniTextures);
	Safe_Release(m_pAniTextureSingle);
}

void Animation::Update(float x, float y,Direction dir)
{
	m_fPosX = x;
	m_fPosy = y -imageInfo.m_imageInfo[curFrame].hight;
	mdir = dir;
	/*if (m_fPosX >= (640-m_nWidth))
		m_fPosX = 10.0f;*/
}

void Animation::UpdateOdd(float x, float y, Direction dir)
{
	m_fPosX = x;
	m_fPosy = y - m_nHight / m_nRow;
	mdir = dir;
}

//创建多图动画
bool Animation::CreateAnimation(LPCTSTR fileName,LPCTSTR fileType, int count, float x, float y,bool isLoop)
{
	if (!fileName)
		return false;
	m_pAniTextures = CreateTextures(fileName, fileType, count,imageInfo);
	if (!m_pAniTextures)
	{
		MessageBox(NULL, L"wrong", L"ErrorAni！", NULL);
	}
	m_nAniFrameCount = count;
	m_fPosX = x;
	m_fPosy = y - imageInfo.m_imageInfo[curFrame].hight;
	m_bIsLoop = isLoop;
	return true;
}

//创建单图动画
bool Animation::CreateAnimation(LPCTSTR fileName, float x, float y, int row,int list, bool isLoop)
{
	if (!fileName)
		return false;
	m_pAniTextureSingle = CreateTexture(fileName, m_nWidth, m_nHight);

	if(!m_pAniTextureSingle)
		MessageBox(NULL, fileName, L"asd", NULL);
	m_bIsLoop = isLoop;
	m_nRow = row;
	m_nList = list;
	m_fPosX = x;
	m_fPosy = y - m_nHight / m_nRow;
	return true;
}

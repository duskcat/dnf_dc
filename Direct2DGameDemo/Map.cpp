#include "Map.h"
#define SHOW_WIDTH 820
#define SHOW_HIGHT 480

Map::Map()
{
	m_pGui = new GUIClass(640, 480);
}

bool Map::Init()
{
	return true;
}

void Map::Render(float x,float y)
{
	static RECT rect,rectPros;
	if(m_pProspect)
		SPRITE_DRAW(m_pProspect, 0, 0);
	//绘制背景
	//SPRITE_DRAW(m_pSprite, m_pBackground, 0, 0);
	if (mapPosX >= 0&&mapPosX<m_nWidthBg- SHOW_WIDTH)
	{
		SetRect(&rect, mapPosX, 0, mapPosX+ SHOW_WIDTH, 480);
		SPRITE_DRAWEX(m_pBackground, &rect, 0, 0);
	}
	else if(mapPosX >= (m_nWidthBg - SHOW_WIDTH))
	{
		SetRect(&rect, m_nWidthBg - SHOW_WIDTH, 0, m_nWidthBg, 480);
		SPRITE_DRAWEX(m_pBackground, &rect, 0, 0);
	}
	else
	{
		SetRect(&rect, 0, 0, SHOW_WIDTH, 480);
		SPRITE_DRAWEX(m_pBackground, &rect, 0, 0);
	}

	if (mapPosX >= m_nWidthBg)
		mapPosX = m_nWidthBg;
	if (mapPosX <= 0)
		mapPosX = 0;
	//绘制门

	//绘制GUI
	/*static POINT point;
	point = GetMousePosition(hWnd);
	ProcessGUI(m_pGui, point.x, point.y, GUICALLBACK);*/

	//绘制怪物
	//monsterMgr->Render();
}

void Map::CleanUp()
{
	Safe_Release(m_pBackground);
	Safe_Release(m_pProspect);
}

void Map::AddMap(LPCTSTR bgName, LPCTSTR prosName)
{
	//创建场景
	if (bgName)
	if (!CREATE_TEXTURE_IMAGEINFO(bgName,&imgInfo, &m_pBackground))
	{
		mapWidth = m_nWidthBg = imgInfo.Width;
		mapHight = m_nHightBg = imgInfo.Height;
	}
	if(prosName)
	if (!CREATE_TEXTURE_IMAGEINFO(prosName,&imgInfo,&m_pProspect))
	{
		m_nWidthPros = imgInfo.Width;
		m_nHightPros = imgInfo.Height;
	}
	//创建门

}

void Map::AddDoor(LPCTSTR doorName, int doorType, float xPos, float yPos)
{
}

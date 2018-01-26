#include "Door.h"

Door::Door(DoorInfo di, float x, float y)
{
	doorInfo = di;
	m_pTexClose = CreateTexture(di.closeTex, m_nWidth, m_nHight);
	m_pTexDoor = CreateTexture(di.path, m_nWidth, m_nHight);
	if (!m_pTexClose)
		m_bIsOpen = true;
	if (!m_pTexDoor)
	{
		m_nWidth = 100;
		m_nHight = 40;	
	}
	m_fPosX = x;
	m_fPosY = y;
}

bool Door::Init()
{
	return true;
}

void Door::Render()
{
	if (m_pTexDoor)
		SPRITE_DRAW(m_pTexDoor, m_fPosX - mapPosX, m_fPosY);
	if(!m_bIsOpen)
		SPRITE_DRAW(m_pTexClose, m_fPosX - mapPosX, m_fPosY);
	SetRect(&m_doorRange, m_fPosX - mapPosX, m_fPosY+m_nHight/4*3, m_fPosX + m_nWidth/2 - mapPosX, m_fPosY+m_nHight);
}

void Door::CleanUp()
{
	Safe_Release(m_pTexDoor);
	Safe_Release(m_pTexClose);
}

bool Door::CreateDoor(LPCTSTR doorName, DoorInfo di, float xPos, int yPos)
{
	return false;
}

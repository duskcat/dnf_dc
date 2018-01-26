#pragma once
#include "stdafx.h"
#include "Door.h"
#include "GUIControls.h"

//µÿÕº¿‡–Õ
#define MAP_TYPE_DUNGEON 1
#define MAP_TYPE_TOWN    2

class Map
{
protected:
	LPDIRECT3DTEXTURE9 m_pProspect=NULL;
	LPDIRECT3DTEXTURE9 m_pBackground=NULL;
	Door *m_pDoor=NULL;
	int m_nDoorNum = 0;
	GUIClass *m_pGui=NULL;
	float m_nWidthBg, m_nHightBg;
	float m_nWidthPros, m_nHightPros;
	D3DXIMAGE_INFO imgInfo;
	int m_nMapType;
	int m_nDoorType;
public:
	Map();
	~Map() { CleanUp(); }
	virtual bool Init();
	virtual void Render(float x, float y);
	virtual void CleanUp();
	virtual void AddMap(LPCTSTR bgName,LPCTSTR prosName);
	virtual void AddDoor(LPCTSTR doorName,int doorType,float xPos,float yPos);
};

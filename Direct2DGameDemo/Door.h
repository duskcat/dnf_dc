#pragma once
#include "stdafx.h"

#define DOOR_TYPE_IN	 1
#define DOOR_TYPE_OUT	 2
#define DOOR_TYPE_CHOOSE 3

struct DoorInfo
{
	LPCWSTR path;
	LPCWSTR closeTex;
	string xml;
	float rolePosX;
	float rolePosY;
	float mapx;
};

class Door
{
protected:
	LPDIRECT3DTEXTURE9 m_pTexDoor = NULL;
	LPDIRECT3DTEXTURE9 m_pTexClose;
	float m_fPosX, m_fPosY;
	int m_nWidth, m_nHight;
	bool m_bIsInited;
	bool m_bIsOpen;
	DoorInfo doorInfo;
	bool m_bIsCollision = false;
	RECT m_doorRange;
public:
	Door() {}
	Door(DoorInfo di,float x,float y);
	~Door() { CleanUp(); }
	virtual bool Init();
	virtual void Render();
	virtual void CleanUp();
	virtual bool CreateDoor(LPCTSTR doorName,DoorInfo di,float xPos,int yPos);
	virtual DoorInfo GetDoorInfo() { return doorInfo; }
	virtual void SetCollision(bool b) { m_bIsCollision = b; }
	bool IsOpen() { return m_bIsOpen; }
	void DoorState(bool b) { m_bIsOpen = b; }
	virtual RECT GetRange() { return m_doorRange; }
};


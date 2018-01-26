#pragma once

#include "AnimationMgr.h"
#include "NpcMgr.h"
#include "DoorMgr.h"
#include "MonsterMgr.h"
#include "Map.h"
#include "Role.h"
#include "GUIControls.h"
#include "stdafx.h"

#define townInst Town::Instance()
#define monsterInst MonsterMgr::Instance()
#define guiInst GUIClass::Instance()

class Town
{
protected:
	LPDIRECT3DTEXTURE9 m_pTexLoad;
	Map *m_pMap = NULL;				//��ͼ
	int m_nMapType = MAP_TYPE_TOWN;	//��ͼ����
	int m_nMapCount = 0;				//��ͼid
	int initedMap[10];				//�Ѽ��ص�ͼ
	LPCTSTR m_sTownName = NULL;		//��ͼ����
	int m_nNpcCount = 0;			//��ͼnpc����
	AnimationMgr *m_pAniMgr = NULL;	//��ͼ��������
	LPCTSTR m_sMapBg = NULL;		//��ͼ������
	LPCTSTR m_sMapPros = NULL;		//��ͼԶ����
	//NPC
	NpcMgr *m_pNpcMgr = NULL;
	DoorMgr *m_pDoorMgr = NULL;		//��������
	XmlData xmlData;
	float rolePosX=0,rolePosY=0;
	GUIClass *m_pGui = NULL;
	GUIClass *m_pGuiOption;
	float mBeginTime, mEndTime;
	bool m_bIsLoad;
public:
	Town();
	static Town* Instance() { static Town town; return &town; }
	Town(LPCTSTR mapName,LPCTSTR bgName);
	~Town() { CleanUp(); }
	virtual bool Init(string dataFile);
	virtual bool Render();
	virtual void RenderLine();
	virtual bool CleanUp();
	bool IsInited(int id);
	virtual float GetRoleX() { return rolePosX; }
	virtual float GetRoleY() { return rolePosY; }
private:

};

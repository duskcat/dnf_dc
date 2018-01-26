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
	Map *m_pMap = NULL;				//地图
	int m_nMapType = MAP_TYPE_TOWN;	//地图类型
	int m_nMapCount = 0;				//地图id
	int initedMap[10];				//已加载地图
	LPCTSTR m_sTownName = NULL;		//地图名字
	int m_nNpcCount = 0;			//地图npc数量
	AnimationMgr *m_pAniMgr = NULL;	//地图动画管理
	LPCTSTR m_sMapBg = NULL;		//地图背景名
	LPCTSTR m_sMapPros = NULL;		//地图远景名
	//NPC
	NpcMgr *m_pNpcMgr = NULL;
	DoorMgr *m_pDoorMgr = NULL;		//城镇出入口
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

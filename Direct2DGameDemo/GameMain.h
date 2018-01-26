#pragma once

#include "stdafx.h"
#include "GUIControls.h"
#include "Map.h"
//#include "Role.h"
#include "MonsterMgr.h"
#include "Town.h"

class GameMain
{
protected:
	LPD3DXFONT m_pFont;
	LPDIRECT3DTEXTURE9 m_pBackground;
	LPDIRECT3DTEXTURE9 *m_pBGs;
public:
	bool m_bIsInited=false;
	GameMain() {}
	~GameMain() { CleanUp(); }
	virtual bool Init();
	virtual void Render(int mouseX,int mouseY);
	virtual void CleanUp();
};
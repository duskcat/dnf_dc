#pragma once
#include "stdafx.h"
#include "GUIControls.h"

class ChooseRole
{
protected:
	LPD3DXFONT m_pFont;
	bool m_bHasRole;
	int m_nRoleCount;
	int m_nWidth, m_nHeight;
	D3DXIMAGE_INFO m_ImageInfo;
	bool m_bMouseDown=false;
	GUIClass *m_pGui;
public:
	bool m_bIsInited = false;
	ChooseRole();
	~ChooseRole() { CleanUp(); }
	virtual bool SelectRole();
	virtual bool CreateRole();
	virtual bool Render(int mouseX,int mouseY,void(*funcPtr)(int id,int state));
	virtual void CleanUp();
};


class SelectChannel
{
protected:
	LPDIRECT3DTEXTURE9 m_pBackgroundTex;
	LPDIRECT3DTEXTURE9 *m_pChannelTexs;
	LPDIRECT3DTEXTURE9 m_pSelectCNTex;
	bool m_bMouseDown = false;
	GUIClass *m_pGui;
public:
	bool m_bIsInited = false;
	SelectChannel();
	~SelectChannel() { CleanUp(); }
	virtual bool Init();
	virtual void Render(int mouseX, int mouseY, void(*funcPtr)(int id, int status));
	virtual void CleanUp();
};
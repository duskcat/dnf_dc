#pragma once
#include "cEngine.h"
#include "stdafx.h"
#include "GUIControls.h"
#include "BeginIF.h"
#include "GameMain.h"

class cDNF :public cApplication
{
protected:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_ImageInfo;
	DWORD StartTime;
	DWORD IntervalTime;
	int m_MouseX = 0, m_MouseY = 0;
public:
	cDNF() {}
	~cDNF() {CleanUp();}
	BOOL Init();						//direct3D资源初始化
	BOOL Render(HWND hWnd);			//Direct3D渲染
	BOOL CleanUp();					//Direct3D资源清理
	VOID ShowText(HWND hWnd);
};


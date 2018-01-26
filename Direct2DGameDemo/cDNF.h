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
	BOOL Init();						//direct3D��Դ��ʼ��
	BOOL Render(HWND hWnd);			//Direct3D��Ⱦ
	BOOL CleanUp();					//Direct3D��Դ����
	VOID ShowText(HWND hWnd);
};


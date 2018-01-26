#pragma once
#ifndef ENGINE_SYSTEM_H_
#define ENGINE_SYSTEM_H_

#include "stdafx.h"

#define WINDOW_WIDTH 1148
#define WINDOW_HEIGHT 510
#define WINDOW_WIDTH_NEW 1148
#define WINDOW_HEIGHT_NEW 510
extern HINSTANCE gInstance;

class cApplication
{
protected:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	ID3DXFont* m_pFont = NULL;

	HINSTANCE m_hInstance;
	HWND m_hWnd;

	TCHAR m_Class[MAX_PATH];
	TCHAR m_Caption[MAX_PATH];

	WNDCLASSEX m_wcex;
	DWORD m_Style;
	DWORD m_xPos, m_yPos;
	DWORD m_Width, m_Height;
	
public:
	cApplication();
	HINSTANCE GethInstance();
	HWND GethWnd();
	BOOL Resize(long Width, long Height);
	BOOL Run();
	BOOL Direct3D_Init(HWND hWnd);
	virtual BOOL Init() { return TRUE; }
	virtual BOOL Render(HWND hwnd) { return TRUE; }
	virtual BOOL CleanUp() { return TRUE; }
};

static cApplication* g_pApplication = NULL;
static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#endif // !ENGINE_SYSTEM_H_

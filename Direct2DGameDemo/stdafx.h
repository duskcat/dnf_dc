#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#ifndef WINDOW_H_
#define WINDOW_H_
#include <windows.h>
#include <tchar.h>
#include <timeapi.h>
#include <list>
#include <map>
#include <atlstr.h>
#include "tinystr.h"
#include "tinyxml.h"
#include "cInput.h"
#include <direct.h>
#include <string>
using std::string;
using namespace std;
#endif // !STDAFX_H_

#ifndef DIRECTX_H_
#define DIRECTX_H_
#pragma comment(lib,"winmm.lib")
#include <d3d9.h>
#pragma comment(lib,"d3d9.lib")
#include<d3dx9.h>
#pragma  comment(lib,"d3dx9.lib")
#endif // !DIRECTX_H_

#ifndef SAFE_DELETE_H_
#define SAFE_DELETE_H_
template<typename T>inline void Safe_delete(T* &p)
{
	if (p) { delete p; p = nullptr; }
}

template<typename T>inline void Safe_Release(T* &p)
{
	if (p) { p->Release(); p = nullptr; }
}
#endif

#ifndef MACRO_H_
#define MACRO_H_

#include "macroDeclar.h"

#define CREATE_FONT(pD3dDevice,Height,Width,Italic,str,pFont) FAILED(D3DXCreateFont(pD3dDevice,Height,Width,0,1,Italic,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,0,str,pFont))
//#define Pos(x,y) &

//创建纹理使用文件宽高
#define CREATE_TEXTURE(filename,texTure) FAILED(D3DXCreateTextureFromFileEx(g_pDevice,filename,D3DX_FROM_FILE,D3DX_FROM_FILE,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_XRGB(255, 255, 255),NULL,NULL,texTure))
//创建纹理使用指定宽高
#define CREATE_TEXTUREWH(filename,width,height,texTure) FAILED(D3DXCreateTextureFromFileEx(g_pDevice,filename,width,height,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_XRGB(255, 255, 255),NULL,NULL,texTure))

#define CREATE_TEXTURE_IMAGEINFO(filename,imgInfo,texTure) FAILED(D3DXCreateTextureFromFileEx(g_pDevice,filename,D3DX_FROM_FILE,D3DX_FROM_FILE,0,0,D3DFMT_UNKNOWN,D3DPOOL_MANAGED,D3DX_FILTER_LINEAR,D3DX_FILTER_LINEAR,D3DCOLOR_XRGB(255, 255, 255),imgInfo,NULL,texTure))
//使用精灵绘制
#define SPRITE_DRAW(texTure,x,y) if(texTure)g_pSprite->Draw(texTure, NULL, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(x, y, 0), D3DCOLOR_XRGB(255, 255, 255))

#define SPRITE_DRAWEX(texTure,rect,x,y) if(texTure)g_pSprite->Draw(texTure, rect, &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(x, y, 0), D3DCOLOR_XRGB(255, 255, 255))

//获得当前系统时间(毫秒级)
#define GetCurtime GetTickCount()

//#define KEY_DOWN(vk_code) GetAsyncKeyState(vk_code)&0x8000
#define DIKEYDOWN(dik_code) g_pInput->IsKeyDown(dik_code)
#define DIMOUSEDOWN(dim_code) g_pInput->IsMouseButtonDown(dim_code)

//间隔时间宏
#define ROLE_ANI_INTERVAL_TIME 200
#define SKILL_ANI_INTERVAL_TIME 100
#define ITEM_ANI_INTERVAL_TIME 70

#define ROLE_RUN_SPEED 0.20f
#define ROLE_WALK_SPEED 0.07f

//加载时背景图显示时间
#define loadTime 1.0f

//图片信息
struct  Image_Info
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO ImageInfo;
	UINT Width, Height;
};

//游戏状态
#define GAME_START_IF	1
#define GAME_ROLE_IF	2
#define GAME_CHANNEL_IF 3
#define GAME_MAIN_IF	4

//自定义顶点格式
struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD color;
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)  //FVF灵活顶点格式
#endif


#ifndef FILE_H_
#define FILE_H_
#endif

#ifndef FUNCTION_COMMON
#define FUNCTION_COMMON

//全局变量定义
extern LPDIRECT3DDEVICE9 g_pDevice;
extern LPD3DXSPRITE g_pSprite;
extern HWND g_hWnd;
//常用字体
extern ID3DXFont *g_pCommFont;

//计算间隔时间
inline bool IntervalTimeBigger(float n)
{
	static float curTime, LastTime = 0;
	curTime = GetTickCount()*0.001f;
	if (LastTime == 0)
		LastTime = curTime;
	if (curTime - LastTime >= n)
	{
		LastTime = curTime;
		return true;
	}
	return false;
}


inline void IntervalTime(float n, int &i)
{
	static DWORD curTime, LastTime = 0;
	curTime = GetTickCount();
	if (curTime - LastTime >= n)
	{
		i++;
		LastTime = curTime;
	}
}
//获取鼠标位置
inline POINT GetMousePosition(HWND hWnd)
{
	static POINT point;
	GetCursorPos(&point);
	ScreenToClient(hWnd, &point);
	return point;
}

//创建多张纹理
inline LPDIRECT3DTEXTURE9* CreateTextures(LPCTSTR fileName,LPCTSTR fileType, int count)
{
	static TCHAR strFileName[100];
	LPDIRECT3DTEXTURE9 *pTexs = new LPDIRECT3DTEXTURE9[count];
	for (int i = 0; i < count; i++)
	{
		swprintf_s(strFileName, L"%s%d.%s", fileName, i, fileType);
		if(CREATE_TEXTURE(strFileName, &pTexs[i]))
			MessageBox(NULL, strFileName, L"ErrorAni！", NULL);
	}
	if (!pTexs)
	{
		//return false; 
		MessageBox(NULL, strFileName, L"ErrorAni！", NULL);
		return NULL;
	}

	return pTexs;
}

class ImageInfo
{
protected:
	
public:
	int width;
	int hight;
	ImageInfo *m_imageInfo;
	ImageInfo() {}
	~ImageInfo() {}
private:

};
//创建多张纹理并输出文件宽高
inline LPDIRECT3DTEXTURE9* CreateTextures(LPCTSTR fileName, LPCTSTR fileType, int count,ImageInfo &(imageInfo))
{
	static TCHAR strFileName[100];
	D3DXIMAGE_INFO imgInfo;
	imageInfo.m_imageInfo = new ImageInfo[count];
	LPDIRECT3DTEXTURE9 *pTexs = new LPDIRECT3DTEXTURE9[count];
	for (int i = 0; i < count; i++)
	{
		swprintf_s(strFileName, L"%s%d.%s", fileName, i, fileType);
		if (CREATE_TEXTURE_IMAGEINFO(strFileName,&imgInfo, &pTexs[i]))
			MessageBox(NULL, strFileName, L"ErrorAni！", NULL);
		imageInfo.m_imageInfo[i].width = imgInfo.Width;
		imageInfo.m_imageInfo[i].hight = imgInfo.Height;
	}
	if (!pTexs)
	{
		//return false; 
		MessageBox(NULL, strFileName, L"ErrorAni！", NULL);
		return NULL;
	}
	return pTexs;
}

//创建单张纹理
inline LPDIRECT3DTEXTURE9 CreateTexture(LPCTSTR fileName, int &w, int &h)
{
	D3DXIMAGE_INFO imgInfo;
	LPDIRECT3DTEXTURE9 pTex = NULL;
	if (CREATE_TEXTURE_IMAGEINFO(fileName, &imgInfo, &pTex))
		return NULL;
	w = imgInfo.Width;
	h = imgInfo.Height;
	return pTex;
}

#endif

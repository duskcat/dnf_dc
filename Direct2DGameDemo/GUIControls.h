#pragma once
#include "stdafx.h"
//控件类型
#define GUI_STATICTEXT 1
#define GUI_BUTTON     2
#define GUI_BACKGROUND 3

//鼠标状态
#define BUTTON_UP		1
#define BUTTON_OVER		2
#define BUTTON_DOWN		3
#define BUTTON_DOWNUP	4

//控件ID
#define STATIC_ID_1		1
#define STATIC_ID_2		2
#define BUTTON_ID_1		3
#define BUTTON_ID_2		4
#define BUTTON_ID_3		5
#define BUTTON_ID_4		6
#define BUTTON_ID_5		7
#define BUTTON_ID_6		8
#define BUTTON_ID_7		9
#define BUTTON_ID_8		10
#define BUTTON_ID_9		11
#define BUTTON_ID_10	12
#define BUTTON_ID_11	13

//FVF灵活顶点
struct GUIVERTEX
{
	float x, y, z, rhw;
	unsigned long color;
	float u, v;
};
#define D3DFVF_GUI (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//控件属性结构体
struct GUICONTROL
{
	int m_type;	//控件类型
	int m_id;	//控件id
	unsigned long m_color;	//控件颜色
	int m_listID;
	LPCWSTR xml;
	float m_xPos, m_yPos;	//控件位置
	float m_width, m_height;	//控件宽高

	wchar_t *m_text;	//文字内容
	LPDIRECT3DTEXTURE9 m_Background;	//控件背景图
	LPDIRECT3DTEXTURE9 m_pBGLight;
	LPDIRECT3DTEXTURE9 m_upTex=NULL, m_downTex=NULL, m_overTex=NULL;	//按钮3状态纹理图
};

class GUIClass
{
private:
	D3DXIMAGE_INFO m_ImageInfo;
	LPD3DXFONT *m_pFonts;	//D3D字体对象
	GUICONTROL *m_pControls;	//控件对象
	LPDIRECT3DVERTEXBUFFER9 *m_pVertexBuffer;	//顶点缓存
	GUICONTROL m_Background;	//背景控件
	//LPDIRECT3DVERTEXBUFFER9 m_BackgroundBuffer;	//背景图缓冲区对象

	bool m_bIsBackgroundUsed;
	int m_nTotalFontNum;
	int m_nTotalControlNum;
	int m_nTotalBufferNum;
	int m_nWindowWidth;
	int m_nWindowHeight;
	bool m_bIsRender=false;
public:
	float lastTime, curTime;
	LPDIRECT3DTEXTURE9 *m_pBGs;
	LPDIRECT3DTEXTURE9 m_pTex=NULL;
	int m_nBgCount;
	bool m_bIsLoading=true;
	GUIClass(int w, int h);
	~GUIClass() { ClearUp(); }
	void Render();
	GUICONTROL *GetBackground() { return &m_Background; }
	GUICONTROL *GetBackground(int curBg);
	//LPDIRECT3DVERTEXBUFFER9 GetBackgroundBuffer() { return m_BackgroundBuffer; }

	int GetTotalFontNum() { return m_nTotalFontNum; }
	int GetTotalControlNum() { return m_nTotalControlNum; }
	int GetTotalBufferNum() { return m_nTotalBufferNum; }
	int GetWindowWidth() { return m_nWindowWidth; }
	int GetWindowHeight() { return m_nWindowHeight; }

	bool IsBackgroundUsed() { return m_bIsBackgroundUsed; }
	void SetWindowSize(int w, int h) { m_nWindowWidth = w; m_nWindowHeight = h; }

	LPD3DXFONT GetFont(int id)	//返回字体
	{
		if (id < 0 || id >= m_nTotalFontNum)return NULL;
		return m_pFonts[id];
	}

	GUICONTROL *GetGUIControl(int id)	//返回控件
	{
		if (id < 0 || id >= m_nTotalControlNum)return NULL;
		return &m_pControls[id];
	}

	bool CreateTextFont(wchar_t *fontName, int size, int *fontID);	//创建字体
	bool AddBackground(LPCTSTR filename, LPCTSTR loadImageName);
	bool AddBackground(LPCTSTR fileName, int count,LPCTSTR fileType, LPCTSTR loadImageName);
	bool AddStaticText(int id, wchar_t *text, float x, float y, unsigned long color, int fontID);
	bool AddButton(int id, float x, float y, wchar_t *up,wchar_t *over, wchar_t *down);
	bool AddButton(int id, float x, float y,int w,int h, LPCWSTR up, LPCWSTR over, LPCWSTR down);
	bool AddButton(int id, float x, float y, int w, int h, LPCWSTR up, LPCWSTR over, LPCWSTR down, LPCWSTR xml);
	void ClearUp();
	static GUIClass* Instance() { static GUIClass gui(640,480); return &gui;}
};

//渲染一张背景所有按钮
void ProcessGUI(GUIClass *gui, int mouseX, int mouseY, void(*funcPtr)(int id, int status));
//渲染多背景之一
void ProcessGUI(GUIClass *gui, int mouseX, int mouseY, void(*funcPtr)(int id, int status),int curBg);
//渲染所有背景
void ProcessGUI(GUIClass * gui, int mouseX, int mouseY, void(*funcPtr)(int id, int status), bool allBg);
//EditBox
struct MFEditBox
{
	wchar_t* name;
	int id;
	wchar_t* text;
	int m_xPos, m_yPos;
	float m_width, m_height;
	LONG m_mouseX, m_mouseY;
	LPDIRECT3DTEXTURE9 m_pBackground=NULL;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer = NULL;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer = NULL;
};

class EditBoxClass
{
protected:
	LPDIRECT3DDEVICE9 m_pDevice;
	LPD3DXSPRITE m_pSprite;
	D3DXVECTOR2* m_pLineArr = NULL;
	HWND m_hwnd;
	LPD3DXLINE m_pLine;
	MFEditBox* m_pEditBox;
	int m_nEditBoxCount=0;
	
public:
	bool CtrlRender(LONG mouseX, LONG monseY);
	EditBoxClass(LPDIRECT3DDEVICE9 device,LPD3DXSPRITE sprite);
	virtual bool AddEditBoxFromFile(int xPos,int yPos,wchar_t *fileName);
	virtual bool AddEditBox(int x,int y,int w,int h);
	virtual bool ShowControl();
	virtual wchar_t* GetText();
	virtual bool SetText();
	~EditBoxClass();
	virtual void CleanUp();
};


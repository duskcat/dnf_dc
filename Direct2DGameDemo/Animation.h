#pragma once

#include "stdafx.h"
#include "macroFunc.h"

enum Direction
{
	Dir_Left = 0,
	Dir_Up = 1,
	Dir_Right=2,
	Dir_Down=3
};

class Animation
{
protected:
	LPDIRECT3DTEXTURE9 *m_pAniTextures=NULL;
	LPDIRECT3DTEXTURE9 m_pAniTextureSingle=NULL;
	int m_nAniFrameCount;
	float m_fPosX, m_fPosy;
	int m_nWidth, m_nHight;
	ImageInfo imageInfo;
	//ImgInfo* m_pImgInfo=NULL;
	bool m_bIsLoop;
	D3DXVECTOR2 m_vSacling;
	int m_nRow;
	int m_nList;
	int curFrame = 0;
	float curTime, lastTime;
	bool m_bIsRender=true;
	Direction mdir = Dir_Right;
	int m_nFrameSpeed=ROLE_ANI_INTERVAL_TIME;
	bool m_bIsplayed = false;
public:
	Animation();
	Animation(LPCTSTR fileName, float x, float y, int row, int list, bool isLoop);
	Animation(LPCTSTR fileName, LPCTSTR fileType, int count, float x, float y,int speed,bool isLoop);
	Animation(LPCTSTR fileName, int count, float x, float y, int speed, D3DXVECTOR2 scaling);
	~Animation() { CleanUp(); }
	virtual bool Init();
	virtual void Render();
	virtual void RenderScaling();
	virtual void Render(float x, float y, Direction dir);
	virtual void CleanUp();
	virtual void Update(float x,float y,Direction dir);
	virtual void UpdateOdd(float x, float y, Direction dir);
	virtual bool IsPlayed() { return m_bIsplayed; }
	float GetWidth() {return imageInfo.m_imageInfo[curFrame].width;}
	float GetHight() {return imageInfo.m_imageInfo[curFrame].hight;}
	//多图片创建动画(LPCTSTR,LPCTSTR,int count,float x,float y,int w,int h,bool);
	virtual bool CreateAnimation(LPCTSTR fileName, LPCTSTR fileType,int count,float x,float y,bool isLoop);

	//单张图片创建动画(LPCTSTR,float x,float y,int w,int h,bool);
	virtual bool CreateAnimation(LPCTSTR fileName, float x, float y,int row, int list, bool isLoop);
};

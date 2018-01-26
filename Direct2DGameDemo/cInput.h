#pragma once

#ifndef CINPUT_H_
#define CINPUT_H_
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"dxguid.lib")


class DirectInput
{
protected:
	LPDIRECTINPUT8 m_pDirectInput=NULL;
	LPDIRECTINPUTDEVICE8 m_pKeyboardDevice=NULL;
	LPDIRECTINPUTDEVICE8 m_pMouseDevice=NULL;
	char m_KeyStateBuffer[256] = {0};
	DIMOUSESTATE m_diMouseState = { 0 };
public:
	HRESULT Init(HWND hWnd,HINSTANCE hInstance,DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	VOID GetInput();
	bool IsKeyDown(int iKey);
	bool IsMouseButtonDown(int button);
	float MouseDX();
	float MouseDY();
	float MouseDZ();
	DirectInput();
	~DirectInput();

private:

};

extern DirectInput* g_pInput;
#endif
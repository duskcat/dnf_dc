#include "cInput.h"

HRESULT DirectInput::Init(HWND hWnd, HINSTANCE hInstance, DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDirectInput, NULL);

	m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, NULL);
	m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	m_pKeyboardDevice->SetCooperativeLevel(hWnd,keyboardCoopFlags);
	m_pKeyboardDevice->Acquire();
	m_pKeyboardDevice->Poll();

	m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL);
	m_pMouseDevice->SetDataFormat(&c_dfDIMouse);
	m_pMouseDevice->SetCooperativeLevel(hWnd, mouseCoopFlags);
	m_pMouseDevice->Acquire();
	m_pMouseDevice->Poll();


	return S_OK;
}

VOID DirectInput::GetInput()
{
	HRESULT hr=m_pKeyboardDevice->GetDeviceState(sizeof(m_KeyStateBuffer),(LPVOID)&m_KeyStateBuffer);
	if (hr)
	{
		m_pKeyboardDevice->Acquire();
		m_pKeyboardDevice->GetDeviceState(sizeof(m_KeyStateBuffer), (LPVOID)&m_KeyStateBuffer);
	}

	hr = m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_diMouseState);
	if (hr)
	{
		m_pMouseDevice->Acquire();
		m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_diMouseState);
	}
}

//键盘按下
bool DirectInput::IsKeyDown(int iKey)
{
	if (m_KeyStateBuffer[iKey] & 0x80)
		return true;
	return false;
}

//鼠标键按下
bool DirectInput::IsMouseButtonDown(int button)
{
	return (m_diMouseState.rgbButtons[button]&0x80)!=0;
}

float DirectInput::MouseDX()
{
	return (float)m_diMouseState.lX;
}

float DirectInput::MouseDY()
{
	return (float)m_diMouseState.lY;
}

float DirectInput::MouseDZ()
{
	return (float)m_diMouseState.lZ;
}

DirectInput::DirectInput()
{
	ZeroMemory(m_KeyStateBuffer, sizeof(m_KeyStateBuffer));
	ZeroMemory(&m_diMouseState, sizeof(m_diMouseState));
}

DirectInput::~DirectInput()
{
	if (m_pKeyboardDevice != NULL)
		m_pKeyboardDevice->Unacquire();
	if (m_pMouseDevice != NULL)
		m_pMouseDevice->Unacquire();
	if (m_pKeyboardDevice)
	{
		m_pKeyboardDevice->Release();
		m_pKeyboardDevice = NULL;
	}
	if (m_pMouseDevice)
	{
		m_pMouseDevice->Release();
		m_pMouseDevice = NULL;
	}
	if (m_pDirectInput)
	{
		m_pDirectInput->Release();
		m_pDirectInput = NULL;
	}
}
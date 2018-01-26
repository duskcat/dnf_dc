#include "cEngine.h"

HINSTANCE gInstance;
cApplication::cApplication()
{
	g_pApplication = this;
	m_hInstance = GetModuleHandle(NULL);
	gInstance = m_hInstance;
	swprintf_s(m_Class, L"DNF");
	swprintf_s(m_Caption, L"DNF");

	m_xPos = 0;
	m_yPos = 0;
	m_Width = WINDOW_WIDTH;
	m_Height = WINDOW_HEIGHT;
	m_Style = WS_OVERLAPPEDWINDOW;

	m_wcex.cbSize = sizeof(m_wcex);
	m_wcex.lpfnWndProc = WndProc;
	m_wcex.hInstance = m_hInstance;
	m_wcex.lpszClassName = m_Class;
	m_wcex.lpszMenuName = m_Caption;
	m_wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_wcex.cbWndExtra = 0;
	m_wcex.cbClsExtra = 0;
	m_wcex.style = CS_CLASSDC;
	m_wcex.hbrBackground = HBRUSH(WHITE_BRUSH);
}

HWND cApplication::GethWnd()
{
	return m_hWnd;
}

HINSTANCE cApplication::GethInstance()
{
	return m_hInstance;
}

BOOL cApplication::Run()
{
	MSG Msg;
	if (!RegisterClassEx(&m_wcex))
		return FALSE;

	m_hWnd = CreateWindow(m_Class, m_Caption, m_Style, m_xPos, m_yPos, m_Width, m_Height, NULL, NULL, m_hInstance, NULL);

	if (!m_hWnd)
		return FALSE;
	Resize(WINDOW_WIDTH, WINDOW_HEIGHT);

	if (!Direct3D_Init(m_hWnd))
		return FALSE;

	ShowWindow(m_hWnd, SW_NORMAL);
	UpdateWindow(m_hWnd);

	ZeroMemory(&Msg, sizeof(Msg));
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
			if (!Render(m_hWnd))
				break;
		}
	}
	CleanUp();
	UnregisterClass(m_Class, m_hInstance);
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}
}

BOOL cApplication::Resize(long Width, long Height)
{
	int xFrame = GetSystemMetrics(SM_CXSIZEFRAME);		//�߿���
	int yFrame = GetSystemMetrics(SM_CYSIZEFRAME);		//�߿�߶�
	int yCaption = GetSystemMetrics(SM_CYCAPTION);		//�������߶�
	int xScreen = GetSystemMetrics(SM_CXSCREEN);		//��Ļ���
	int yScreen = GetSystemMetrics(SM_CYSCREEN);		//��Ļ�߶�

	int cx = xFrame + Width + xFrame;					//���ڿ��
	int cy = yFrame + Height + yCaption + yFrame;		//���ڸ߶�

	SetWindowPos(m_hWnd, HWND_TOP,						//���ô���
		(xScreen - cx) / 2, (yScreen - cy) / 2,			//���ô���λ��
		cx, cy, SWP_SHOWWINDOW);						//���ô��ڴ�С
	return TRUE;
}

BOOL cApplication::Direct3D_Init(HWND hWnd)
{

	//����D3D�ӿ�ָ��
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	//��ȡӲ���豸��Ϣ
	D3DCAPS9 caps; int vp = 0;
	ZeroMemory(&caps, sizeof(caps));
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
		return FALSE;
	if (caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//�����豸ָ��
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 2;							//��̨������������˫����
	d3dpp.Windowed = true;								//����ģʽ
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			//��תЧ��
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.hDeviceWindow = hWnd;
	//d3dpp.EnableAutoDepthStencil = true;

	m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,								//Ĭ���Կ�
		D3DDEVTYPE_HAL,									//Ӳ�������
		hWnd,											//��ǰ���ھ��
		vp,												//�����������ģʽ
		&d3dpp,
		&m_pDevice);									//D3D�豸ָ��
														//��������ָ��
	D3DXCreateSprite(m_pDevice, &m_pSprite);


	Safe_Release(m_pD3D);

	if (!Init())
		return FALSE;
	return TRUE;
}
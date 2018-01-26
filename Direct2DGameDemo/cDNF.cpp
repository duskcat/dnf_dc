#include "cDNF.h"
#include "Town.h"
#include "NPC.h"
#include "Role.h"

GUIClass *g_pStartGUI = NULL;
GameMain *g_pGameMain = NULL;
ChooseRole* g_pRole = NULL;
int GameStatus = GAME_START_IF;

#pragma region//ȫ�ֱ�������
LPDIRECT3DDEVICE9 g_pDevice;
LPD3DXSPRITE g_pSprite;
HWND g_hWnd;
ID3DXFont *g_pCommFont;
DirectInput* g_pInput;
D3DXMATRIX g_pMax;
ID3DXLine *g_pLine;
POINT gMousePosition;

//��ͼȫ�ֱ���
float mapPosX;
float mapPosY;
float mapWidth;
float mapHight;
#pragma endregion

//��Դ��ʼ��
BOOL cDNF::Init()
{
#pragma region//��ʼ��ȫ�ֱ���
	g_pDevice = m_pDevice;
	g_pSprite = m_pSprite;
	D3DXCreateLine(g_pDevice, &g_pLine);
	g_pLine->SetWidth(1.0f);
	g_pLine->SetAntialias(true);
	g_hWnd = m_hWnd;
	g_pInput = new DirectInput();
	g_pInput->Init(m_hWnd, m_hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mapPosX = 0;
	mapPosY = 0;
	D3DXMatrixTransformation2D(&g_pMax, 0, 0, 0, 0, 0, 0);
#pragma endregion

#pragma region//��������
	if (CREATE_FONT(m_pDevice, 20, 0, false, _T("΢���ź�"), &m_pFont))
		MessageBox(NULL, L"asd", L"asd", NULL);
	g_pCommFont = m_pFont;

#pragma endregion

//�Ҳ����������
CREATE_TEXTUREWH(L"image//createRole//rightbar.png", 321, 510, &m_pTexture);

#pragma region //��ʼ����ʼ�˵�
	g_pStartGUI = new GUIClass(640,480);
	g_pStartGUI->AddBackground(L"image//startmenu//bg",4,L"png",NULL);
	g_pStartGUI->AddButton(BUTTON_ID_1, 0, 240, NULL, NULL, L"image//startmenu//con_new1.png");
	g_pStartGUI->AddButton(BUTTON_ID_2, 0, 290, NULL, NULL, L"image//startmenu//con_over1.png");
	g_pStartGUI->AddButton(BUTTON_ID_3, 0, 340, NULL, NULL, L"image//startmenu//con_stop1.png");
#pragma endregion 
	
#pragma region //��ʼ����Ϸ������
	g_pGameMain = new GameMain();
	if (!g_pGameMain->m_bIsInited)
		g_pGameMain->Init();
#pragma endregion
	/*townInst->Init("data//aierwen.xml");
	roleInst->Init();
	roleInst->CreateRole(townInst->GetRoleX(), townInst->GetRoleY());*/
PlaySound(L"����.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); //ѭ�����ű������� 

#pragma region //��ʼ����ɫѡ��Ƶ��ѡ��
g_pRole = new ChooseRole();
//g_pSelectCN = new SelectChannel();
//g_pSelectCN->Init();
#pragma endregion

	return TRUE;
}

//GUI�ص�����
void GUICallback(int id, int state)
{
	if(state==BUTTON_DOWNUP)
	switch (id)
	{
	case BUTTON_ID_1:
		if(!g_pRole->m_bIsInited)
		{
			g_pRole->CreateRole();
			GameStatus = GAME_ROLE_IF;
		}
		break;
	case BUTTON_ID_2:
		//��������Ϸ��
		break;
	case BUTTON_ID_3:
		//��ѡ�
		break; 
	case BUTTON_ID_4:
		break;
	case BUTTON_ID_5:
		GameStatus = GAME_START_IF;
		break;
	case BUTTON_ID_6:
		break;
	}
}

//��Ϸ��Ⱦ
BOOL cDNF::Render(HWND hWnd)
{
#pragma region //��ʼ����
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
	m_pDevice->BeginScene();                     // ��ʼ����
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
#pragma endregion

//��ȡ����
g_pInput->GetInput();

#pragma region //��ȡ���λ��
	GetCursorPos(&gMousePosition);	
	ScreenToClient(g_hWnd, &gMousePosition);
	m_MouseX = gMousePosition.x;
	m_MouseY = gMousePosition.y;
#pragma endregion

#pragma region //��Ϸ״̬
	switch (GameStatus)
	{
	case GAME_START_IF:
		ProcessGUI(g_pStartGUI, m_MouseX, m_MouseY, GUICallback, true);
		break;
	case GAME_ROLE_IF:
		if (!g_pRole->Render(m_MouseX, m_MouseY, GUICallback))
		{
			GameStatus = GAME_MAIN_IF;
			g_pRole->CleanUp();
			g_pStartGUI->ClearUp();
		}
		break;
	case GAME_CHANNEL_IF:
		/*g_pSelectCN->Render(m_MouseX, m_MouseY, GUICallback);
		g_pStartGUI->ClearUp();*/
		break;
	case GAME_MAIN_IF:	
		g_pGameMain->Render(m_MouseX, m_MouseY);
		break;
	default:
		break;
	}
#pragma endregion

#pragma region //��Ϸ������
	/*townInst->Render();
	roleInst->Render();*/
#pragma endregion

#pragma region//����
	//��������
	//g_pAnimation->Update(x += ROLE_RUN_SPEED, y , dir);
	
	/*g_pAnimation->Render(SKILL_ANI_INTERVAL_TIME);
	g_pAni->Render(SKILL_ANI_INTERVAL_TIME);*/

	//��ɫ����
	
#pragma endregion

//�������
	//���ܲ���
	//g_Skill->Render();

#pragma region//������Ⱦ
	//������Ⱦ
	SPRITE_DRAW(m_pTexture, 820, 0);
	ShowText(hWnd);
	//��������
	m_pSprite->End();
	//g_pLine->Draw(g_pLineArr, 4, D3DCOLOR_XRGB(0, 0, 0));
	//roleInst->RenderLine();
	//town->RenderLine();
	m_pDevice->EndScene();								
	m_pDevice->Present(NULL, NULL, NULL, NULL);  
#pragma endregion
	return TRUE;
}

//��Դ����
BOOL cDNF::CleanUp()
{
	return TRUE;
}

//������ʾ
VOID cDNF::ShowText(HWND hWnd)
{
	static int frameCount = 0;
	static float fps = 0.0;
	static DWORD curTime, LastTime,runTime = GetTickCount()*0.001f;
	curTime = GetTickCount()*0.001f;
	frameCount++;
	if (curTime - LastTime >= 1.0f)
	{
		fps = (float)frameCount / (curTime - LastTime);
		frameCount = 0;
		LastTime = curTime;
	}
	static int n = 0;
	static RECT formatRect;
	/*GetClientRect(hWnd, &formatRect);*/
	SetRect(&formatRect, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	static TCHAR strFileName[100];
	//n = swprintf_s(strFileName, L"%s:%d,yPos:%d,FPS:%.3f\nmapX:%0.3f,mapY:%0.3f\n roleX:%0.3f,roleY:%0.3f",L"xPos", m_MouseX, m_MouseY, fps,mapPosX,mapPosY,roleInst->GetPosX(),roleInst->GetPosY());
	//g_pCommFont->DrawTextW(m_pSprite, strFileName, n, &formatRect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(255, 0, 0));
}

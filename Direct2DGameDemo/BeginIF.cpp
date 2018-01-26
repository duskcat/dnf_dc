#include "BeginIF.h"
EditBoxClass *g_pEditBox = NULL;

LPDIRECT3DTEXTURE9 *m_pTextures;
LPDIRECT3DTEXTURE9 m_pRoleInfo;
LPDIRECT3DTEXTURE9 m_pBg;
bool m_bIsRender;

ChooseRole::ChooseRole()
{
	m_pGui = new GUIClass(640,480);
	m_bIsRender = true;
}

//选择角色
bool ChooseRole::SelectRole()
{
	return false;
}

void CallBack(int id, int state)
{
	if(state == BUTTON_DOWNUP)
	switch (id)
	{
	case 3:
		m_pRoleInfo = m_pTextures[0];
		break;
	case 4:
		m_pRoleInfo = m_pTextures[1];
		break;
	case 5:
		m_pRoleInfo = m_pTextures[2];
		break;
	case 6:
		m_pRoleInfo = m_pTextures[3];
		break;
	case 7:
		m_pRoleInfo = m_pTextures[4];
		break;
	case 8:
		m_pRoleInfo = m_pTextures[5];
		break;
	case 13:
		m_bIsRender = false;
		break;
	default:
		break;
	}
}

//创建角色，初始化
bool ChooseRole::CreateRole()
{
	m_bIsInited = true;
	//m_pGui->AddBackground(L"image//createRole//bg.png", NULL);
	int w, h;
	m_pBg = CreateTexture(L"image//createRole//bg.png", w, h);
	m_pGui->AddButton(BUTTON_ID_1, 20, 300, L"image//createRole//character_btn//0.png", L"image//createRole//character_btn//1.png", L"image//createRole//character_btn//2.png");
	m_pGui->AddButton(BUTTON_ID_10,740, 300, L"image//createRole//character_btn//4.png", L"image//createRole//character_btn//5.png", L"image//createRole//character_btn//6.png");
	m_pGui->AddButton(BUTTON_ID_3, 180, 300, L"image//createRole//character_btn//8.png", L"image//createRole//character_btn//9.png", L"image//createRole//character_btn//10.png");
	m_pGui->AddButton(BUTTON_ID_4, 260, 300, L"image//createRole//character_btn//16.png", L"image//createRole//character_btn//17.png", L"image//createRole//character_btn//18.png");
	m_pGui->AddButton(BUTTON_ID_2, 100, 300, L"image//createRole//character_btn//20.png", L"image//createRole//character_btn//21.png", L"image//createRole//character_btn//22.png");
	m_pGui->AddButton(BUTTON_ID_5, 340, 300, L"image//createRole//character_btn//24.png", L"image//createRole//character_btn//25.png", L"image//createRole//character_btn//26.png");
	m_pGui->AddButton(BUTTON_ID_7, 500, 300, L"image//createRole//character_btn//28.png", L"image//createRole//character_btn//29.png", L"image//createRole//character_btn//30.png");
	m_pGui->AddButton(BUTTON_ID_8, 580, 300, L"image//createRole//character_btn//56.png", L"image//createRole//character_btn//57.png", L"image//createRole//character_btn//58.png");
	m_pGui->AddButton(BUTTON_ID_6, 420, 300, L"image//createRole//character_btn//36.png", L"image//createRole//character_btn//37.png", L"image//createRole//character_btn//38.png");
	m_pGui->AddButton(BUTTON_ID_9, 660, 300, L"image//createRole//character_btn//48.png", L"image//createRole//character_btn//49.png", L"image//createRole//character_btn//50.png");
	m_pGui->AddButton(BUTTON_ID_11, 350, 400, L"image//createRole//2.png", L"image//createRole//3.png", L"image//createRole//4.png");

	m_pTextures = CreateTextures(L"image//createRole//", L"jpg", 6);
	m_pRoleInfo = m_pTextures[1];
	return true;
}

//角色选择界面渲染
bool ChooseRole::Render(int mouseX, int mouseY, void(*funcPtr)(int id, int state))
{
	if (!m_bIsRender)
		return false;
	SPRITE_DRAW(m_pBg, 0, 0);
	SPRITE_DRAW(m_pRoleInfo, 0, 0);
	ProcessGUI(m_pGui, mouseX, mouseY,CallBack);
	return true;
}

void ChooseRole::CleanUp()
{
	if (m_pTextures)
		for (int i = 0; i < 6; i++)
		{
			m_pTextures[i]->Release();
			m_pTextures[i] = NULL;
		}
	Safe_Release(m_pRoleInfo);
	Safe_Release(m_pBg);
	m_pGui->ClearUp();
}

SelectChannel::SelectChannel()
{
	m_pGui = new GUIClass(640, 480);
}

bool SelectChannel::Init()
{
	m_bIsInited = true;
	m_pGui->AddBackground(L"image//selectchannel//channel", 14, L"png", L"sc.png");

	CREATE_TEXTURE(L"image//selectchannel//channel0.png", &m_pBackgroundTex);
	if (!m_pBackgroundTex) return false;

	m_pGui->AddButton(BUTTON_ID_6, 0, 60, 640, 115, NULL, NULL, NULL);

	return true;
}

void SelectChannel::Render(int mouseX, int mouseY, void(*funcPtr)(int id, int status))
{
	static int n = 0;
	SPRITE_DRAW(m_pBackgroundTex, 0, 0);
	if (mouseX > 0 && mouseX < 637 && mouseY>60 && mouseY < 175)
	{
		n = mouseX / 49;
		ProcessGUI(m_pGui, mouseX, mouseY, funcPtr,n+1);
	}
	else
		ProcessGUI(m_pGui, mouseX, mouseY, funcPtr, n+1);
}

void SelectChannel::CleanUp()
{
	if (m_pBackgroundTex)
	{
		Safe_Release(m_pBackgroundTex);
	}
	m_pGui->ClearUp();
}

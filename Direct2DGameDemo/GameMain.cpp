#include "GameMain.h"

int CurrentBg = 0;
GUIClass *m_pGUI = NULL;

bool GameMain::Init()
{
	m_bIsInited = true;
	//初始化role背景
	m_pGUI = new GUIClass(640, 480);
	m_pGUI->AddBackground(L"image//rolebginfo//", 20, L"png",L"sc.png");
	m_pGUI->AddButton(BUTTON_ID_1, 410, 460, L"image//rolebginfo//btn//7.png", L"image//rolebginfo//btn//8.png", L"image//rolebginfo//btn//9.png");
	m_pGUI->AddButton(BUTTON_ID_2, 370, 460, L"image//rolebginfo//btn//3.png", L"image//rolebginfo//btn//4.png", L"image//rolebginfo//btn//5.png");
	//初始化怪物
	return true;
}

void GUICALLBACK(int id,int status)
{
	switch (id)
	{
	case BUTTON_ID_1:
		if (status==BUTTON_DOWNUP)
		{
			CurrentBg++;
			if (CurrentBg == 20)
			{
				townInst->Init("data//siliyaroom.xml");
				roleInst->Init();
				roleInst->CreateRole(townInst->GetRoleX(), townInst->GetRoleY());
				m_pGUI->ClearUp();
			}
		}
		break;
	case BUTTON_ID_2:
		if (status == BUTTON_DOWNUP)
		{
			CurrentBg--;
			if (CurrentBg < 0)
				CurrentBg = 0;
		}
		break;
	default:
		break;
	}
}

void GameMain::Render(int mouseX, int mouseY)
{
	if (CurrentBg <= 19)
		ProcessGUI(m_pGUI, mouseX, mouseY, GUICALLBACK,CurrentBg);
	else
		{
			if (townInst->Render())
			{
				monsterInst->CollisionDetec(roleInst->GetRoleRange());
				monsterInst->Render();
				roleInst->Render();
			}
		}
}

void GameMain::CleanUp()
{
	
}

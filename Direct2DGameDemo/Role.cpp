#include "Role.h"
#include "AnimationMgr.h"
#include "SkillMgr.h"
#include "Town.h"

AnimationMgr *roleAniMgr;

#define MAXWIDTH 820
#define MAXHIGHT 480

Role::Role()
{
	//角色属性初始化
	Hp = 100;
	Mp = 100;
	m_fPosX = 45;
	m_fPosY = 470;
	m_nHight = 135;
	m_nWidth = 90;
	CurRoleState = ROLE_STATE_STAND;
	roleAniMgr = new AnimationMgr();
	SetRect(&m_RoleRange, m_fPosX + mapPosX, m_fPosY + m_nHight, m_fPosX + m_nWidth + mapPosX, m_fPosY);
	m_pGuiOption = new GUIClass(800, 600);
}

Role::~Role()
{

}

Role * Role::Instance()
{
	static Role role; 
	return &role;
}

bool Role::Init()
{
	m_bIsRender = true;
	m_pBottomBar=CreateTexture(L"image//role//bar1.png", m_nWidthBar, m_nHightBar);
	m_pGuiOption->AddButton(BUTTON_ID_1, 456, 460, L"image//gui//77.png", L"image//gui//78.png", L"image//gui//79.png");
	return true;
}

void CallBackOption(int id, int state)
{
	if (state != BUTTON_DOWNUP)
		return;
	switch (id)
	{
	case BUTTON_ID_1:
		townInst->CleanUp();
		monsterInst->CleanUp();
		townInst->Init("data//aierwen.xml");
		roleInst->Position(600, 420);
		mapPosX = 3200;

		break;
	default:
		break;
	}
}

void Role::Render()
{
	if (!m_bIsRender)
		return;
	//更新角色状态
	Update();
	//角色动作绘制
	m_pAniCurTex->Update(m_fPosX, m_fPosY, m_dDir);
	m_pAniCurTex->Render();
	
	//sprite初始矩阵
	g_pSprite->SetTransform(&g_pMax);
	m_bIsPlayed = m_pAniCurTex->IsPlayed();
	m_pTitlel->Update(m_fPosX, m_fPosY - 135, m_dDir);
	m_pTitlel->Render();
	SPRITE_DRAW(m_pName, m_fPosX-15, m_fPosY - 190);
	if (m_bInfo)
		SPRITE_DRAW(m_pInfo, 300, 50);

	//角色技能绘制
	skillMgrInst->Update(m_dDir);
	skillMgrInst->RenderSkill();
	/*if (m_bIsCollision)
		MessageBox(NULL, L"asd", L"asdf", NULL);*/
	//绘制底部角色栏（技能，物品，菜单等）
	static RECT rect;
	SetRect(&rect, 0, 8, 820, 482);
	SPRITE_DRAWEX(m_pBottomBar,&rect, 0, 30);
	ProcessGUI(m_pGuiOption, gMousePosition.x, gMousePosition.y, CallBackOption);
}

void Role::SetLineArr()
{
	m_pLineArr = new D3DXVECTOR2[5];
}

void Role::RenderLine()
{
	g_pLine->Draw(m_pLineArr, 5, D3DCOLOR_XRGB(255, 0, 0));
}

void Role::CleanUp()
{

}

void Role::Update()
{
	//判断角色的行走条件
	static string aniName="stand";

	if(m_bIsPlayed)								//技能使用完切换状态
		CurRoleState = ROLE_STATE_STAND;
	if(CurRoleState==ROLE_STATE_WALK)			//行走状态切换为站立姿态
		CurRoleState = ROLE_STATE_STAND;
	curTime = GetTickCount();

	if (DIKEYDOWN(DIK_RIGHT))
	{
		if (m_fPosX <= MAXWIDTH/2 && mapPosX < mapWidth - MAXWIDTH)
			m_bIsMoved = true;
		else if (mapPosX >= mapWidth - MAXWIDTH)
			m_bIsMoved = true;
		else
			m_bIsMoved = false;
		if (m_bIsMoved)
			m_fPosX += ROLE_SPEED;
		else
			mapPosX += ROLE_SPEED;
		if (m_fPosX >= MAXWIDTH - m_nWidth / 2)
		{
			m_fPosX = MAXWIDTH - m_nWidth / 2;
		}
		CurRoleState = ROLE_STATE_WALK;
		m_dDir = Dir_Right;
	}
	if (DIKEYDOWN(DIK_LEFT))
	{
		if (m_fPosX <= 0)
			m_bIsMoved = false;
		else if (m_fPosX >= MAXWIDTH/2 && mapPosX >= mapWidth - MAXWIDTH-1)
			m_bIsMoved = true;
		if (m_fPosX <= MAXWIDTH/2+1 && mapPosX <= mapWidth - MAXWIDTH+2)
			m_bIsMoved = false;
		if (m_fPosX <= MAXWIDTH/2+1 && mapPosX <= 0)
			m_bIsMoved = true;
		if (m_bIsMoved)
			m_fPosX -= ROLE_SPEED;
		else
			mapPosX -= ROLE_SPEED;
		if (m_fPosX <= MIN_POS_X)
			m_fPosX = MIN_POS_X;
		CurRoleState = ROLE_STATE_WALK;
		m_dDir = Dir_Left;

	}
	if (DIKEYDOWN(DIK_UP))
	{
		m_fPosY -= ROLE_RUN_SPEED;
		if (m_fPosY <= MIN_POS_Y)
			m_fPosY = MIN_POS_Y;
		CurRoleState = ROLE_STATE_WALK;
	}
	if (DIKEYDOWN(DIK_DOWN))
		{
			m_fPosY += ROLE_RUN_SPEED;
			if (m_fPosY >= MAX_POS_Y)
				m_fPosY = MAX_POS_Y;
			CurRoleState = ROLE_STATE_WALK;
		}
		
	if (DIKEYDOWN(DIK_X))
	{
		CurRoleState = ROLE_STATE_ATTACK;
	}
	if (DIKEYDOWN(DIK_LSHIFT))
	{
		CurRoleState = ROLE_STATE_SKILL;
		skillMgrInst->AddSkill(new Skill(L"image//skill//blood//", L"png", 35, m_fPosX, m_fPosY,D3DXVECTOR2(0.8f,0.8f),new Animation(L"image//skill//blood//ani",L"png",18,m_fPosX,m_fPosY,100,false)));
	}
	if (DIKEYDOWN(DIK_A))
	{
		aniName = "hadouken";
		CurRoleState = ROLE_STATE_SKILL;
		skillMgrInst->AddSkill(new Skill(L"image//skill//firefront//", L"png", 7, m_fPosX, m_fPosY, D3DXVECTOR2(1.0f, 1.0f)));
	}
	if (DIKEYDOWN(DIK_S))
	{
		aniName = "tuci";
		CurRoleState = ROLE_STATE_SKILL;
		skillMgrInst->AddSkill(new Skill(L"image//skill//tuci//", L"png", 10, m_fPosX, m_fPosY, D3DXVECTOR2(0.4f, 0.4f)));
	}

	if (DIKEYDOWN(DIK_I))
	{
		if (m_bInfo == false)
			m_bInfo = true;
		else
			m_bInfo = false;
	}

	mapPosY = m_fPosY;
	//	if (m_bIsCollision&&mCollisionType == COLLISION_TYPE_MONSTER)
	//		m_bIsHurt = true;
	//	else
	//		m_bIsHurt = false;
	//if(m_bIsHurt)
	//	CurRoleState = ROLE_STATE_HURT;
	switch (CurRoleState)
	{
	case ROLE_STATE_STAND:
		{aniName = "stand"; m_bIsAttack = false; }
		break;
	case ROLE_STATE_WALK:
		{aniName = "walk"; m_bIsAttack = false; }
		break;
	case ROLE_STATE_RUN:
		{aniName = "run"; m_bIsAttack = false; }
		break;
	case ROLE_STATE_ATTACK:
		{aniName = "sknormalattack"; m_bIsAttack = true; }
		break;
	/*case ROLE_STATE_HURT:
		{aniName = "hurt"; m_bIsAttack = false; }
		break;*/
	case ROLE_STATE_SKILL:
		m_bIsAttack = true;
		break;
	default:
		break;
	}

	m_pAniCurTex = roleAniMgr->GetAnimation(aniName);
	m_nWidth = m_pAniCurTex->GetWidth();
	m_nHight = m_pAniCurTex->GetHight();

	//根据方向设置当前sprite的矩阵
	switch (m_dDir)
	{
	case Dir_Left:
	{
		D3DXMatrixTransformation2D(&m_pMax, &D3DXVECTOR2(m_fPosX + 45, m_fPosY), 0, &D3DXVECTOR2(-1, 1), 0, 0, 0); 
		SetRect(&m_RoleRange, m_fPosX - m_pAniCurTex->GetWidth() / 2, m_fPosY - m_nHight, m_fPosX + m_nWidth, m_fPosY);

		if(CurRoleState==ROLE_STATE_STAND||CurRoleState==ROLE_STATE_WALK)
		{
			SetRect(&m_RoleRange, m_fPosX + m_nWidth / 4, m_fPosY - m_nHight, m_fPosX + m_nWidth, m_fPosY);
		}
	}
		break;
	case Dir_Up:
		break;
	case Dir_Right:
	{
		D3DXMatrixTransformation2D(&m_pMax, 0, 0, 0, 0, 0, 0);
		static RECT rect;
		//SetRect(&rect, m_fPosX, m_fPosY-m_nHight, m_fPosX + m_nWidth, m_fPosY);
		//static TCHAR temp[200];
		//static int n = 0;
		//n = swprintf_s(temp, L"%0.3f\n%0.3f\n%03.f\n%0.3f",m_fPosX,m_fPosY-m_nHight,m_fPosX+m_nWidth,m_fPosY);
		//g_pCommFont->DrawTextW(g_pSprite, temp, n, &rect, DT_TOP | DT_RIGHT, D3DCOLOR_XRGB(255, 0, 0));

		/*m_pLineArr[0].x = m_fPosX;
		m_pLineArr[0].y = m_fPosY - m_pAniCurTex->GetHight();
		m_pLineArr[1].x = m_fPosX + m_pAniCurTex->GetWidth()/4*3;
		m_pLineArr[1].y = m_fPosY - m_pAniCurTex->GetHight();
		m_pLineArr[2].x = m_fPosX + m_nWidth/4*3;
		m_pLineArr[2].y = m_fPosY;
		m_pLineArr[3].x = m_fPosX;
		m_pLineArr[3].y = m_fPosY;
		m_pLineArr[4].x = m_fPosX;
		m_pLineArr[4].y = m_fPosY - m_pAniCurTex->GetHight();*/
		SetRect(&m_RoleRange, m_fPosX, m_fPosY - m_nHight, m_fPosX + m_nWidth, m_fPosY);
		if (CurRoleState == ROLE_STATE_STAND || CurRoleState == ROLE_STATE_WALK)
			SetRect(&m_RoleRange, m_fPosX, m_fPosY - m_nHight, m_fPosX + m_nWidth / 4 * 3, m_fPosY);
	}
		break;
	case Dir_Down:
		break;
	default:
		break;
	}
	g_pSprite->SetTransform(&m_pMax);
}

void Role::Hurt(float dmg)
{
	m_fHurtDamage = dmg; 
	Hp -= dmg; 
	string hp = to_string(Hp);
	//MessageBox(NULL, CharToWchar(to_string(dmg).c_str()), CharToWchar(hp.c_str()), NULL);
}

bool Role::CreateRole(float x, float y)
{
	m_fPosX = x;
	m_fPosY = y;

	roleAniMgr->CreateAnimationType("stand", new Animation(L"image//role//swordman//stand", L"png", 4, m_fPosX, m_fPosY,0, true));
	roleAniMgr->CreateAnimationType("walk", new Animation(L"image//role//swordman//walk", L"png", 8, m_fPosX, m_fPosY, 0, true));
	roleAniMgr->CreateAnimationType("run", new Animation(L"image//role//swordman//run", L"png", 8, m_fPosX, m_fPosY, 0, true));
	roleAniMgr->CreateAnimationType("attack", new Animation(L"image//role//swordman//attank", L"png", 6, m_fPosX, m_fPosY, 0, true));
	roleAniMgr->CreateAnimationType("sknormalattack", new Animation(L"image//role//swordman//", L"png", 20, m_fPosX, m_fPosY, 35, true));
	roleAniMgr->CreateAnimationType("hadouken", new Animation(L"image//role//swordman//fire", L"png", 9, m_fPosX, m_fPosY, 100, true));
	roleAniMgr->CreateAnimationType("tuci", new Animation(L"image//role//swordman//tuci", L"png", 10, m_fPosX, m_fPosY, 80, true));
	roleAniMgr->CreateAnimationType("hurt", new Animation(L"image//role//swordman//hurt", L"png", 4, m_fPosX, m_fPosY, 160, true));
	m_pAniCurTex= roleAniMgr->GetAnimation("stand");
	//m_pAniEquip = new Animation(L"image//role//weapeon//", L"png", 20, m_fPosX + 40, m_fPosY - 50, 50, true);
	//SetLineArr();
	m_pTitlel = new Animation(L"image//animation//lastboss//", L"png", 152, m_fPosX+30, m_fPosY-200,100, true);
	int w, h;
	m_pName = CreateTexture(L"image//role//0.png", w, h);
	m_pInfo = CreateTexture(L"image//createRole//info.png", w, h);
	//roleAniMgr->CreateAnimationType("hadouken", new Animation(L"image//role//swordman//fire", L"png", 9, m_fPosX, m_fPosY, 60, true));
	//g_pSkillMgr->CreateSkill("blood", new Skill(L"image//skill//blood//", L"png", 35, m_fPosX, m_fPosY));
	return true;
}

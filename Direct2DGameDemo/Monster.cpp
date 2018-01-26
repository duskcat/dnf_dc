#include "Monster.h"
#include "Animation.h"
#include <math.h>

AnimationMgr *msAniMgr=NULL;
Animation* msSkill = NULL;
#define MONSTER_WALK_SPEED 0.1f

Monster::Monster()
{
	m_pStateMachine = new StateMachine<Monster>(this);
	m_pStateMachine->SetCurrentState(State_Walk::Instance());
	//m_pStateMachine->SetGlobleState(State_GetHurt::Instance());
}
//创建怪物，位置，方向等随机
void Monster::Init(int x, int y,LPCWSTR texHead)
{
	m_fPosX = x;
	m_fPosY = y;
	msAniMgr = new AnimationMgr();
	msAniMgr->CreateAnimationType("skill", new Animation(L"image//monster//serred//skill",L"png",11, m_fPosX, m_fPosY, 150, true));
	msAniMgr->CreateAnimationType("walk", new Animation(L"image//monster//serred//wlk",L"png",10, m_fPosX, m_fPosY,150,true));
	msAniMgr->CreateAnimationType("hurt", new Animation(L"image//monster//serred//hurt",L"png",3, m_fPosX, m_fPosY, 300, true));
	msAniMgr->CreateAnimationType("attack", new Animation(L"image//monster//serred//attack",L"png",5, m_fPosX, m_fPosY,150,true));
	msSkill = new Animation(L"image\\monster\\serred\\skill\\", L"png", 9, OffSetX(), OffSetY(), 80, true);
	HP = 200;
	MaxHp = 200;
	MP = 100;
	int w, h;
	m_pTexHead = CreateTexture(texHead, w, h);
	MonsterAni = msAniMgr->GetAnimation("walk");
}

void Monster::Render()
{
	/*MonsterAni->UpdateOdd(m_fPosX - mapPosX, m_fPosY, mDir);
	MonsterAni->Render();*/
	MonsterAni->Update(m_fPosX - mapPosX, m_fPosY, mDir);
	MonsterAni->Render();
	SetRect(&monsterRange, OffSetX(), m_fPosY - m_nHight, OffSetX() + m_nWidth, m_fPosY);
	g_pSprite->SetTransform(&g_pMax);
}

void Monster::RenderStateBar()
{
	int w, h;
	static LPDIRECT3DTEXTURE9	m_pTexHp = CreateTexture(L"image//monster//93.png", w, h);
	static LPDIRECT3DTEXTURE9   m_pTexFrame = CreateTexture(L"image//monster//106.png", w, h);
	static RECT rect;
	SetRect(&rect, 0, 0, (float)HP / MaxHp * 594, 9);
	SPRITE_DRAW(m_pTexFrame, 0, 0);
	SPRITE_DRAW(m_pTexHead, 4, 3);
	SPRITE_DRAWEX(m_pTexHp, &rect, 33, 20, );
}

void Monster::Walk()
{
	static D3DXMATRIX m_Matrix;
	curTime = GetTickCount();
	//间隔一段时间随机改变方向
	if (curTime - lastTime >= rand() % 4000 + 1500)
	{
		curDir = (rand() % 4);
		lastTime = curTime;
	}
	switch (curDir)
	{
		case 0:
		{
			mDir = Dir_Left;
			D3DXMatrixTransformation2D(&m_Matrix, &D3DXVECTOR2(OffSetX() + MonsterAni->GetWidth() / 2, m_fPosY), 0, &D3DXVECTOR2(-1, 1), 0, 0, 0);
			g_pSprite->SetTransform(&m_Matrix);
			m_fPosX -= MONSTER_WALK_SPEED;
			if (m_fPosX <= MIN_POS_X)
				m_fPosX = MIN_POS_X;
		}
		break;

		case 1:
		{
			mDir = Dir_Up;
			m_fPosY -= MONSTER_WALK_SPEED;
			if (m_fPosY <= MIN_POS_Y)
				m_fPosY = MIN_POS_Y;
		}
		break;
		case 2:
		{
			mDir = Dir_Right;
			D3DXMatrixTransformation2D(&m_Matrix, 0, 0, 0, 0, 0, 0);
			g_pSprite->SetTransform(&m_Matrix);
			m_fPosX += MONSTER_WALK_SPEED;
			if (m_fPosX >= mapWidth)
				m_fPosX = mapWidth;
		}
		break;
		case 3:
		{
			mDir = Dir_Down;
			m_fPosY += MONSTER_WALK_SPEED;
			if (m_fPosY >= MAX_POS_Y)
				m_fPosY = MAX_POS_Y;
		}
		break;
		default:
			break;
	}
}

void Monster::Attack()
{
	static D3DXMATRIX m_Matrix;
	switch (mDir)
	{
	case Dir_Left:
		D3DXMatrixTransformation2D(&m_Matrix, &D3DXVECTOR2(OffSetX() + MonsterAni->GetWidth() / 2, m_fPosY), 0, &D3DXVECTOR2(-1, 1), 0, 0, 0);
		g_pSprite->SetTransform(&m_Matrix);
		break;
	case Dir_Up:
		break;
	case Dir_Right:
		D3DXMatrixTransformation2D(&m_Matrix, 0, 0, 0, 0, 0, 0);
		g_pSprite->SetTransform(&m_Matrix);
		break;
	case Dir_Down:
		break;
	default:
		break;
	}
	SkillOffSetPos();
	SetRect(&m_rMonsterSkillRegion, m_fSkillOffX, m_fPosY, m_fSkillOffX + msSkill->GetWidth(), m_fPosY + msSkill->GetHight());
	msSkill->Update(m_fSkillOffX,m_fPosY,mDir);
	msSkill->Render();
}

void Monster::Runaway()
{
}

void Monster::Trace()
{
	static D3DXMATRIX m_Matrix;
	if (roleInst->GetPosX() < OffSetX())
	{
		mDir = Dir_Left;
		D3DXMatrixTransformation2D(&m_Matrix, &D3DXVECTOR2(OffSetX() + MonsterAni->GetWidth() / 2, m_fPosY), 0, &D3DXVECTOR2(-1, 1), 0, 0, 0);
		g_pSprite->SetTransform(&m_Matrix);
		m_fPosX -= MONSTER_WALK_SPEED;
		if (m_fPosY > roleInst->GetPosY())
			m_fPosY -= MONSTER_WALK_SPEED;
		else
			m_fPosY += MONSTER_WALK_SPEED;
	}
	else
	{
		mDir = Dir_Right;
		D3DXMatrixTransformation2D(&m_Matrix, 0, 0, 0, 0, 0, 0);
		m_fPosX += MONSTER_WALK_SPEED;
		g_pSprite->SetTransform(&m_Matrix);
		if (m_fPosY > roleInst->GetPosY())
			m_fPosY -= MONSTER_WALK_SPEED;
		else
			m_fPosY += MONSTER_WALK_SPEED;
	}
}

void Monster::Dead()
{
	if (HP <= 0)
		m_bIsDead = true;
}

void Monster::SetCurAni(string name)
{
	MonsterAni = msAniMgr->GetAnimation(name);
}

void Monster::SkillOffSetPos()
{
	m_fSkillOffX = m_fPosX - mapPosX + m_nWidth;
	m_fSkillOffY = m_fPosY;
}

void Monster::Update()
{
	m_nWidth = MonsterAni->GetWidth();
	m_nHight = MonsterAni->GetHight();
	//设置警戒范围
	SetRect(&m_rWarningRegion, OffSetX() - 100, OffSetY() + m_nHight - 100, OffSetX() + m_nWidth + 100, OffSetY() + 100);
	SetRect(&m_rAttackRegion, OffSetX() - 50, OffSetY() + m_nHight - 50, OffSetX() + m_nWidth + 50, OffSetY() + 50);
	m_pStateMachine->Update();
}

void Monster::CleanUp()
{
	MonsterAni->CleanUp();
}

//walk->trace
void State_Walk::Execute(Monster *monster)
{
	static RECT rect;
	//角色是否在怪物警戒范围内(true:开始追击)
	if (IntersectRect(&rect, &roleInst->GetRoleRange(), &monster->WarningRegion()))
		monster->GetFSM()->ChangeState(State_Trace::Instance());
	else if (monster->GetCollision() && roleInst->IsAttack())
		monster->GetFSM()->ChangeState(State_GetHurt::Instance());
	else
		monster->Walk();
}

void State_Walk::Exit(Monster * monster)
{
	/*int i = rand() % 4;
	switch (i)
	{
	case 0:
		monster->GetFSM()->ChangeState(State_Attack::Instance());
		break;
	case 1:
		monster->GetFSM()->ChangeState(State_Walk::Instance());
		break;
	case 2:
		monster->GetFSM()->ChangeState(State_Runaway::Instance());
		break;
	default:
		break;
	}*/
}

void State_Walk::Enter(Monster * monster)
{
	monster->SetCurAni("walk");
}

//attack->hurt->runaway
void State_Attack::Execute(Monster *monster)
{
	static RECT rect;
	if (monster->GetHp() < 20 && monster->GetHp() > 0)
		monster->GetFSM()->ChangeState(State_Runaway::Instance());
	/*else if (monster->GetHp() <= 0)
		monster->GetFSM()->ChangeState(State_Dead::Instance());*/
	else if (monster->GetCollision()&&roleInst->IsAttack())
		monster->GetFSM()->ChangeState(State_GetHurt::Instance());
	else if (!IntersectRect(&rect, &roleInst->GetRoleRange(), &monster->WarningRegion()))
	{
		monster->GetFSM()->ChangeState(State_Walk::Instance());
	}
	else
		monster->Attack();
}

void State_Attack::Enter(Monster * monster)
{
	monster->SetCurAni("attack");
}

//runaway->walk->dead
void State_Runaway::Execute(Monster *monster)
{
	if (monster->OffSetX() - roleInst->GetPosX() > 100)
		monster->GetFSM()->ChangeState(State_Walk::Instance());
	//else
	//	monster->walk();
}

//dead
void State_Dead::Execute(Monster *monster)
{
	if (monster->IsDead())
		;
	//else
	//	monster->walk();
}

void State_GetHurt::Execute(Monster * monster)
{
	monster->Dead();
	if (!roleInst->IsAttack())
		monster->GetFSM()->ChangeState(State_Attack::Instance());
}

void State_GetHurt::Enter(Monster * monster)
{
	//monster->GetHurt(roleInst->Damage());
	monster->GetHurt(40);
	monster->SetCurAni("hurt");
}

void State_Trace::Execute(Monster * monster)
{
	static RECT rect;
	if (!IntersectRect(&rect, &roleInst->GetRoleRange(), &monster->WarningRegion()))
	{
		monster->GetFSM()->ChangeState(State_Walk::Instance());
	}
	//else if (IntersectRect(&rect, &roleInst->GetRoleRange(), &monster->AttackRegion()))
	//{
	//	monster->GetFSM()->ChangeState(State_Attack::Instance());
	//}

	else if (fabs(roleInst->GetPosX() - monster->OffSetX()) <= 100)
	{
		monster->GetFSM()->ChangeState(State_Attack::Instance());
	}
	else
		monster->Trace();
}

void State_Trace::Enter(Monster * monster)
{
	monster->SetCurAni("walk");
}

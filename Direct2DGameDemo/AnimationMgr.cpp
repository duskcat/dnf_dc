#include "AnimationMgr.h"

BOOL AnimationMgr::CreateAnimationType(string type, Animation *ani)
{
	if (!ani)
		return FALSE;
	m_mAniType[type] = ani;
	m_lAnimations.push_back(ani);
	return true;
}

bool AnimationMgr::AddAnimation(Animation *ani)
{
	m_lAnimations.push_back(ani);
	return true;
}

void AnimationMgr::Render()
{
	if (m_lAnimations.empty())
		return;
	static list<Animation*>::iterator ite;
	for (ite=m_lAnimations.begin();ite!=m_lAnimations.end();ite++)
	{
		(*ite)->RenderScaling();
	}
}

Animation * AnimationMgr::GetAnimation(string name)
{
	return m_mAniType[name];
}

void AnimationMgr::CleanUp()
{
	if (m_lAnimations.empty())
		return;
	static list<Animation*>::iterator ite,cur;
	for (ite = m_lAnimations.begin(); ite != m_lAnimations.end();)
	{
		cur = ite++;
		(*cur)->CleanUp();
		m_lAnimations.erase(cur);
	}
}

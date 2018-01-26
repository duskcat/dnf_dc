#pragma once

#include "stdafx.h"
#include "Animation.h"

class AnimationMgr
{
protected:
	typedef map<string, Animation*> AniType;
	AniType m_mAniType;
	typedef list<Animation*> AnimationList;
	AnimationList m_lAnimations;
public:
	AnimationMgr() {};
	BOOL CreateAnimationType(string type, Animation *ani);
	bool AddAnimation(Animation *ani);
	void Render();
	Animation *GetAnimation(string name);
	Animation* TraverseMonster() {};
	AnimationList GetMonsterlist() { return m_lAnimations; };
	void CleanUp();
};
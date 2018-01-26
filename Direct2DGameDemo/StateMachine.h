#pragma once
#include "state.h"

template<class entity_type>
class StateMachine
{
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState=NULL;
	State<entity_type>* m_pPreviousState=NULL;
	State<entity_type>* m_pGlobleState=NULL;
public:
	StateMachine(entity_type* owner) :m_pOwner(owner) {}
	void Update()const
	{
		if (m_pGlobleState) m_pGlobleState->Execute(m_pOwner);
		if (m_pCurrentState) m_pCurrentState->Execute(m_pOwner);
	}
	void ChangeState(State<entity_type>* pNewState)
	{
		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);
		m_pCurrentState = pNewState;
		m_pCurrentState->Enter(m_pOwner);
	}
	void RevertToPreviousState() { m_pCurrentState = m_pPreviousState; }
	void SetCurrentState(State<entity_type>* s) { m_pCurrentState = s; }
	void SetPreviousState(State<entity_type>* s) { m_pPreviousState = s; }
	void SetGlobleState(State<entity_type>* s) { m_pGlobleState = s; }
	State<entity_type>* CurrentState() { return m_pCurrentState; }
	State<entity_type>* PreviousState() { return m_pPreviousState; }
	State<entity_type>* GlobleState() { return m_pGlobleState; }
};

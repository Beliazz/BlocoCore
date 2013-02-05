#include "BlocoCore.h"


IEventManager BLOCOCORE_API* g_pEventMgr = NULL;
IEventManager BLOCOCORE_API * IEventManager::Get()
{
	return g_pEventMgr;
}

 IEventManager::IEventManager(char const * const pName,bool setAsGlobal )
{
	if ( setAsGlobal )
		g_pEventMgr = this;
}

 IEventManager::~IEventManager()
{
	if ( g_pEventMgr == this )
		g_pEventMgr = NULL;
}


// lastly, some macros that make it less difficult to safely use
// a possibly not-ready system ...
bool BLOCOCORE_API  safeAddListener( EventListenerPtr const & inHandler, EventType const & inType )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VAddListener( inHandler, inType );
}
bool BLOCOCORE_API  safeDelListener( EventListenerPtr const & inHandler, EventType const & inType )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VDelListener( inHandler, inType );
}
bool BLOCOCORE_API  safeTriggerEvent( IEventData const & inEvent )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VTrigger( inEvent );
}
bool BLOCOCORE_API  safeQueEvent( IEventDataPtr const & inEvent )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VQueueEvent( inEvent );
}
bool BLOCOCORE_API  safeAbortEvent( EventType const & inType, bool allOfType /*= false*/ )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VAbortEvent( inType, allOfType );
}
bool BLOCOCORE_API  safeTickEventManager( unsigned long maxMillis /*= kINFINITE*/ )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VTick( maxMillis );
}
bool BLOCOCORE_API  safeValidateEventType( EventType const & inType )
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->VValidateType( inType );
}
void BLOCOCORE_API  safeSetDebugView(DebugView* pDebugView)
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->SetDebugView( pDebugView );
}
void BLOCOCORE_API  safeRemoveDebugView()
{
	assert(IEventManager::Get() && _T("No event manager!"));
	return IEventManager::Get()->RemoveDebugView();
}







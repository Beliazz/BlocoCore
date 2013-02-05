#include "BlocoCore.h"

LuaStateManager BLOCOCORE_API* g_pAppLuaStateManager = NULL;


// LuaStateManager::LuaStateManager				- Chapter 11, page 317

 LuaStateManager::LuaStateManager( void )
: m_GlobalState( true )	// 'true' Indicates to init the standard Lua library 
						// for dofile, etc.
{
	//Create our metatable...
	m_MetaTable = m_GlobalState->GetGlobals().CreateTable( "LuaStateManagerMetaTable" );
	m_MetaTable.SetObject( "__index", m_MetaTable );

	// Here we register two functions to make them accessible to script.
	m_MetaTable.RegisterObjectDirect( "DoFile", (LuaStateManager *)0, &LuaStateManager::DoFile );
	m_MetaTable.RegisterObjectDirect( "PrintDebugMessage", (LuaStateManager *)0, &LuaStateManager::PrintDebugMessage );

	LuaObject luaStateManObj = m_GlobalState->BoxPointer( this );
	luaStateManObj.SetMetaTable( m_MetaTable );

	// And here we expose the metatable as a named entity.
	m_GlobalState->GetGlobals().SetObject( "LuaStateManager", luaStateManObj );
}

 LuaStateManager::~LuaStateManager()
{
}


// LuaStateManager::Init				- Chapter 11, page 318

bool LuaStateManager::Init( char const * const pInitFileName )
{
	// Create our global actor table.
	// This table will hold context for all actors created in the game world.
	LuaObject globals = m_GlobalState->GetGlobals();
	LuaObject actorTable = globals.CreateTable( "ActorList" );

	return DoFile( pInitFileName );
}

bool LuaStateManager::DoFile(char const * const pFileName)
{
	return ExecuteFile(m_GlobalState,pFileName);
}

bool LuaStateManager::ExecuteFile(LuaStateOwner & luaState, char const * const pFileName)
{
	const int retVal = luaState->DoFile(pFileName);
	const bool bSucceeded = ( 0 == retVal );
	assert( bSucceeded && "Unable to execute Lua script file!" );
	return bSucceeded;
}

int LuaStateManager::ExecuteString( char const * const pStringToExecute )
{
	const int retVal = m_GlobalState->DoString( pStringToExecute );

	return retVal;
}

LuaObject LuaStateManager::GetGlobalActorTable( void )
{
	return m_GlobalState->GetGlobal( "ActorList" );
}

void LuaStateManager::IdentifyLuaObjectType( LuaObject & objToTest )
{
	assert( !objToTest.IsNil() && "Nil!" );
	assert( !objToTest.IsBoolean() && "Boolean!" );
	assert( !objToTest.IsCFunction() && "C-Function!" );
	assert( !objToTest.IsFunction() && "Function!" );
	assert( !objToTest.IsInteger() && "Integer!" );
	assert( !objToTest.IsLightUserData() && "Light User Data!" );
	assert( !objToTest.IsNone() && "None!" );
	assert( !objToTest.IsNumber() && "Number!" );
	assert( !objToTest.IsString() && "String!" );
	assert( !objToTest.IsTable() && "Table!" );
	assert( !objToTest.IsUserData() && "User Data!" );
	assert( !objToTest.IsWString() && "Wide String!" );
	assert( 0 && "UNKNOWN!" );
}

void LuaStateManager::PrintDebugMessage( LuaObject debugObject )
{
	LuaObject stringObj;
	const char * pFinalStr = debugObject.ToString();

	//Generate an event.
	//const EvtData_Debug_String debugEvent( ( NULL == pFinalStr ) ? "INVALID!" : pFinalStr, EvtData_Debug_String::kDST_ScriptMsg );
	//safeTriggerEvent( debugEvent );
}

void LuaStateManager::RegisterFunction( const char* funcName, lua_CFunction function, int nupvalues /*= 0*/ )
{
	m_GlobalState->GetGlobals().Register(funcName, function, nupvalues);
}

void LuaStateManager::RegisterFunction( const char* funcName, int (*function)(LuaState*), int nupvalues /*= 0*/ )
{
	m_GlobalState->GetGlobals().Register(funcName, function, nupvalues);
}

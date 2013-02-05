#ifndef LuaStateManager_h__
#define LuaStateManager_h__

#include "BlocoCore.h" 


// class LuaStateManager
class BLOCOCORE_API LuaStateManager
{
public:
	LuaStateManager(void);

	~LuaStateManager();

	// I hate two-stage initialization, but due to dependencies, 
	// we have to have an Init called after the Event Manager gets built.
	// This function runs the init script.
	bool Init( char const * const pInitFileName );

	// Returns the main state used by the entire game.  
	// Other implementations may use multiple LuaStates, but for our purposes
	// a single state will do just fine.
	LuaStateOwner & GetGlobalState(void)  { return m_GlobalState; }

	// Executes a Lua script file.
	bool DoFile(char const * const pFileName);
	static bool ExecuteFile(LuaStateOwner & luaState, char const * const pFileName);

	// Executes an arbitrary Lua command.
	int ExecuteString( char const * const pStringToExecute );

	// Debug function for determining an object's type.
	static void IdentifyLuaObjectType( LuaObject & objToTest );

	// The table where all actor context and data is stored
	// for script accessability.
	LuaObject GetGlobalActorTable( void );

	// register funtion
	void RegisterFunction(const char* funcName, lua_CFunction function, int nupvalues = 0);
	void RegisterFunction(const char* funcName, int (*func)(LuaState*),  int nupvalues = 0);

private:
	// Debug print string function (callable from script).
	void PrintDebugMessage( LuaObject debugObject );

	// Our global LuaState.
	LuaStateOwner m_GlobalState;

	// Our portal to the outside world.
	LuaObject m_MetaTable;
};

extern LuaStateManager BLOCOCORE_API* g_pAppLuaStateManager;

#endif // LuaStateManager_h__

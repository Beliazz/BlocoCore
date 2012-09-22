// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifndef BlocoCore_H__
#define BlocoCore_H__

#ifdef BLOCOCORE_EXPORTS
#define BLOCOCORE_API __declspec(dllexport)
#else
#define BLOCOCORE_API __declspec(dllimport)
#endif


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK new
#endif


#pragma warning (disable: 4251)
#pragma warning (disable: 4996)

#define WIN32_LEAN_AND_MEAN   
#include <Windows.h> 

struct AppMsg
{
	HWND m_hWnd;
	UINT m_uMsg;
	WPARAM m_wParam;
	LPARAM m_lParam;
};

#define kpWildcardEventType "*"

// General
#include <stdlib.h>
#include <malloc.h>
#include <memory>
#include <wchar.h>
#include <tchar.h>
#include <assert.h>
#include <cassert>
#include <crtdbg.h>
#include <mmsystem.h>
#include <direct.h>
#include <shlobj.h>
#include <strstream>
#include <functional>
#include <time.h>
#include <WinSock2.h>
#include <io.h>
#include <sys/stat.h>

#include <locale>
#include <iostream>
#include <sstream>

// STL
#include <string>
#include <list>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iterator>
#include <fstream>


// DirectX
#include "d3dx9.h"
#pragma comment(lib, "d3dx9.lib")

// math
#include <xnamath.h>

// lua
#include <LuaPlus/LuaLink.h>
#include <LuaPlus/LuaPlus.h>
#include <LuaPlus/LuaObject.h>
#pragma comment(lib, "luaplus51-1201_debug.lib")

using namespace LuaPlus;
using namespace std;

#include "Vec.h"
#include "Geometry.h"

#include "Templates.h"
#include "Interfaces.h"

#include "HashedString.h"
#include "EventManager.h"
#include "LuaStateManager.h"
#include "CProcess.h"
#include "CProcessManager.h"

#endif

// TODO: reference additional headers your program requires here

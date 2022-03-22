// ml_fixes.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "explorer.h"
#include "lua.hpp"

#define DLLEXPORT __declspec(dllexport)

extern "C" DLLEXPORT int add_ml_fixes(lua_State* L) {
	lua_getglobal(L, "os");

	if (lua_isnil(L, -1))
		return 0;

	lua_pushstring(L, "listall");
	lua_pushcfunction(L, listDirectory);
	lua_rawset(L, -3);
	lua_pushstring(L, "listfiles");
	lua_pushcfunction(L, listDirectoryFiles);
	lua_rawset(L, -3);
	lua_pushstring(L, "listdirs");
	lua_pushcfunction(L, listDirectoryDirs);
	lua_rawset(L, -3);

	return 0;
}

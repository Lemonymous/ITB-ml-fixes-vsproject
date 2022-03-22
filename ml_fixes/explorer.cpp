#include "stdafx.h"
#include "explorer.h"

int listDirectoryFull(lua_State *L, int mode) {
	lua_newtable(L);

	if (!lua_isstring(L, 1))
		return 1;

	const char *dirname = lua_tostring(L, 1);

	WIN32_FIND_DATAA fdFile;
	HANDLE handle = NULL;
	std::regex fullPath("(.*)");
	std::regex startsWithDriveLetter("^.:.*$");
	std::string path;

	if (!std::regex_match(dirname, startsWithDriveLetter))
		path = regex_replace(dirname, fullPath, ".\\$1\\*.*");
	else
		path = regex_replace(dirname, fullPath, "$1\\*.*");

	if ((handle = FindFirstFileA(path.c_str(), &fdFile)) == INVALID_HANDLE_VALUE) {
		return 1;
	}

	int index = 1;
	do {
		if (strcmp(fdFile.cFileName, ".") == 0 || strcmp(fdFile.cFileName, "..") == 0)
			continue;

		int isDir = fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? 1 : 0;
		if (mode != -1 && mode != isDir)
			continue;

		lua_pushnumber(L, index++);
		lua_pushstring(L, fdFile.cFileName);
		lua_settable(L, -3);

	} while (FindNextFileA(handle, &fdFile));

	FindClose(handle);

	return 1;
}

int listDirectory(lua_State *L) {
	return listDirectoryFull(L, -1);
}

int listDirectoryFiles(lua_State *L) {
	return listDirectoryFull(L, 0);
}

int listDirectoryDirs(lua_State *L) {
	return listDirectoryFull(L, 1);
}

#ifndef EXPLORER_H
#define EXPLORER_H

#pragma once
#include "lua.hpp"

int listDirectory(lua_State *L);
int listDirectoryFiles(lua_State *L);
int listDirectoryDirs(lua_State *L);

#endif

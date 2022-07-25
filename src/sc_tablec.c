/*************************************************\
||                                               ||
||                  SANDCRATER                   ||
||                                               ||
|| This program is free software under the terms ||
|| of the GNU General Public License - version 3 ||
|| as published in  https://www.gnu.org/licenses ||
||                                               ||
||     Table creation example with Lua C-API     ||
||    Copyright (C)  2022 Thadeu A C de Paula    ||
||                                               ||
\*************************************************/


#include "sc.h"


static int createTabEx(lua_State *L) {

  /* create a table with 1 index (number) and 1 key (no-number) */
  lua_createtable(L,1,1);

  /* create a item with index 1 and value 10 */
  lua_pushnumber(L,1);
  lua_pushnumber(L,10);
  lua_settable(L,-3);

  /* create an item with key "hi" and value 20 */
  lua_pushstring(L, "hi");
  lua_pushnumber(L, 20);
  lua_settable(L,-3);
  return 1;
}


static const luaL_Reg reg[] = {
  {"createTableExample", createTabEx },
  {NULL, NULL}
};


int luaopen_sc_tablec(lua_State *L) {
  #if (LUA_VERSION_NUM == 501)
    luaL_register(L, "sc_tablec", reg);
  #elif (LUA_VERSION_NUM >= 502)
    luaL_newlib(L, reg);
  #endif
  return 1;
}

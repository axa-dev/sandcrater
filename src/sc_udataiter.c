/*************************************************\
||                                               ||
||                  SANDCRATER                   ||
||                                               ||
|| This program is free software under the terms ||
|| of the GNU General Public License - version 3 ||
|| as published in  https://www.gnu.org/licenses ||
||                                               ||
||     Lua iterator examples using  Userdata     ||
||    Copyright (C)  2022 Thadeu A C de Paula    ||
||                                               ||
\*************************************************/


#include <glob.h>
#include "sc.h"

/* //------------------------------------------------------------------------ //

In short...
Part 1 - Create a type in C (struct or typedef) or reuse some struct
Part 2 - On luaopen_* function add a metatable
Part 3 - Create a registry containing the functions to be used as methods
Part 4 - Using luaL_register (lua5.1) or luaL_setfuncs (lua5.2+) include the
         registry containing the methods and metamethods.
Part 5 - On the added method, check if the userdata has the right metatable
Part 6 - Example of garbage collection metamethod: the same function can
         be used as :close() and as __gc metamethod

// ------------------------------------------------------------------------// */


static int ls_iter(lua_State *L) {
  glob_t *lsdata = luaL_checkudata(L,1,"ls_udata");
  size_t index = luaL_checkinteger(L,2);

  if (lsdata->gl_pathc <= index) return 0;

  lua_pushinteger(L,index+1);
  lua_pushstring(L,lsdata->gl_pathv[index]);
  return 2;
}


/* PART 6. Function used as __gc and close method */
static int ls_gc(lua_State *L) {
  glob_t *lsdata = (glob_t *) lua_touserdata(L,1);
  luaL_argcheck(L, lsdata != NULL,1, "Path handler expected");
  globfree(lsdata);
  return 0;
}


static int ls_opener(lua_State *L) {

  const char *path = luaL_checkstring(L,1);

  lua_pushcfunction(L,ls_iter);
  glob_t *lsdata = lua_newuserdata(L,sizeof(glob_t));

  /* set ls_udata as the metatable of the userdata */
  luaL_getmetatable(L, "ls_udata");
  lua_setmetatable(L,-2);

  int st = glob(path,0,NULL,&(*lsdata));
  if (st == 0) {
    lua_pushinteger(L,0);
    return 3;
  } else {
    return 0;
  }
}


/* PART 3: Registry with the functions to be used as methods of userdata */
static const luaL_Reg ls_udata_mt[] = {
  {"__gc",  ls_gc},  /* PART 6 */
  {NULL,NULL}
};



/*
** List of functions exported to the module
*/
static const luaL_Reg ls_udata_functions[] = {
  {"ls", ls_opener },
  {NULL, NULL}
};


int luaopen_sc_udataiter(lua_State *L) {
  /* PART 2 - Add the metatable */
  luaL_newmetatable(L,"ls_udata");
  lua_pushvalue(L,-1);
  lua_setfield(L,-2,"__index");

  /* PART 4 - Register the methods of userdata */
  #if (LUA_VERSION_NUM == 501)
    luaL_register(L,NULL,ls_udata_mt);
  #elif (LUA_VERSION_NUM >= 502)
    luaL_setfuncs(L,ls_udata_mt, 0);
  #endif

  #if (LUA_VERSION_NUM == 501)
    luaL_register(L, "sc_tablec", ls_udata_functions);
  #elif (LUA_VERSION_NUM >= 502)
    luaL_newlib(L, ls_udata_functions);
  #endif
  return 1;
}

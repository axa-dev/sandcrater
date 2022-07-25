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
Part 1 - Create a type in C (struct or typedef)
Part 2 - On luaopen_* function add a metatable
Part 3 - Create a registry containing the functions to be used as methods
Part 4 - Using luaL_register(lua5.1) or luaL_setfuncs include the registry
         containing the methods and metamethods.
Part 5 - On the added method, check if the userdata has the right metatable
Part 6 - Example of garbage collection metamethod: the same function can
         be used as :close() and as __gc metamethod

// ------------------------------------------------------------------------// */

/* PART 1. Type Creation */
typedef struct {
  size_t pos;
  int closed;
  glob_t gt;
} ls_t;


int ls_read(lua_State *L) {
  /* PART 5. Check if userdata has the right metatable */
  ls_t *lsdata = luaL_checkudata(L,1,"ls_udata");
  if (lsdata->closed) {
    lua_pushstring(L, "Cannot read closed path");
    lua_error(L);
  }
  if (lsdata->gt.gl_pathc > lsdata->pos) {
    lua_pushstring(L,lsdata->gt.gl_pathv[lsdata->pos]);
    lsdata->pos++;
    return 1;
  }
  return 0;
}

/* PART 6. Function used as __gc and close method */
static int ls_close(lua_State *L) {
  ls_t *lsdata = (ls_t *) lua_touserdata(L,1);
  luaL_argcheck(L, lsdata != NULL,1, "Path handler expected");

  if (!lsdata->closed) {
    globfree(&(*lsdata).gt);
    lsdata->closed = 1;
  }
  return 0;
}


static int ls_opener(lua_State *L) {

  const char *path = luaL_checkstring(L,1);

  ls_t *lsdata = lua_newuserdata(L,sizeof(ls_t));

  /* set ls_udata as the metatable of the userdata */
  luaL_getmetatable(L, "ls_udata");
  lua_setmetatable(L,-2);

  lsdata->pos=0;
  lsdata->closed=0;

  int st = glob(path,0,NULL,&(*lsdata).gt);
  if (st == 0) {
    return 1;
  } else {
    return 0;
  }
}


/* PART 3: Registry with the functions to be used as methods of userdata */
static const luaL_Reg ls_udata_methods[] = {
  {"read",  ls_read},
  {"close", ls_close},  /* PART 6 */
  {"__gc",  ls_close},  /* PART 6 */
  {NULL,NULL}
};

/*
** List of functions exported to the module
*/
static const luaL_Reg ls_udata_functions[] = {
  {"ls", ls_opener },
  {NULL, NULL}
};


int luaopen_sc_udataread(lua_State *L) {
  /* PART 2 - Add the metatable */
  luaL_newmetatable(L,"ls_udata");
  lua_pushvalue(L,-1);
  lua_setfield(L,-2,"__index");

  /* PART 4 - Register the methods of userdata */
  #if (LUA_VERSION_NUM == 501)
    luaL_register(L,NULL,ls_udata_methods);
  #elif (LUA_VERSION_NUM >= 502)
    luaL_setfuncs(L,ls_udata_methods, 0);
  #endif

  #if (LUA_VERSION_NUM == 501)
    luaL_register(L, "sc_tablec", ls_udata_functions);
  #elif (LUA_VERSION_NUM >= 502)
    luaL_newlib(L, ls_udata_functions);
  #endif
  return 1;
}

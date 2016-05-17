
#include "selua.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

//#include "lua.hpp"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
==============================================================================
   Lua bindings with members and methods
==============================================================================
*/

static int get_int (lua_State *L, void *v)
{
  lua_pushnumber(L, *(int*)v);
  return 1;
}

static int set_int (lua_State *L, void *v)
{
  *(int*)v = //luaL_checkint
  luaL_checkinteger(L, 3);
  return 0;
}

static int get_number (lua_State *L, void *v)
{
  lua_pushnumber(L, *(lua_Number*)v);
  return 1;
}

static int set_number (lua_State *L, void *v)
{
  *(lua_Number*)v = luaL_checkinteger(L, 3);
  return 0;
}

static int get_string (lua_State *L, void *v)
{
  lua_pushstring(L, (char*)v );
  return 1;
}

typedef int (*Xet_func) (lua_State *L, void *v);

/* member info for get and set handlers */
typedef const struct{
  const char *name;  /* member name */
  Xet_func func;     /* get or set function for type of member */
  size_t offset;     /* offset of member within your_t */
}  Xet_reg_pre;

typedef Xet_reg_pre * Xet_reg;

static void Xet_add (lua_State *L, Xet_reg l)
{
  for (; l->name; l++) {
    lua_pushstring(L, l->name);
    lua_pushlightuserdata(L, (void*)l);
    lua_settable(L, -3);
  }
}

static int Xet_call (lua_State *L)
{
  /* for get: stack has userdata, index, lightuserdata */
  /* for set: stack has userdata, index, value, lightuserdata */
  Xet_reg m = (Xet_reg)lua_touserdata(L, -1);  /* member info */
  lua_pop(L, 1);                               /* drop lightuserdata */
  luaL_checktype(L, 1, LUA_TUSERDATA);
  return m->func(L, (void *)((char *)lua_touserdata(L, 1) + m->offset));
}

static int index_handler (lua_State *L)
{
  /* stack has userdata, index */
  lua_pushvalue(L, 2);                     /* dup index */
  lua_rawget(L, lua_upvalueindex(1));      /* lookup member by name */
  if (!lua_islightuserdata(L, -1)) {
    lua_pop(L, 1);                         /* drop value */
    lua_pushvalue(L, 2);                   /* dup index */
    lua_gettable(L, lua_upvalueindex(2));  /* else try methods */
    if (lua_isnil(L, -1))                  /* invalid member */
      luaL_error(L, "cannot get member '%s'", lua_tostring(L, 2));
    return 1;
  }
  return Xet_call(L);                      /* call get function */
}

static int newindex_handler (lua_State *L)
{
  /* stack has userdata, index, value */
  lua_pushvalue(L, 2);                     /* dup index */
  lua_rawget(L, lua_upvalueindex(1));      /* lookup member by name */
  if (!lua_islightuserdata(L, -1))         /* invalid member */
    luaL_error(L, "cannot set member '%s'", lua_tostring(L, 2));
  return Xet_call(L);                      /* call set function */
}

/*
==============================================================================
  Your structure and custom methods
==============================================================================
*/

#define YOUR_T "YourClass"

typedef struct {
  int    id;
  char   name[16];
  int    age;
  double x,y;
} your_t;


static your_t *check_your_t (lua_State *L, int index)
{
  your_t *yd;
  luaL_checktype(L, index, LUA_TUSERDATA);
  yd = (your_t *)luaL_checkudata(L, index, YOUR_T);
  if (yd == NULL) luaL_typerror(L, index, YOUR_T);
  return yd;
}

static your_t *push_your_t (lua_State *L)
{
  your_t *yd = (your_t*)lua_newuserdata(L, sizeof(your_t));
  luaL_getmetatable(L, YOUR_T);
  lua_setmetatable(L, -2);
  return yd;
}

static int id_counter;

static int your_create (lua_State *L)
{
  your_t *yd;
  //unsigned int  
  size_t name_len;
  const char *name = luaL_checklstring(L, 1, &name_len);
  if( name_len > 15 ) luaL_error(L, "name too long"); /* die */
  yd = push_your_t(L);
  strcpy( yd->name, name );
  yd->age = luaL_checkinteger(L, 2);
  yd->x   = luaL_checknumber(L, 3);
  yd->y   = luaL_checknumber(L, 4);
  yd->id  = ++id_counter;
  return 1;
}

static int your_destroy (lua_State *L)
{
  your_t *yd = (your_t*)lua_touserdata(L,1);
  printf("Goodbye %s:%d at (%lf,%lf)\n", yd->name, yd->id, yd->x, yd->y);
  return 0;
}

static int your_position (lua_State *L)
{
  your_t *yd = check_your_t(L, 1);
  double   x = yd->x;
  double   y = yd->y;
  if( lua_gettop(L) > 1 ) {
    yd->x = luaL_checknumber(L, 2);
    yd->y = luaL_checknumber(L, 3);
  }
  lua_pushnumber(L,x);
  lua_pushnumber(L,y);
  return 2;
}

static int test (lua_State *L)
{
  int n = luaL_checknumber(L, 1);
  lua_pushnumber(L, 66);
  lua_pushnumber(L, 67);
  lua_pushnumber(L, 68);
  return n;
}


static const luaL_reg your_meta_methods[] = {
{"__gc", your_destroy },
{0,0}
};

static const luaL_reg your_methods[] = {
{"create",   your_create},
{"position", your_position},
{"test",     test},
{0,0}
};

static const Xet_reg_pre your_getters[] = {
{"id",   get_int,    offsetof(your_t,id)   },
{"name", get_string, offsetof(your_t,name) },
{"age",  get_int,    offsetof(your_t,age)  },
{"x",    get_number, offsetof(your_t,x)    },
{"y",    get_number, offsetof(your_t,y)    },
{0,0}
};

static const Xet_reg_pre your_setters[] = {
{"age",  set_int,    offsetof(your_t,age)  },
{"x",    set_number, offsetof(your_t,x)    },
{"y",    set_number, offsetof(your_t,y)    },
{0,0}
};


int your_register (lua_State *L)
{
  int metatable, methods;

  /* create methods table, & add it to the table of globals */
  luaL_openlib(L, YOUR_T, your_methods, 0);
  methods = lua_gettop(L);

  /* create metatable for your_t, & add it to the registry */
  luaL_newmetatable(L, YOUR_T);
  luaL_openlib(L, 0, your_meta_methods, 0);  /* fill metatable */
  metatable = lua_gettop(L);

  lua_pushliteral(L, "__metatable");
  lua_pushvalue(L, methods);    /* dup methods table*/
  lua_rawset(L, metatable);     /* hide metatable:
                                   metatable.__metatable = methods */
  lua_pushliteral(L, "__index");
  lua_pushvalue(L, metatable);  /* upvalue index 1 */
  Xet_add(L, your_getters);     /* fill metatable with getters */
  lua_pushvalue(L, methods);    /* upvalue index 2 */
  lua_pushcclosure(L, index_handler, 2);
  lua_rawset(L, metatable);     /* metatable.__index = index_handler */

  lua_pushliteral(L, "__newindex");
  lua_newtable(L);              /* table for members you can set */
  Xet_add(L, your_setters);     /* fill with setters */
  lua_pushcclosure(L, newindex_handler, 1);
  lua_rawset(L, metatable);     /* metatable.__newindex = newindex_handler */

  lua_pop(L, 1);                /* drop metatable */
  return 1;                     /* return methods on the stack */
}


// Global static pointer used to ensure a single instance of the class.

selua* selua::m_inst = NULL; 
lua_State *g_L=NULL;

/** This function is called to create an instance of the class.
    Calling the constructor publicly is not allowed. The constructor
    is private and is only called by this Instance function.
*/

selua* selua::Instance()
{
   if (!m_inst)   // Only allow one instance of class to be generated.
      m_inst = new selua;
   return m_inst;
}

selua* selua::Erase(){
	  if(!m_inst&&g_L==NULL)
	 {
	  lua_close(g_L);
	  g_L=NULL;
	  }
	}
int selua::init(){
	 if(g_L==NULL)
	 {
	 g_L = lua_open();

  luaL_openlibs(g_L);
  /*
  luaopen_base(g_L);
  luaopen_table(g_L);
  //luaopen_io(L);
  luaopen_string(g_L);
  luaopen_math(g_L);
  luaopen_debug(g_L);
  * */
  your_register(g_L);
  }
    return 0;
	}
int selua::f_enter_lua_cbloop(){
	}
    int selua::f_exec_lua_file(std::string argv){
		//lua_dofile(g_L, (const char *)argv.c_str());
		int s = luaL_loadfile(g_L, argv.c_str());
		return 1;
	}
    int selua::f_exec_lua_ep(std::string argv,std::vector<std::string> argv2){
		return 1;
	}

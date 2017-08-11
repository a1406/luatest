#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

lua_State *global_lua;

int main(int argc, char *argv[])
{
    
    return 0;
}


void scriptingInit(int setup) {
    lua_State *lua = lua_open();

	if (setup)
	{
	}

//    luaLoadLibraries(lua);
//    luaRemoveUnsupportedFunctions(lua);

    /* Lua beginners often don't use "local", this is likely to introduce
     * subtle bugs in their code. To prevent problems we protect accesses
     * to global variables. */
//    scriptingEnableGlobalsProtection(lua);

	global_lua = lua;
}

/* Release resources related to Lua scripting.
 * This function is used in order to reset the scripting environment. */
void scriptingRelease(void) {
    lua_close(global_lua);
}

void scriptingReset(void) {
    scriptingRelease();
    scriptingInit(0);
}

void luaSetGlobalArray(lua_State *lua, char *var, char **elev, int elec) {
    int j;

    lua_newtable(lua);
    for (j = 0; j < elec; j++) {
        lua_pushlstring(lua, elev[j],strlen(elev[j]));
        lua_rawseti(lua,-2,j+1);
    }
    lua_setglobal(lua,var);
}



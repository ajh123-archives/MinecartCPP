extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <string>
#include <raylib.h>
#include "mc_script.h"
#include "mc_logging.h"
#include "mc_scripting_lib.h"
#include "minecart.h"

minecart::scripting::Script::Script(std::string path) {
	this->path = path;
	this->L = luaL_newstate();
	minecart::scripting::AddLuaLibs(this->L);
}

void minecart::scripting::Script::Start() {
	int r = luaL_dofile(this->L, this->path.c_str());
	this->CheckState(r);
}

void minecart::scripting::Script::Update() {
	
}

void minecart::scripting::Script::Shutdown() {
	lua_close(this->L);
}

bool minecart::scripting::Script::CheckState(int r) {
	if (r != LUA_OK) {
		std::string error = lua_tostring(this->L, -1);
		error = "LUA: "+error;
		minecart::engine::GetLogger()->AddLog(LOG_FATAL, error.c_str());
		return false;	
	}
	return true;
}

void minecart::scripting::AddLuaLibs(lua_State *L) {
	luaL_openlibs(L);
	lua_pushcfunction(L, minecart::logging::lua_Print);
	lua_setglobal(L, "print");
	luaL_requiref(L, "minecart", AddMineCartLib, 0);
}

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <string>
#include <raylib.h>
#include "mc_lua.h"
#include "minecart.h"

minecart::modifyable::LUAFile::LUAFile() {
	this->L = luaL_newstate();
}

void minecart::modifyable::LUAFile::Start() {
	std::string cmd = "error(\"A LUA error\") ";
	int r = luaL_dostring(this->L, cmd.c_str());
	if (r == LUA_OK) {

	} else {
		std::string error = lua_tostring(this->L, -1);
		error = "LUA: "+error;
		minecart::engine::GetLogger()->AddLog(LOG_FATAL, error.c_str());
	}
}

void minecart::modifyable::LUAFile::Update() {
	
}

void minecart::modifyable::LUAFile::Shutdown() {
	lua_close(this->L);
}

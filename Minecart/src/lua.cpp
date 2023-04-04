extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

#include <string>
#include <raylib.h>
#include "mc_lua.h"
#include "minecart.h"

minecart::modifyable::LUAFile::LUAFile(std::string path) {
	this->path = path;
	this->L = luaL_newstate();
	luaL_openlibs(this->L);
}

void minecart::modifyable::LUAFile::Start() {
	std::string cmd = "error(\"A LUA error\") ";
	int r = luaL_dofile(this->L, this->path.c_str());
	this->CheckState(r);
}

void minecart::modifyable::LUAFile::Update() {
	
}

void minecart::modifyable::LUAFile::Shutdown() {
	lua_close(this->L);
}

bool minecart::modifyable::LUAFile::CheckState(int r) {
	if (r != LUA_OK) {
		std::string error = lua_tostring(this->L, -1);
		error = "LUA: "+error;
		minecart::engine::GetLogger()->AddLog(LOG_FATAL, error.c_str());
		return false;	
	}
	return true;
}

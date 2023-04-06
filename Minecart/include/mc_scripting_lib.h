#ifndef MINECART_SCRIPTING_LIB_H
#define MINECART_SCRIPTING_LIB_H

#include <string>
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

namespace minecart {
	namespace scripting {
		int AddMineCartLib(lua_State *L);
	}
}

#endif // MINECART_SCRIPTING_LIB_H

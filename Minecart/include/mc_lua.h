#ifndef MINECART_LUA_H
#define MINECART_LUA_H

#include <string>
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

namespace minecart {
	namespace modifyable {
		class LUAFile {
			private:
				lua_State *L;
			public:
				LUAFile();
				void Start();
				void Update();
				void Shutdown();
		};
	}
}

#endif // MINECART_LUA_H

#ifndef MINECART_LUA_H
#define MINECART_LUA_H

#include <string>
extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

namespace minecart {
	namespace scripting {
		class Script {
			private:
				lua_State *L;
				std::string path;
			public:
				Script(std::string path);
				void Start();
				void Update();
				void Shutdown();
				bool CheckState(int r);
		};
	}
}

#endif // MINECART_LUA_H

#include "mc_scripting_lib.h"
#include "mc_logging.h"

int minecart::scripting::AddMineCartLib(lua_State *L) {
	static const luaL_Reg minecart[] = {
		{ "Log", minecart::logging::lua_PrintLog },
		{ NULL, NULL }
	};

	luaL_newlib( L, minecart );
	return 1;
}

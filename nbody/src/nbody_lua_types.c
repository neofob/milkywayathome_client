/*
Copyright (C) 2011  Matthew Arsenault

This file is part of Milkway@Home.

Milkyway@Home is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Milkyway@Home is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Milkyway@Home.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "nbody_types.h"
#include "nbody_lua_types.h"
#include "nbody_lua_functions.h"
#include "lua_milkyway_math.h"

static void registerNBodyTypes(lua_State* luaSt)
{
    registerBody(luaSt);

    registerHalo(luaSt);
    registerDisk(luaSt);
    registerSpherical(luaSt);

    registerPotential(luaSt);
    registerInitialConditions(luaSt);

    registerNBodyCtx(luaSt);
}

static void registerOtherTypes(lua_State* luaSt)
{
    registerMilkywayMath(luaSt);
    registerVector(luaSt);
    registerDSFMT(luaSt);
}

static void registerOtherStuff(lua_State* luaSt)
{
    registerPredefinedModelGenerators(luaSt);
    registerUtilityFunctions(luaSt);
}

static void registerUsedStandardStuff(lua_State* luaSt)
{
    luaopen_base(luaSt);
    luaopen_table(luaSt);
    luaopen_string(luaSt);
    lua_pop(luaSt, 3);
}

void registerNBodyLua(lua_State* luaSt)
{
    registerUsedStandardStuff(luaSt);
    registerNBodyTypes(luaSt);
    registerOtherTypes(luaSt);
    registerOtherStuff(luaSt);
}


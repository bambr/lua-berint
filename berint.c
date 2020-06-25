#include <stdlib.h>
#include <math.h>

#include "lua.h"
#include "lauxlib.h"

static int l_ber2int (lua_State *L) {
    size_t max = 0;
    const char* str = luaL_checklstring(L, 1, &max);

    size_t offset = 0;
    if (lua_gettop(L) >= 2) {
        offset = luaL_checknumber(L, 2) - 1;
    }

    if (max > offset+9)
        max = offset+9; // 9 bytes is max BER length for long

    long val = 0;

    int i = offset;
    while (i < max) {
        val <<= 7;
        if (str[i] & 0x80) {
            val += str[i] & 0x7F;
            i++;
        } else {
            val += str[i];
            i++;
            break;
        }
    }

    if (i-offset == 8 && (str[i] & 0x80)) {
        lua_pushnil(L);
        lua_pushnil(L);
    } else {
        lua_pushnumber(L, val);
        lua_pushnumber(L, i + 1);
    }

    return 2;
}

static int l_int2ber (lua_State *L) {
    long val = luaL_checklong(L, 1);
    if (val >= 0) {
        unsigned char size = floor(log(val) / log(0x80)) + 1;
        char data[size];

        if (size == 1)
            data[0] = val;
        else {
            int i = size-2;
            data[size-1] = val & 0x7F;

            for (; i >= 0; i--) {
                val >>= 7;
                data[i] = (val & 0x7F) | 0x80;
            }
        }
        lua_pushlstring(L, data, size);
    } else 
        lua_pushnil(L);

    return 1;
}

// -------------------------------

static const struct luaL_reg berint [] = {
    {"ber2int", l_ber2int},
    {"int2ber", l_int2ber},
    {NULL, NULL}
};

int luaopen_berint (lua_State *L) {
    luaL_openlib(L, "berint", berint, 0);
    return 1;
}

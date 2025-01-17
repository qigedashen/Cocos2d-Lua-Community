/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "scripting/lua-bindings/manual/network/lua_extensions.h"

#if __cplusplus
extern "C" {
#endif
// socket
#include "luasocket/luasocket.h"
#include "luasocket/luasocket_scripts.h"
#include "luasocket/mime.h"
// cjson
#include "cjson/lua_cjson.h"
// filesystem
#include "lfs/lfs.h"
// lpack
#include "lpack/lpack.h"
// zlib
#include "lzlib/lua_zlib.h"
// lsqlite3
#include "lsqlite3/lsqlite3.h"
// lunqlite3
#include "lunqlite/lunqlite.h"
// protoc-gen-lua
#include "protobuf/pb.h"
// sproto
LUALIB_API int luaopen_lpeg (lua_State *L);
LUALIB_API int luaopen_sproto_core(lua_State *L);
// lua-protobuf
LUALIB_API int luaopen_lua_pb (lua_State *L);
// client.crypt
LUALIB_API int luaopen_client_crypt(lua_State *L);


static luaL_Reg luax_exts[] = {
    {"socket.core", luaopen_socket_core}, // luasocket
    {"mime.core", luaopen_mime_core}, // luasocket
    {"cjson", luaopen_cjson_safe}, // cjson
    {"lfs", luaopen_lfs}, // lfs
    {"pack", luaopen_pack}, // lpack
    {"zlib", luaopen_zlib}, // lzlib
    {"lsqlite3", luaopen_lsqlite3}, // lsqlite3
    {"unqlite", luaopen_lunqlite}, // lunqlite
    {"pb", luaopen_pb}, // protoc-gen-lua
    {"lpeg", luaopen_lpeg}, // sproto
    {"sproto.core", luaopen_sproto_core}, // sproto
    {"luapb", luaopen_lua_pb}, // lua-protobuf
    {"client.crypt", luaopen_client_crypt}, // client.crypt
    {NULL, NULL}
};

void luaopen_lua_extensions(lua_State *L)
{
    // load extensions
    luaL_Reg* lib = luax_exts;
    lua_getglobal(L, "package");
    lua_getfield(L, -1, "preload");
    for (; lib->func; lib++)
    {
        lua_pushcfunction(L, lib->func);
        lua_setfield(L, -2, lib->name);
    }
    lua_pop(L, 2);

    luaopen_luasocket_scripts(L);
}

#if __cplusplus
} // extern "C"
#endif

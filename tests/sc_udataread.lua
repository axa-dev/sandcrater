--[===============================================[
||                                               ||
||                  SANDCRATER                   ||
||                                               ||
|| This program is free software under the terms ||
|| of the GNU General Public License - version 3 ||
|| as published in  https://www.gnu.org/licenses ||
||                                               ||
||     Lua iterator examples using  Userdata     ||
||    Copyright (C)  2022 Thadeu A C de Paula    ||
||                                               ||
--]===============================================]

local scui = require("sc.udataread")

local x = scui.ls("/*")

assert( type(x:read()) == "string" )
assert( type(x:read()) == "string" )
assert( x:close() == nil )

res,err = pcall(x.read,x)
assert( res == false )
assert( err == "Cannot read closed path")

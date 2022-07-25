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

local scui = require("sc.udataiter")

for i,v in scui.ls("/*") do
  assert(type(i) == "number")
  assert(type(v) == "string")
end

--[===============================================[
||                                               ||
||                  SANDCRATER                   ||
||                                               ||
|| This program is free software under the terms ||
|| of the GNU General Public License - version 3 ||
|| as published in  https://www.gnu.org/licenses ||
||                                               ||
||     Table creation example with Lua C-API     ||
||    Copyright (C)  2022 Thadeu A C de Paula    ||
||                                               ||
--]===============================================]

local tables = require("sc.tablec")

local ls = tables.createTableExample()

assert(ls[1] == 10)
assert(ls.hi == 20)


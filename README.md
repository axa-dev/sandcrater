# Sandcrater

**A Sandbox tests and references for development with Lua C API**

Considerations:

- For each demonstration, one module is created under `src` folder;
  The library opener should be on the `sc.h`. File names are prefixed
  with `sc_`.
- For each demonstration, a Lua file is created under `tests` folder
  with asserts to prove the code and intention is correct.
- By example, `src/sc_something.c` will include `sc.h` and will have
  a Lua counterpart named `tests/sc_something.lua` and the module
  required under Lua as `require("sc.something")`
- To compile and test, simply run `./luatest test`
- To clean the tree, simply run `./luatest clean`

It is recommended to have `sparse` installed and run `./luatest sparse`


## Intentions

The codes here presented are intended as proof of concept and referece only.
In other words, show how to represent C structures and data on Lua and
vice-versa.

The examples aim to be as simple as possible, so consider it may be not have
all the error checking needed for a production code, only the ones needed
to make the proof be done.


## Index

| Name          | Example intention |
|---------------|-------------------|
| `sc_udatait`  | Lua iterator based on userdata |
| `sc_tablec`   | Lua table creation via C Api   |

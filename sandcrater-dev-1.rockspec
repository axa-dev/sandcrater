package = "sandcrater"
version = "dev-1"
source = {
   url = "git+ssh://git@github.com/axa-dev/sandcrater.git"
}
description = {
   homepage = "https://github.com/axa-dev/sandcrater/README.md",
   license = "GPL-3"
}
build = {
   type = "builtin",
   modules = {
      ["sc.tablec"]  = { sources = { "src/sc_tablec.c" } },
      ["sc.udatait"] = { sources = { "src/sc_udatait.c" } }
   }
}

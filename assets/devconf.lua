--
-- This configuration is intended to be used during development tests
-- like with `make test` or `make dtest`
--

variables = {
  CFLAGS="-Wall -Wextra -O2 -pedantic-errors -fPIC -fdiagnostics-color"
}

# illumos-make

Portable Illumos make to make it easier to compile Illumos stuff on non-Illumos systems without translating the Makefile.

Tested on GNU/Linux, FreeBSD, NetBSD, DragonflyBSD, Solaris & Illumos.

## Dependencies

- Clang / GCC
- GNU make
- Bash or Korn shell to run the tests.
- libbsd (GNU/Linux)
- pkg-config

Build with `gmake` & test with `gmake test`

## Bugs / Limitations

- The distributed make (`dmake`) functionality may not work.
- The `.KEEP_STATE` feature is a no-op on non-Solaris platforms.
- Compiler warnings are turned off by default. It makes no sense to fix those if we're tracking upstream.

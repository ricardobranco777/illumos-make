
PROG	= make
PREFIX	?= /usr/local
BINDIR	?= $(PREFIX)/bin
MANDIR	?= $(PREFIX)/share/man
DATADIR	?= $(PREFIX)/share/$(PROG)
DOCDIR	?= $(PREFIX)/share/doc/$(PROG)

WARN_FLAGS = \
	-Wno-format-extra-args

CXX	?= g++
CC	?= gcc
AR	?= ar
CXXFLAGS ?= -O2 $(WARN_FLAGS)
CFLAGS	 ?= -O2 $(WARN_FLAGS)

SRCDIR	= src
BINOBJ	= $(SRCDIR)/bin
INCDIR	= $(SRCDIR)/include

OS := $(shell uname -s)

# --- Platform-specific flags & libraries ---

LIBS = -lpthread

ifeq ($(OS),Linux)
  BSD_LIBS   := $(shell pkg-config --libs   libbsd   2>/dev/null)
  BSD_CFLAGS := $(shell pkg-config --cflags libbsd   2>/dev/null)
  ifneq ($(BSD_LIBS),)
    LIBS += $(BSD_LIBS)
  endif
  LIBS += $(INTL_LIB)
endif

ifeq ($(OS),SunOS)
  CC = gcc
  CXX = g++
  LIBS += -lnsl
  # prefer OpenCSW intl
  ifneq ($(wildcard /opt/csw/lib/libintl.*),)
    LIBS += -L/opt/csw/lib -lintl
  else
    LIBS += -lintl
  endif
endif

# --- Common flags ---

COMMON_CPPFLAGS = \
  -I$(INCDIR) \
  -I/usr/local/include \
  -I/usr/local/include/libelf \
  -I$(SRCDIR) \
  -I. \
  $(BSD_CFLAGS)

all: $(PROG)

# --- libmksh ---

MKSH_SRCS = \
  $(SRCDIR)/lib/mksh/dosys.cc \
  $(SRCDIR)/lib/mksh/globals.cc \
  $(SRCDIR)/lib/mksh/i18n.cc \
  $(SRCDIR)/lib/mksh/macro.cc \
  $(SRCDIR)/lib/mksh/misc.cc \
  $(SRCDIR)/lib/mksh/mksh.cc \
  $(SRCDIR)/lib/mksh/read.cc

MKSH_OBJS = $(MKSH_SRCS:.cc=.o)
LIBMKSH   = libmksh.a

$(LIBMKSH): $(MKSH_OBJS)
	$(AR) rcs $@ $^

# --- libvroot ---

VROOT_SRCS = \
  $(SRCDIR)/lib/vroot/access.cc \
  $(SRCDIR)/lib/vroot/args.cc \
  $(SRCDIR)/lib/vroot/chdir.cc \
  $(SRCDIR)/lib/vroot/chmod.cc \
  $(SRCDIR)/lib/vroot/chown.cc \
  $(SRCDIR)/lib/vroot/chroot.cc \
  $(SRCDIR)/lib/vroot/creat.cc \
  $(SRCDIR)/lib/vroot/execve.cc \
  $(SRCDIR)/lib/vroot/lock.cc \
  $(SRCDIR)/lib/vroot/lstat.cc \
  $(SRCDIR)/lib/vroot/mkdir.cc \
  $(SRCDIR)/lib/vroot/mount.cc \
  $(SRCDIR)/lib/vroot/open.cc \
  $(SRCDIR)/lib/vroot/readlink.cc \
  $(SRCDIR)/lib/vroot/report.cc \
  $(SRCDIR)/lib/vroot/rmdir.cc \
  $(SRCDIR)/lib/vroot/setenv.cc \
  $(SRCDIR)/lib/vroot/stat.cc \
  $(SRCDIR)/lib/vroot/truncate.cc \
  $(SRCDIR)/lib/vroot/unlink.cc \
  $(SRCDIR)/lib/vroot/utimes.cc \
  $(SRCDIR)/lib/vroot/vroot.cc

VROOT_OBJS = $(VROOT_SRCS:.cc=.o)
LIBVROOT   = libvroot.a

$(LIBVROOT): $(VROOT_OBJS)
	$(AR) rcs $@ $^

# --- libmakestate ---

MAKESTATE_SRCS = \
  $(SRCDIR)/lib/makestate/ld_file.c \
  $(SRCDIR)/lib/makestate/lock.c

MAKESTATE_OBJS = $(MAKESTATE_SRCS:.c=.o)
LIBMAKESTATE   = libmakestate.a

$(LIBMAKESTATE): $(MAKESTATE_OBJS)
	$(AR) rcs $@ $^

# --- Main binary ---

BIN_SRCS = \
  $(SRCDIR)/bin/ar.cc \
  $(SRCDIR)/bin/depvar.cc \
  $(SRCDIR)/bin/doname.cc \
  $(SRCDIR)/bin/dosys.cc \
  $(SRCDIR)/bin/files.cc \
  $(SRCDIR)/bin/globals.cc \
  $(SRCDIR)/bin/implicit.cc \
  $(SRCDIR)/bin/macro.cc \
  $(SRCDIR)/bin/main.cc \
  $(SRCDIR)/bin/misc.cc \
  $(SRCDIR)/bin/nse_printdep.cc \
  $(SRCDIR)/bin/parallel.cc \
  $(SRCDIR)/bin/pmake.cc \
  $(SRCDIR)/bin/read.cc \
  $(SRCDIR)/bin/read2.cc \
  $(SRCDIR)/bin/rep.cc \
  $(SRCDIR)/bin/state.cc \
  $(SRCDIR)/lib/bsd/bsd.cc

BIN_OBJS = $(BIN_SRCS:.cc=.o)

LIBS_STATIC = $(LIBMKSH) $(LIBVROOT) $(LIBMAKESTATE)

$(PROG): $(BIN_OBJS) $(COMPAT_OBJS) $(LIBS_STATIC)
	$(CXX) $(CXXFLAGS) -o $@ $(BIN_OBJS) $(COMPAT_OBJS) $(LIBS_STATIC) $(LIBS)

# --- Generic compilation rules ---

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(COMMON_CPPFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $(COMMON_CPPFLAGS) -c -o $@ $<

clean:
	$(RM) -f $(PROG) \
	  $(BIN_OBJS) $(COMPAT_OBJS) \
	  $(MKSH_OBJS) $(VROOT_OBJS) $(MAKESTATE_OBJS) \
	  $(LIBMKSH) $(LIBVROOT) $(LIBMAKESTATE)

test:	$(PROG)
	MAKE=$$PWD/make FILEDIR=$$PWD/test/files bash test/make_test.ksh

.PHONY: all install clean test

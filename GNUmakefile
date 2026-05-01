PROG	= make

WARN_FLAGS ?= \
	-Wno-format \
	-Wno-format-security \
	-Wno-parentheses \
	-Wno-stringop-overflow \
	-Wno-switch \
	-Wno-unknown-warning-option \
	-Wno-unused-value

CXX	?= g++
CC	?= gcc
CXXFLAGS	?= -O2 $(WARN_FLAGS)
CFLAGS		?= -O2 $(WARN_FLAGS)

SRCDIR	= src
INCDIR	= $(SRCDIR)/include

OS := $(shell uname -s)

LIBS = -lpthread

ifeq ($(OS),Linux)
	BSD_CFLAGS := $(shell pkg-config --cflags libbsd 2>/dev/null)
	BSD_LIBS   := $(shell pkg-config --libs   libbsd 2>/dev/null)
	ifneq ($(BSD_LIBS),)
		LIBS += $(BSD_LIBS)
	endif
endif

ifeq ($(OS),NetBSD)
	LIBS += -lrt
endif

ifeq ($(OS),SunOS)
	CC  = gcc
	CXX = g++
	LIBS += -lnsl
endif

LIBELF_CFLAGS := $(shell pkg-config --cflags libelf 2>/dev/null)
LIBELF_LIBS   := $(shell pkg-config --libs   libelf 2>/dev/null)
LIBS += $(LIBELF_LIBS)

COMMON_CPPFLAGS = \
	-I$(INCDIR) \
	-I$(SRCDIR) \
	-I. \
	$(BSD_CFLAGS)

BIN_SRCS      := $(wildcard $(SRCDIR)/bin/*.cc) $(SRCDIR)/lib/bsd/bsd.cc
MAKESTATE_SRCS := $(wildcard $(SRCDIR)/lib/makestate/*.c)
MKSH_SRCS     := $(wildcard $(SRCDIR)/lib/mksh/*.cc)
ifeq ($(OS),SunOS)
	VROOT_SRCS := $(wildcard $(SRCDIR)/lib/vroot/*.cc)
else
	VROOT_SRCS := $(filter-out $(SRCDIR)/lib/vroot/mount.cc, \
		$(wildcard $(SRCDIR)/lib/vroot/*.cc))
endif

BIN_OBJS       = $(BIN_SRCS:.cc=.o)
MAKESTATE_OBJS = $(MAKESTATE_SRCS:.c=.o)
MKSH_OBJS      = $(MKSH_SRCS:.cc=.o)
VROOT_OBJS     = $(VROOT_SRCS:.cc=.o)

all: $(PROG)

$(PROG): $(BIN_OBJS) $(MKSH_OBJS) $(VROOT_OBJS) $(MAKESTATE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(COMMON_CPPFLAGS) -c -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) $(COMMON_CPPFLAGS) -c -o $@ $<

test: $(PROG)
	MAKE=$$PWD/$(PROG) FILEDIR=$$PWD/test/files $$(command -v ksh || command -v bash) test/make_test.ksh

clean:
	$(RM) $(PROG) $(BIN_OBJS) $(MKSH_OBJS) $(VROOT_OBJS) $(MAKESTATE_OBJS)

.PHONY: all install test clean

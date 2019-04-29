# wdwm version
VERSION = 6.2

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

X11INC = /usr/X11R6/include
X11LIB = /usr/X11R6/lib

# Xinerama
XINERAMALIBS  = -lXinerama

# freetype
FREETYPELIBS = -lfontconfig -lXft
FREETYPEINC = /usr/include/freetype2
# OpenBSD (uncomment)
#FREETYPEINC = ${X11INC}/freetype2

# wayland
WAYLANDLIBS = -lwayland-server

# wayland proto plumbing
WAYLANDPROTOCOLS = /usr/share/wayland-protocols
WAYLANDSCANNER = /usr/bin/wayland-scanner

# xkbcommon
XKBLIBS = -lxkbcommon

# wlroots
WLROOTSLIBS = -lwlroots

# pixman
PIXMANINC = /usr/include/pixman-1

# includes and libs
INCS = -I. -I${X11INC} -I${FREETYPEINC} -I${PIXMANINC}
LIBS = -L${X11LIB} -lX11 ${XINERAMALIBS} ${FREETYPELIBS} ${WAYLANDLIBS} ${XKBLIBS} ${WLROOTSLIBS}

# flags
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DWLR_USE_UNSTABLE
#CFLAGS   = -g -std=c99 -pedantic -Wall -O0 ${INCS} ${CPPFLAGS}
CFLAGS   = -std=c99 -pedantic -Wall -Wno-deprecated-declarations -Os ${INCS} ${CPPFLAGS}
LDFLAGS  = ${LIBS}

# compiler and linker
CC = cc

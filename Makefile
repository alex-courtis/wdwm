# wdwm - wayland dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c wdwm.c util.c xdg-shell-protocol.c
OBJ = ${SRC:.c=.o}

all: options wdwm

options:
	@echo wdwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk xdg-shell-protocol.h

config.h:
	cp config.def.h $@

xdg-shell-protocol.h:
	${WAYLANDSCANNER} server-header\
		${WAYLANDPROTOCOLS}/stable/xdg-shell/xdg-shell.xml $@

xdg-shell-protocol.c:
	${WAYLANDSCANNER} private-code\
		${WAYLANDPROTOCOLS}/stable/xdg-shell/xdg-shell.xml $@

wdwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f wdwm ${OBJ} wdwm-${VERSION}.tar.gz xdg-shell-protocol.[ch]

dist: clean
	mkdir -p wdwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		wdwm.1 drw.h util.h xdg-shell-protocol.h ${SRC} dwm.png\
		transient.c wdwm-${VERSION}
	tar -cf wdwm-${VERSION}.tar wdwm-${VERSION}
	gzip wdwm-${VERSION}.tar
	rm -rf wdwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f wdwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/wdwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < wdwm.1 >\
		${DESTDIR}${MANPREFIX}/man1/wdwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/wdwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/wdwm\
		${DESTDIR}${MANPREFIX}/man1/wdwm.1

.PHONY: all options clean dist install uninstall

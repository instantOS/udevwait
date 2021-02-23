PREFIX = /usr/

all: udevwait

udevwait: udevwait.c
	gcc -ludev -o udevwait udevwait.c

install: udevwait
	install -Dm 755 udevwait ${DESTDIR}${PREFIX}bin/udevwait

uninstall:
	rm ${DESTDIR}${PREFIX}bin/udevwait

clean:
	rm udevwait

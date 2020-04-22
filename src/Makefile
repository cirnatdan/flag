PREFIX?=	/usr/local
BINDIR=		${PREFIX}/bin

PROG=	flag
SRCS=	flag.c config.c

.PATH:	${.CURDIR}/include
SRCS+=	pkgsrc.c
MAN=

DPLIBS+=	libc

.include <bsd.prog.mk>

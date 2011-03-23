#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pkgfind/pkgfind.h"

#define PKGSRCDIR	"/usr/pkgsrc"

int
main(int argc, char *argv[])
{
	const char *path;
	int ch, count = 0;

	setprogname("flag");

	/* default matches are partial matches */
	match = partialmatch;
	/* no special searches by default */
	search = NULL;

	cflag = qflag = 0;

	while ((ch = getopt(argc, argv, "Ccn:Mqx")) != -1) {
		switch (ch) {
		case 'C':	/* search in comments */
			search = "COMMENT";
			break;
		case 'c':	/* case sensitive */
			cflag = 1;
			break;
		case 'n':
			count = atoi(optarg);
			break;
		case 'M':	/* search for maintainer */
			search = "MAINTAINER";
			break;
		case 'q':	/* quiet, don't output comment */
			qflag = 1;
			break;
		case 'x':	/* exact matches */
			match = exactmatch;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	if ((path = getenv("PKGSRCDIR")) == NULL)
		path = PKGSRCDIR;

	for (; *argv != NULL; ++argv)
		pkgfind(path, *argv, count);

	return 0;
}

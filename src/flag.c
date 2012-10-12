#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pkgfind/pkgfind.h"
#include "config.h"

static void
usage()
{
	(void)fprintf(stderr, "Usage: flag [command] [package1] [package2] ... \n");
	exit(EXIT_FAILURE);
}

static void
handle_options(const char ***argv, int *argc)
{
	const char *path;
	char *commands[] = {"--install", "--remove", "--search"};
	char *command = NULL;
	int ch, count = 0, i,j;

	if (*argc < 2)
		usage();

	printf("number of arguments: %i \n", *argc);
	for (i = 0; i < *argc; i++)
	{
		if (i == 1) {
			for (j = 0; j < )
		}
		printf("argument %i: %s\n", i, (*argv)[i]);
	}

	path = flag_get_pkgsrc_path();

	//for (; *argv != NULL; ++argv)
	//	pkgfind(path, *argv, count);
}

int
main(int argc, const char **argv)
{
	//setprogname("flag");
	flag_load_config();

	handle_options(&argv, &argc);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "config.h"
#include "include/commands.h"

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
	int ch, count = 0, i,j;

	if (*argc < 2)
		usage();

	path = flag_get_pkgsrc_path();
	
	if (strcmp((*argv)[1], "--install") == 0) {
		printf("install command \n");
	}
	else if(strcmp((*argv)[1], "--search") == 0) {
		printf("search command \n");
		for (i = 2; i < *argc; i++) {
			printf("pkg[%i]: %s\n", i, (*argv)[i]);
			flag_search(path, (*argv)[i]);
		}

	}
	else if(strcmp((*argv)[1], "--remove") == 0) {
		printf("remove command \n");	
	}
}

int
main(int argc, const char **argv)
{
	//setprogname("flag");
	flag_load_config();

	handle_options(&argv, &argc);

	return 0;
}

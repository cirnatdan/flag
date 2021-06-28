#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "config.h"
#include "commands.h"

static void
usage()
{
	(void)fprintf(stderr, "Usage: flag [command] [package1] [package2] ... \n");
	exit(EXIT_FAILURE);
}

void
search(const char ***search_strings, int count, const char *pkgsrc_path)
{
	struct package *packages;
	int i, j = 0;
	for (i = 0; i < count; i++) {
		packages = pkgsrc_search(pkgsrc_path, (*search_strings)[i], 0, 0);

		while(strcmp(packages[j].name, "") != 0) {
			printf("%s\n", packages[j].path);
			j++;
		}
	}
}

void
print_options(const char *package_name, const char *pkgsrc_path)
{
	struct package *packages;
	packages = pkgsrc_search(pkgsrc_path, package_name, 1, 0);
	if (strcmp(packages[0].name, "") == 0 ) {
		printf("Package not found! \n");
		return;
	}
	pkgsrc_options(pkgsrc_path, packages[0]);
}

void
print_dependencies(const char *package_name, const char *pkgsrc_path)
{
	struct package *packages;
	packages = pkgsrc_search(pkgsrc_path, package_name, 1, 0);
	if (strcmp(packages[0].name, "") == 0 ) {
		printf("Package not found! \n");
		return;
	}
	pkgsrc_dependencies(pkgsrc_path, packages[0]);
}

void
install(const char ***package_names, int count, const char *pkgsrc_path)
{
	struct package packages[count];
	struct package *search_result;

	for (int i = 0; i < count; i++) {
		search_result = pkgsrc_search(pkgsrc_path, (*package_names)[i], 1, 0);
		if (strcmp(search_result[0].name, "") == 0) {
			printf("Package %s not found! \n", (*package_names)[i]);
			return;
		}
		packages[i] = search_result[0];
	}

	for (int i = 0; i < count; i++) {
		pkgsrc_install(pkgsrc_path, packages[i]);
	}
}

void
remove_packages(const char ***package_names, int count, const char *pkgsrc_path)
{
	struct package packages[count];
	struct package *search_result;

	for (int i = 0; i < count; i++) {
		search_result = pkgsrc_search(pkgsrc_path, (*package_names)[i], 1, 0);
		if (strcmp(search_result[0].name, "") == 0) {
			printf("Package %s not found! \n", (*package_names)[i]);
			return;
		}
		packages[i] = search_result[0];
	}

	for (int i = 0; i < count; i++) {
		pkgsrc_remove(pkgsrc_path, packages[i]);
	}
}

static void
handle_options(const char ***argv, int *argc)
{
	const char *pkgsrc_path;
	int ch, count = 0, i,j;

	if (*argc < 2)
		usage();

	(*argv)++;
	(*argc)--;
	const char *command = (*argv)[0];

	pkgsrc_path = flag_get_pkgsrc_path();
	
	if (strcmp(command, "install") == 0) {
		(*argv)++;
		(*argc)--;
		install(&(*argv), *argc, pkgsrc_path);
	}
	else if(strcmp(command, "search") == 0) {
		(*argv)++;
		(*argc)--;
		search(&(*argv), *argc, pkgsrc_path);
	}
	else if(strcmp(command, "remove") == 0) {
		(*argv)++;
		(*argc)--;
		remove_packages(&(*argv), *argc, pkgsrc_path);
	}
	else if(strcmp(command, "options") == 0) {
		(*argv)++;
		(*argc)--;
		print_options((*argv)[0], pkgsrc_path);
	}
	else if(strcmp(command, "dependencies") == 0) {
		(*argv)++;
		(*argc)--;
		print_dependencies((*argv)[0], pkgsrc_path);
	}
}

int
main(int argc, const char **argv)
{
	//setprogname("flag");
	flag_load_config();

	handle_options(&argv, &argc);

	return EXIT_SUCCESS;
}

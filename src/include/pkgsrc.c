/*
 * Contains adapted code from pkgfind
 *
 * Copyright (c) 2004 Peter Postma <peter@pointless.nl>
 * All rights reserved.
 * 
 * Includes modifications by  * pancake@phreaker.net ** changes 2004/09/14
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <sys/stat.h>
#include <sys/param.h>

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#if HAVE_NBCOMPAT_H
#include <nbcompat.h>
#else
#include <err.h>
#endif

#include "pkgsrc.h"

//GLOBAL VARIABLES
const char * const skip[] = {
	".", "..", "CVS", ".git", "bootstrap", "doc", "distfiles",
	"licenses", "mk", "packages", NULL
};

int		(*match)(const char *, const char *, int);


static int
checkskip(const struct dirent *dp)
{
	const char * const *p;

	for (p = skip; *p != NULL; p++)
		if (strcmp(dp->d_name, *p) == 0)
			return 0;
	return 1;
}

int
partialmatch(const char *s, const char *find, int case_sensitive)
{
	size_t len, n;

	len = strlen(find);
	n = strlen(s) - len;

	do {
		if (strncasecmp(s, find, len) == 0)
				return 1;
	} while (*++s != '\0' && n-- > 0);

	return 0;
}

static int
exactmatch(const char *s, const char *find, int case_sensitive)
{
	if (case_sensitive)
		return (strcmp(s, find) == 0);
	else
		return (strcasecmp(s, find) == 0);
}

struct package*
pkgsrc_search(const char *pkgsrc_path, const char *package_name, int exact_match, int case_sensitive)
{
	struct dirent **category, **package_list = NULL;
	int category_count, package_count;

	char tmp[PATH_MAX];
	char *text = NULL;
	struct stat sb;

	struct package temp_package;
	struct package *packages;
	int packages_found = 0;

	packages = (struct package *)malloc(sizeof(struct package)*200);

	match = partialmatch;
	if (exact_match)
		match = exactmatch;

	if ((category_count = scandir(pkgsrc_path, &category, checkskip, alphasort)) < 0)
		err(EXIT_FAILURE, "%s", pkgsrc_path);

	int i,j;
//	printf("%d\n", category_count);
	for (i = 0; i < category_count; i++) {
		if (snprintf(tmp, sizeof(tmp), "%s/%s", pkgsrc_path, category[i]->d_name)
		    >= sizeof(tmp)) {
			warnx("filename too long");
			continue;
		}
		if (stat(tmp, &sb) < 0 || !S_ISDIR(sb.st_mode))
			continue;
		if ((package_count = scandir(tmp, &package_list, checkskip, alphasort)) < 0) {
			//warn("%s", tmp);
			continue;
		}
		for (j = 0; j < package_count; j++) {
			if (packages_found == 200) {
				break;
			}
			text = package_list[j]->d_name;
			if ((*match)(text, package_name, 0)) {
				//printf("%s/%s\n", category[i]->d_name, package_list[j]->d_name);
				strcpy(temp_package.name, package_list[j]->d_name);
				snprintf(temp_package.path, sizeof(temp_package.path), "%s/%s", category[i]->d_name, package_list[j]->d_name);

				packages[packages_found] = temp_package;
				packages_found++;
			}
		}
	}
	//terminate array with NULL struct
	strcpy(temp_package.name, "");
	packages[packages_found + 1] = temp_package;
	return packages;
}

void
pkgsrc_options(const char *pkgsrc_path, struct package package)
{
	char package_dir[300];
	snprintf(package_dir, sizeof(package_dir), "%s/%s", pkgsrc_path, package.path);

	chdir(package_dir);
	system("bmake show-options");
}

void
pkgsrc_install(const char *pkgsrc_path, struct package package)
{
	char package_dir[300];
	snprintf(package_dir, sizeof(package_dir), "%s/%s", pkgsrc_path, package.path);

	chdir(package_dir);
	system("bmake install clean clean-depends");
}


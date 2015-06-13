/*
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

#if HAVE_NBCOMPAT_H
#include <nbcompat.h>
#else
#include <err.h>
#endif

//GLOBAL VARIABLES
const char * const skip[] = {
	".", "..", "CVS", ".git", "bootstrap", "doc", "distfiles",
	"licenses", "mk", "packages", NULL
};

int		(*match)(const char *, const char *);

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
partialmatch(const char *s, const char *find)
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

void 
flag_search(const char *path, const char *pkg)
{
	struct dirent **category, **package_list = NULL;
	int category_count, package_count;

	char tmp[PATH_MAX];
	char *text = NULL;
	struct stat sb;

	match = partialmatch;
	if ((category_count = scandir(path, &category, checkskip, alphasort)) < 0)
		err(EXIT_FAILURE, "%s", path);

	int i,j;
	printf("%d\n", category_count);
	for (i = 0; i < category_count; i++) {
		if (snprintf(tmp, sizeof(tmp), "%s/%s", path, category[i]->d_name)
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
			text = package_list[j]->d_name;
			if ((*match)(text, pkg)) {
				printf("%s/%s\n", category[i]->d_name, package_list[j]->d_name);
			}
		}
	}
}


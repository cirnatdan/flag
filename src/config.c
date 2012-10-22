#include <stdlib.h>
#include "defaults.h"

#include <stdio.h>


void 
flag_load_config()
{
}

const char*
flag_get_pkgsrc_path()
{
	const char *path;

	if ((path = getenv("PKGSRCDIR")) == NULL)
		path = PKGSRCDIR;

	return path;
}
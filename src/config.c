#include "defaults.h"
#include "stdlib.h"

void 
flag_load_config()
{
}

char*
flag_get_pkgsrc_path()
{
	const char *path;
	if ((path = getenv("PKGSRCDIR")) == NULL)
		path = PKGSRCDIR;
}
#include <dirent.h>

void		pkgfind(const char *, const char *, int);
void		showpkg(const char *, const char *, const char *);
int		getstring(const char *, const char *, char **);
int		checkskip(const struct dirent *);
int		partialmatch(const char *, const char *);
int		exactmatch(const char *, const char *);
void			usage(void);

int		(*match)(const char *, const char *);

const char	*search;
int		cflag, qflag;

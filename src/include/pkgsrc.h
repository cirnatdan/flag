struct package {
    char name[50];
    char description[250];
    char path[100];
};

struct package* pkgsrc_search(const char *, const char *, int, int);
void pkgsrc_options(const char*, struct package);
void pkgsrc_install(const char*, struct package);
void pkgsrc_remove(const char *, struct package);
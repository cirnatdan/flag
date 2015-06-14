INCLUDE(CheckIncludeFiles)

CHECK_INCLUDE_FILES(nbcompat.h HAVE_NBCOMPAT_H)
add_library(commands pkgsrc.c)
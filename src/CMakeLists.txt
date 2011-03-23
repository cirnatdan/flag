include_directories("${PROJECT_SOURCE_DIR}/pkgfind")
add_subdirectory(pkgfind)


add_executable(flag flag.c)
target_link_libraries (flag pkgfind)

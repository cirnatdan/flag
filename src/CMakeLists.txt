include_directories("${PROJECT_SOURCE_DIR}/commands")
add_subdirectory(commands)


add_executable(flag config.c flag.c)
target_link_libraries (flag commands)

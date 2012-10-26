include_directories("${PROJECT_SOURCE_DIR}/include")
add_subdirectory(include)


add_executable(flag config.c flag.c)
target_link_libraries (flag commands)

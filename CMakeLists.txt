project(flag)
cmake_minimum_required(VERSION 2.8)

# Add path for custom modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules"
  )
  
include(TargetDistclean)

add_subdirectory(src)

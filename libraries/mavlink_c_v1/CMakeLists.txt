# v3.21 implemented semantic changes regarding $<TARGET_OBJECTS:...>
# See https://cmake.org/cmake/help/v3.21/command/target_link_libraries.html#linking-object-libraries-via-target-objects
cmake_minimum_required(VERSION 3.21)

add_library(mavlink_c_v1 INTERFACE)
add_library(mavlink_c_v1_usage INTERFACE)

target_include_directories(mavlink_c_v1_usage INTERFACE
  src
)

target_link_libraries(mavlink_c_v1_usage INTERFACE
  base_config
)

target_link_libraries(mavlink_c_v1 INTERFACE mavlink_c_v1_usage)



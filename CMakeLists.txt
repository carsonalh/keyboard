cmake_minimum_required (VERSION 3.8)

project (keyboard C)

enable_testing ()

set (UNITY_EXTENSION_FIXTURE ON CACHE BOOL "")
add_subdirectory (Unity)

add_subdirectory (KeyboardController)


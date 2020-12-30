cmake_minimum_required (VERSION 3.8)

add_library (keyboard_layer STATIC)
target_sources (keyboard_layer
        PRIVATE
            keyboard_layer.h
            keyboard_layer.c
)
# Only do this for now; we will need to include the real keyboard library later
target_link_libraries (keyboard_layer PRIVATE keyboard_mock)
target_include_directories (keyboard_layer PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

enable_testing ()

add_executable (keyboard_layer_test)
target_sources (keyboard_layer_test PRIVATE keyboard_layer_test.c)
target_link_libraries (keyboard_layer_test
        PRIVATE
            keyboard_layer
            keyboard_mock
            unity
)
add_test (COMMAND keyboard_layer_test NAME keyboard_layer)


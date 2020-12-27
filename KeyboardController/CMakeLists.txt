cmake_minimum_required (VERSION 3.8)

# TODO: Add the real keyboard library

add_library (keyboard_mock STATIC)
target_sources (keyboard_mock
        PRIVATE
            keyboard.h
            keyboard_mock.h
            keyboard_mock.c
)
target_include_directories (keyboard_mock
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}"
)

enable_testing ()

add_executable (keyboard_mock_test
    keyboard_mock_test.c
)
target_link_libraries (keyboard_mock_test
        PRIVATE
            keyboard_mock
            unity
)
add_test (COMMAND keyboard_mock_test NAME keyboard_mock_test)


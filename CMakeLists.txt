cmake_minimum_required(VERSION 3.27.7)
project(Algolizer)


set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    src/main.cpp
    src/linear_search.cpp
    src/binary_search.cpp
    src/array.cpp
    src/queue.cpp
    src/utils/InputBox.cpp
    src/bubble_sort.cpp
    src/selection_sort.cpp
    src/stack.cpp
    src/merge_sort.cpp
    src/tree.cpp
    src/insertion_sort.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


include_directories(external)




if(WIN32)
    include(FetchContent)
    set(RAYLIB_VERSION 5.0)
    FetchContent_Declare(
          raylib
          URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
          FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
    )
    set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
    FetchContent_MakeAvailable(raylib)
else()
    find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0
endif()

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    add_library(raygui SHARED IMPORTED)
    set_target_properties(raygui PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/raygui/raygui.dynlib)

    target_link_libraries(${PROJECT_NAME} raygui)

    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

target_link_libraries(${PROJECT_NAME} raylib)


cmake_minimum_required(VERSION 3.27.7)
project(Algolizer)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_FILES
    src/main.cpp
    src/linear_search.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})




include_directories(external)



target_link_libraries(${PROJECT_NAME} raylib)



# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    add_library(raygui SHARED IMPORTED)
    set_target_properties(raygui PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/raygui/raygui.dynlib)

   target_link_libraries(${PROJECT_NAME} raygui)

    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

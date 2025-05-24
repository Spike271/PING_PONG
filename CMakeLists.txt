cmake_minimum_required(VERSION 3.30)
project(PING_PONG LANGUAGES C VERSION 1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)

    # Uncomment if using Wayland
    # find_package(Wayland REQUIRED)
endif ()

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    message("downloading raylib from git.")
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif ()
endif ()

FetchContent_Declare(
        raygui
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raygui/archive/master.tar.gz
)
FetchContent_MakeAvailable(raygui)

# Our Project
add_executable(${PROJECT_NAME} src/main.c
        headers/Ball.h
        headers/Draw.h
        headers/Global.h
        headers/Rectangle.h
        headers/RenderAboutSection.h
        headers/RenderSinglePlayerLevel.h
        headers/RenderMultiPlayerLevel.h
)

if (WIN32)
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY WIN32_EXECUTABLE TRUE)
elseif(APPLE)
    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY MACOSX_BUNDLE TRUE)
elseif (UNIX AND NOT APPLE)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE
        ${raygui_SOURCE_DIR}/src
)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})

    # Uncomment if using Wayland
    # target_link_libraries(${PROJECT_NAME} PRIVATE ${Wayland_LIBRARIES})
endif ()

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(DEST_DIR "${CMAKE_BINARY_DIR}")
file(COPY ${SOURCE_DIR} DESTINATION ${DEST_DIR})

if (${PLATFORM} STREQUAL "Web")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Os -Wall -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s GL_ENABLE_GET_PROC_ADDRESS=1 -s FORCE_FILESYSTEM=1 -s INITIAL_MEMORY=314572800 -s TOTAL_MEMORY=536870912 --preload-file ../res/")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an {project_name}.html file.
endif ()

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()

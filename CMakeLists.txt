cmake_minimum_required(VERSION 3.16)

project(app C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ASSETS FOLDER MACRO
add_compile_definitions(ASSETS_FOLDER="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# ---------- SDL options (IMPORTANT) ----------
# Disable things you don't need to speed up build
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)

set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)

# ---------- Add SDL ----------
add_subdirectory(vendor/sdl)

# ---------- Your sources ----------
file(GLOB_RECURSE APP_SOURCES
    src/*.c
)

add_executable(${PROJECT_NAME} ${APP_SOURCES})

# ---------- Includes ----------
target_include_directories(${PROJECT_NAME} PRIVATE
    include
)

# ---------- Link SDL ----------
# SDL creates targets: SDL3::SDL3 (shared) and SDL3::SDL3-static
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3-static)


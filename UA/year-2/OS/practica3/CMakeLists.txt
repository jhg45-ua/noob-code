cmake_minimum_required(VERSION 3.11)
project(gestomemoria C)

set(CMAKE_C_STANDARD 17)

# Buscar Raylib
find_package(raylib REQUIRED)

include_directories(../lib)

# Definir fuentes
file(GLOB SOURCES "src/*.c" "../lib/file_utils.c")

# Crear ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} raylib m)
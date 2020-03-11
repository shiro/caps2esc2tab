cmake_minimum_required(VERSION 3.0)

project(key-mods)

add_executable(key-mods src/main.c src/capslock.h)
target_compile_options(key-mods PRIVATE -Wall -Wextra)

install(TARGETS key-mods RUNTIME DESTINATION bin)

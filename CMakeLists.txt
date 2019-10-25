cmake_minimum_required(VERSION 3.0)

project(caps2esc2tab)

add_executable(caps2esc2tab src/main.c src/capslock.h)
target_compile_options(caps2esc2tab PRIVATE -Wall -Wextra)

install(TARGETS caps2esc2tab RUNTIME DESTINATION bin)

cmake_minimum_required(VERSION 3.0)

project(imgconv_kdev LANGUAGES C)

add_executable(imgconv_kdev main.c)

install(TARGETS imgconv_kdev RUNTIME DESTINATION bin)

cmake_minimum_required(VERSION 3.13)
project(wdwm VERSION 7.0 LANGUAGES C)

set(CMAKE_C_FLAGS "-std=c99 -pedantic -Wall")

add_compile_definitions(
        VERSION="${CMAKE_PROJECT_VERSION}"
        _DEFAULT_SOURCE
        _BSD_SOURCE
        _POSIX_C_SOURCE=2
        WLR_USE_UNSTABLE)

include_directories(
        .
        /usr/X11R6/include
        /usr/include/freetype2
        /usr/include/pixman-1)

add_executable(wdwm
        config.h
        drw.c
        drw.h
        wdwm.c
        util.c
        util.h
        xdg-shell-protocol.h
        xdg-shell-protocol.c)

target_link_libraries(wdwm
        X11
        Xinerama
        fontconfig
        Xft
        wayland-server
        xkbcommon
        wlroots)

cmake_minimum_required(VERSION 3.5)

project(ctetris LANGUAGES C)

add_executable(ctetris
    main.c
    figure.h
    figure.c
    pos.h
    pos.c
    glass.h
    glass.c
    display.h
    display.c
    constants.h
)

target_link_libraries(ctetris
    ncurses
)

add_executable(tests
    tests_main.c
    figure.h
    figure.c
    pos.h
    pos.c
    glass.h
    glass.c
    constants.h
)

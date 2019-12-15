cmake_minimum_required(VERSION 3.5)

project(ctetris LANGUAGES C)

add_executable(ctetris
    constants.h
    main.c
    figure.h
    figure.c
    pos.h
    pos.c
    glass.h
    glass.c
    display.h
    display.c
    game.h
    game.c
    rnd.h
    rnd.c
)

target_link_libraries(ctetris
    ncurses
)

add_executable(tests
    constants.h
    tests_main.c
    figure.h
    figure.c
    pos.h
    pos.c
    glass.h
    glass.c
    rnd.h
    rnd.c
)

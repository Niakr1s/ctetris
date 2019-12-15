cmake_minimum_required(VERSION 3.5)

project(ctetris LANGUAGES C)

set(SRC
    constants.h
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

add_executable(ctetris
    main.c
    ${SRC}
)

target_link_libraries(ctetris
    ncurses
)

add_executable(tests
    tests_main.c
    ${SRC}
)

target_link_libraries(tests
    ncurses
)

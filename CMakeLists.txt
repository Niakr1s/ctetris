cmake_minimum_required(VERSION 3.5)

project(ctetris LANGUAGES CXX VERSION 17)

set(SRC
    constants.h
    figure.h
    figure.cpp
    pos.h
    pos.cpp
    glass.h
    glass.cpp
    display.h
    display.cpp
    game.h
    game.cpp
    rnd.h
    rnd.cpp
)

add_executable(ctetris
    main.cpp
    ${SRC}
)

target_link_libraries(ctetris
    ncurses
)

if (WITH_TESTS)
add_executable(tests
    tests_main.cpp
    ${SRC}
)

target_link_libraries(tests
    ncurses
)
endif ()

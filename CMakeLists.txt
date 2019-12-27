cmake_minimum_required(VERSION 3.5)

project(ctetris LANGUAGES CXX VERSION 17)

set(SRC
    standardfigure.h
    standardfigure.cpp
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
    ifigure.h
    ifigure.cpp
    ifigurefactory.h
    ifigurefactory.cpp
    figurefactory.h
    figurefactory.cpp
    randomfigurefactory.h
    randomfigurefactory.cpp
)

if(WIN32)
    file(GLOB CURSES ${PDCURSES_LIB_DIR}/*)
    include_directories(${PDCURSES_INCLUDE_DIR})
else()
    set(CURSES ncurses)
endif()

add_executable(ctetris
    main.cpp
    ${SRC}
)

target_link_libraries(ctetris
    ${CURSES}
)

if (WITH_TESTS)
add_executable(tests
    tests_main.cpp
    ${SRC}
)

target_link_libraries(tests
    ${CURSES}
)
endif ()

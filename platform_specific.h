#ifndef PLATFORM_SPECIFIC_H
#define PLATFORM_SPECIFIC_H

#ifdef WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

#endif  // PLATFORM_SPECIFIC_H

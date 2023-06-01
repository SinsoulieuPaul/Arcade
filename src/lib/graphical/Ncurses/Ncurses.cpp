/*
** EPITECH PROJECT, 2023
** B-PDG-300-LIL-3-1-PDGRUSH3-ulysse.decottignies
** File description:
** Ncurses
*/

#include "Ncurses.hpp"

/*==============/
/  Exceptions   /
/==============*/

/// @brief Constructor of the NcursesException class
/// @param message The exception message
/// @param component The component that throw the exception
Ncurses::NcursesException::NcursesException(const std::string &message)
{
    _message = "Ncurses: " + message;
}

/// @brief Return the exception message
/// @return The exception message
const char *Ncurses::NcursesException::what() const noexcept
{
    return _message.c_str();
}

WINDOW *Ncurses::_initscr(void)
{
    return initscr();
}

int Ncurses::_endwin(void)
{
    return endwin();
}

int Ncurses::_clear()
{
    return clear();
}

void Ncurses::_printw(std::string str)
{
    if (str.empty())
        throw NcursesException("Empty string");
    printw("%s", str.c_str());
}

int Ncurses::_getch()
{
    return getch();
}

void Ncurses::_timeout()
{
    timeout(10);
}

void Ncurses::_refresh()
{
    refresh();
}

void Ncurses::_keypad(WINDOW *win, bool boolean)
{
    keypad(win, boolean);
}

void Ncurses::_curs_set(int curs)
{
    curs_set(curs);
}

int Ncurses::_mvaddch(int y, int x, unsigned int ch)
{
    return mvaddch(y, x, ch);
}

int Ncurses::_mvaddstr(int y, int x, const char *str)
{
    return mvaddstr(y, x, str);
}
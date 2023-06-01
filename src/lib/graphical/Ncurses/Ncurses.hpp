/*
** EPITECH PROJECT, 2023
** B-PDG-300-LIL-3-1-PDGRUSH3-ulysse.decottignies
** File description:
** Ncurses
*/

#pragma once
#include <curses.h>
#include <string>

class Ncurses {
    public:
        /// @author Zelie
        /// @brief _initscr function
        /// @param void
        /// @return WINDOW *
        static WINDOW *_initscr(void);

        /// @author Zelie
        /// @brief _endwin function
        /// @param void
        /// @return int
        static int _endwin (void);

        /// @author Zelie
        /// @brief _clear function
        /// @param void
        /// @return int
        static int _clear();

        /// @author Zelie
        /// @brief _getch function
        /// @param void
        /// @return int
        static int _getch();

        /// @author Zelie
        /// @brief _printw function
        /// @param std::string str
        /// @return void
        static void _printw(std::string str);

        /// @author Zelie
        /// @brief _refresh function
        /// @param void
        /// @return void
        static void _refresh();

        /// @author Zelie
        /// @brief _timeout function
        /// @param void
        /// @return void
        static void _timeout();

        /// @author Zelie
        /// @brief _keypad function
        /// @param WINDOW *win
        /// @param bool bf
        /// @return void
        static void _keypad(WINDOW *, bool);

        /// @author Zelie
        /// @brief _curs_set function
        /// @param int visibility
        /// @return void
        static void _curs_set(int);

        /// @author Zelie
        /// @brief _mvaddch function
        /// @param int x
        /// @param int y
        /// @param unsigned int ch
        /// @return int
        static int _mvaddch(int, int, unsigned int);

        /// @author Zelie
        /// @brief _mvaddstr function
        /// @param int x
        /// @param int y
        /// @param const char *str
        static int _mvaddstr(int, int, const char *);
    private:
    public:
    // Exception Class:
    class NcursesException : public std::exception {
        public:

            /// @author Zelie
            /// @brief NcursesException constructor
            /// @param const std::string &message
            explicit NcursesException(const std::string &message);

            /// @author Zelie
            /// @brief what function
            /// @param void
            /// @return const char *
            const char *what() const noexcept override;
        protected:
        private:
            std::string _message;
    };
};

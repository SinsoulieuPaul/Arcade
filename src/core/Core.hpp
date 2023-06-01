/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Core
*/


#ifndef CORE_HPP_
#define CORE_HPP_

#include "../lib/games/AGame.hpp"
#include "../lib/graphical/IDisplayModule.hpp"
#include <exception>
#include <iostream>
#include <dlfcn.h>
#include <filesystem>
#include <chrono>
#include <fstream>
#include <unistd.h>// REMOVE AFTER
#include "../lib/games/Text.hpp"
#include "../lib/games/Entity.hpp"
#include "../lib/games/Prop.hpp"

class Core {
    public:
        /// @author Louis
        /// @brief Core constructor
        /// @param int argc
        /// @param char **argv
        Core(int, char **);

        /// @author Louis
        /// @brief Core destructor
        /// @param void
        ~Core();
        class CoreException : public std::exception {
            public:
                /// @author Louis
                /// @brief CoreException constructor
                /// @param message
                CoreException(const std::string &message) : _message(message) {};

                /// @author Louis
                /// @brief what function
                /// @param void
                /// @return const char *
                const char *what() const noexcept override { return _message.c_str(); };
            protected:
            private:
                std::string _message;
        };

    protected:
    private:
        /// @author Louis
        /// @brief _loadLibs function
        /// @param void
        /// @return void
        void _loadLibs();

        /// @author Louis
        /// @brief _loadGraphLib function
        /// @param std::string *lib
        /// @return void
        void _loadGraphLib(std::string *);

        /// @author Louis
        /// @brief _chooseLibs function
        /// @param std::string *lib
        /// @return void
        void _chooseLibs(std::string *);

        /// @author Zelie
        /// @brief _createGameMenu function
        /// @param void
        /// @return void
        void _createGameMenu();

        // int _menu();

        /// @author Zelie
        /// @brief _createMenu function
        /// @param void
        /// @return void
        void _createMenu();

        /// @author Zelie
        /// @brief _runMenu function
        /// @param void
        /// @return void
        void _runMenu();

        /// @author Louis
        /// @brief _changeGraphLib function
        /// @param void
        /// @return void
        void _changeGraphLib();

        /// @author Louis
        /// @brief _changeGameLib function
        /// @param std::string *lib
        /// @return void
        void _changeGameLib(std::string *);

        /// @author Louis
        /// @brief _createGame function
        /// @return void
        void _createGame();

        /// @author Zelie
        /// @brief setGameIndex function
        /// @param int index
        /// @return void
        void setGameIndex(int);

        /// @author Zelie
        /// @brief setGraphicalIndex function
        /// @param int index
        /// @return void
        void setGraphicalIndex(int);

        /// @author Louis
        /// @brief _runGame function
        /// @param void
        /// @return void
        void _runGame();

        std::string libPath = "./lib/";
        std::vector<std::string> _gameLibs;
        std::vector<std::string> _graphLibs;
        std::vector<std::string> _gameFounds;
        std::vector<std::string> _graphFounds;
        std::shared_ptr<IDispModule> (*_createLib)();
        std::shared_ptr<IDispModule> _module;
        std::shared_ptr<IGameModule> (*_gameLib)();
        std::shared_ptr<IGameModule> _game;
        int _gameIndex;
        int _graphicalIndex;
        bool _reloaded;
};

#endif /* !CORE_HPP_ */

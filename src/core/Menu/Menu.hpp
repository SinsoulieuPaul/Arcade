/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "../../lib/games/AGame.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

class Menu : public AGame {
    public:
        /// @author Zelie
        /// @brief Menu constructor
        /// @param void
        Menu();

        /// @author Zelie
        /// @brief Menu destructor
        /// @param void
        ~Menu();

        State systemInit() override;
        void systemOnUserInput(int) override;
        State systemStop() override;
        std::vector<Text *> textGetAll() override;
        std::vector<Prop *> propGetAll() override;

        int getScore() const;
        void setScore(int);
        void setHighScore(int);
        int getHighScore() const;
    protected:
        /// @author Zelie
        /// @brief _initMenu function
        /// @param void
        /// @return void
        void _initMenu();

        int _index;
        float _i;
        State _state;
        std::vector<Text *> _texts;
        std::vector<Prop *> _props;
        std::string libPath = "./lib/";
        std::vector<std::string> _gameLibs;
        std::vector<std::string> _graphLibs;
        std::vector<std::string> _gameFounds;
        std::vector<std::string> _graphFounds;
    private:
};

#endif /* !MENU_HPP_ */

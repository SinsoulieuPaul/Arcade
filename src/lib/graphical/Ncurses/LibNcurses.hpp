/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** LibNcurses
*/

#ifndef LIBNCURSES_HPP_
    #define LIBNCURSES_HPP_

#include "../IDisplayModule.hpp"
#include "Ncurses.hpp"

class LibNcurses : public IDispModule {
    public:
        LibNcurses();
        LibNcurses(int, int);
        ~LibNcurses();
        bool initScreen() override;
        bool display() override;
        Key getUserInput() override;
        void setUserInput(Key) override;
        bool drawEntity(Entity *) override;
        bool drawEntity(std::vector<Entity *>) override;
        bool drawProp(Prop *) override;
        bool drawProp(std::vector<Prop *>) override;
        bool drawText(Text *) override;
        bool drawText(std::vector<Text *>) override;
        bool clearAll() override;
        bool clearEntity() override;
        bool clearEntity(Id) override;
        bool clearEntity(std::vector<Id>) override;
        bool clearProp(Id) override;
        bool clearProp(std::vector<Id>) override;
        bool clearText(Id) override;
        bool clearText(std::vector<Id>) override;

        bool addText(Text *) override;
        bool addEntity(Entity *) override;
        bool addProp(Prop *) override;

        bool changeScore(int add) override;
        int getScore() override;
        int getHighScore() override;
        bool setScore(int score) override;
        bool setHighScore(int score) override;
        bool writeScore() override;

        bool destroyScreen() override;
        // Clear & draw
        bool update() override;
        bool updateEntity(Id, Entity *) override;
        bool updateEntity(std::vector<std::pair<Id, Entity *>>) override;
        std::vector<Entity *> getEntities() override;
        bool updateProp(Id, Prop *) override;
        bool updateProp(std::vector<std::pair<Id, Prop *>>) override;
        bool updateText(Id, Text *) override;
        bool updateText(std::vector<std::pair<Id, Text *>>) override;
        // Puterror
        bool displayError() override;
        bool sceneSwitch() override;
        // Useless
        int getFPS() override;
        void setKey();

        // check if lib works
        // Useless
        bool debug() override;
        std::vector<float> getRes() override;
        std::vector<float> getSize() override;
    protected:
        int _x;
        int _y;
        std::vector<Entity *> _entities;
        std::vector<Prop *> _props;
        std::vector<Text *> _texts;
        WINDOW *_win;
        Key _key;
        int _score;
        int _highScore;
    private:
    public:
    // Exception Class:
    class LibNcursesException : public std::exception {
        public:
            /// @author Zelie
            /// @brief LibNcursesException constructor
            /// @param std::string &message
            explicit LibNcursesException(const std::string &message);

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

#endif /* !LIBNCURSES_HPP_ */

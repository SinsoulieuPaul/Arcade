/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** LibSfml
*/

#ifndef LIBSFML_HPP_
    #define LIBSFML_HPP_

#include "../IDisplayModule.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class LibSfml : public IDispModule {
    public:
        class LibSfmlException : public std::exception {
            public:
                explicit LibSfmlException(const std::string &message, const std::string &component = "Unknown");
                const char *what() const noexcept override;
            protected:
            private:
                std::string _message;
        };

        LibSfml() ;
        ~LibSfml();

        // -- IDisplayModule --

        bool initScreen() override;
        bool display() override;
        bool destroyScreen() override {
            _destroyScreen();
            return true;
        }
        Key getUserInput() override;
        void setUserInput(Key) override;
        bool drawEntity(Entity *) override;
        bool drawEntity(std::vector<Entity *>) override;
        bool drawProp(Prop *) override;
        bool drawProp(std::vector<Prop *>) override;
        bool drawText(Text *);
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

        bool changeScore(int score) override;
        int getScore() override;
        int getHighScore() override;
        bool setScore(int score) override;
        bool setHighScore(int score) override;
        bool writeScore() override;

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
        // check if lib works
        // Useless
        bool debug() override;
        std::vector<float> getRes() override;
        std::vector<float> getSize() override;

    protected:
    private:
        // Functions

        /// @author Paul
        /// @brief destroyScreen function
        /// @param void
        /// @return void
        void _destroyScreen();

        /// @author Paul
        /// @brief setKey function
        /// @param sf::Keyboard::Key key
        /// @return void
        void setKey(sf::Keyboard::Key key);

        /// @author Paul
        /// @brief createFont function
        /// @param const char *file
        /// @return sf::Font *
        sf::Font *createFont(const char *file);

        /// @author Paul
        /// @brief createRect function
        /// @param int x
        /// @param int y
        /// @param int w
        /// @param int h
        /// @return sf::IntRect
        sf::IntRect createRect(int x, int y, int w, int h);

        /// @author Paul
        /// @brief createTexture function
        /// @param std::string *file
        /// @return sf::Texture *
        sf::Texture *createTexture(std::string *file);

        /// @author Paul
        /// @brief createSprite function
        /// @param sf::Texture *texture
        /// @return sf::Sprite *
        sf::Sprite *createSprite(sf::Texture *texture);

        /// @author Paul
        /// @brief createSprite function
        /// @param sf::Texture *texture
        /// @param sf::IntRect rect
        /// @return sf::Sprite *
        sf::Sprite *createSprite(sf::Texture *texture, sf::IntRect rect);

        /// @author Paul
        /// @brief createText function
        /// @param const char *text
        /// @param sf::Font *font
        /// @param int size
        /// @param sf::Color color
        sf::Text *createText(const char *text, sf::Font *font, int size, sf::Color color);

        /// @author Paul
        /// @brief drawSprite function
        /// @param std::string *path
        /// @param sf::Vector2f pos
        /// @return bool
        bool drawSprite(std::string *path, sf::Vector2f pos, float rotation = 0);

        // Variables
        sf::RenderWindow *_win;
        std::vector<Text *> _texts;
        std::map<Text *, sf::Text *> _sfTexts;
        std::vector<Entity *> _entities;
        std::vector<Prop *> _props;
        std::map<std::string *, sf::Sprite *> _sprites;
        int _score = 0;
        int _highScore = 0;
        sf::Font *_font;
        bool _running;
        Key _key;
};

#endif /* !LIBSFML_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** LibSdl
*/

#ifndef LIBSDL_HPP_
    #define LIBSDL_HPP_

#include "../IDisplayModule.hpp"
#include "SDL.hpp"

class LibSdl : public IDispModule {
    public:
        enum Color {
            RED = 0xFF0000,
            GREEN = 0x00FF00,
            BLUE = 0x0000FF,
            YELLOW = 0xFFFF00,
            CYAN = 0x00FFFF,
            MAGENTA = 0xFF00FF,
            BLACK = 0x000000,
            WHITE = 0xFFFFFF
        };

        class LibSdlException : public std::exception {
            public:
                explicit LibSdlException(const std::string &message, const std::string &component = "Unknown");
                const char *what() const noexcept override;
            protected:
            private:
                std::string _message;
        };

        LibSdl();
        ~LibSdl();

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

        bool changeScore(int add) override;
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
        /// @brief initRender function
        /// @param void
        /// @return void
        void initRender();

        /// @author Paul
        /// @brief destroyRender function
        /// @param void
        /// @return void
        void destroyRender();

        /// @author Paul
        /// @brief renderPresent function
        /// @param void
        /// @return void
        void renderPresent();

        /// @author Paul
        /// @brief renderClear function
        /// @param void
        /// @return void
        void renderClear();

        /// @author Paul
        /// @brief setKey function
        /// @param sf::Keyboard::Key key
        /// @return void
        void setKey(SDL_Keycode key);

        /// @author Paul
        /// @brief createFont function
        /// @param const char *file
        /// @param int size
        /// @return TTF_Font *
        TTF_Font *createFont(const char *file, int size);

        /// @author Paul
        /// @brief destroyFont function
        /// @param TTF_Font *font
        /// @return void
        void destroyFont(TTF_Font *font);

        /// @author Paul
        /// @brief drawPixel function
        /// @param int x
        /// @param int y
        /// @param Color color
        void drawPixel(int x, int y, Color color);

        /// @author Paul
        /// @brief drawPixel function
        /// @param int x
        /// @param int y
        /// @param const SDL_Color &color
        void drawPixel(int x, int y, const SDL_Color &color);

        /// @author Paul
        /// @brief createRect function
        /// @param int x
        /// @param int y
        /// @param int w
        /// @param int h
        /// @return SDL_Rect
        SDL_Rect createRect(int x, int y, int w, int h);

        /// @author Paul
        /// @brief drawwTextures function
        /// @param std::string *path
        /// @param float y
        /// @param float x
        /// @return bool
        bool drawTextures(std::string *path, float y, float x, float rotation = 0);

        /// @author Paul
        /// @brief createTexture function
        /// @param SDL_Surface *surface
        /// @return SDL_Texture *
        SDL_Texture *createTexture(SDL_Surface *surface);

        /// @author Paul
        /// @brief createTexture function
        /// @param std::string *file
        /// @return SDL_Texture *
        SDL_Texture *createTexture(std::string *file);

        /// @author Paul
        /// @brief drawTexture function
        /// @param SDL_Texture *texture
        /// @param SDL_Rect rect
        /// @return void
        void drawTexture(SDL_Texture *texture, SDL_Rect rect);

        /// @author Paul
        /// @brief destroyTexture function
        /// @param SDL_Texture *texture
        /// @return void
        void destroyTexture(SDL_Texture *texture);

        /// @author Paul
        /// @brief moveTexture function
        /// @param SDL_Texture *texture
        /// @param SDL_Rect rect
        /// @return void
        void moveTexture(SDL_Texture *texture, SDL_Rect rect);

        /// @author Paul
        /// @brief createSurface function
        /// @param std::string *file
        /// @return SDL_Surface *
        SDL_Surface *createSurface(std::string *file);

        /// @author Paul
        /// @brief destroySurface function
        /// @param SDL_Surface *surface
        /// @return void
        void destroySurface(SDL_Surface *surface);

        /// @author Paul
        /// @brief createTextSurface function
        /// @param const char *text
        /// @param const SDL_Color &color
        /// @param TTF_Font *font
        /// @return SDL_Surface *
        SDL_Surface *createTextSurface(const char *text, const SDL_Color &color, TTF_Font *font);

        /// @author Paul
        /// @brief createColor function
        /// @param int r
        /// @param int g
        /// @param int b
        /// @param int a
        /// @return SDL_Color
        SDL_Color createColor(int r, int g, int b, int a = 255);

        // Variables
        SDL_Window *_win;
        SDL_Renderer *_render;
        std::vector<Text *> _texts;
        std::map<Text *, std::pair<std::string *, std::pair<SDL_Texture *, SDL_Rect>>> _sdlTexts;
        std::vector<Entity *> _entities;
        std::vector<Prop *> _props;
        std::map<std::string *, std::pair<SDL_Texture *, SDL_Rect>> _textures;
        bool _running;
        Key _key;
        int _score = 0;
        int _highScore = 0;
        TTF_Font *_font;
};

#endif /* !LIBSdl_HPP_ */

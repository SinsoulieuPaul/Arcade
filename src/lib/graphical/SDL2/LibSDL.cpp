/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** LibSdl
*/

#include <iostream>
#include <fstream>
#include "LibSDL.hpp"

extern "C" std::shared_ptr<IDispModule> createLib()
{
    std::cout << "Creating LibSDL instance" << std::endl;
    return std::make_shared<LibSdl>();
}

/*==============/
/  Exceptions   /
/==============*/

/// @brief Constructor of the LibSdlException class
/// @param message The exception message
/// @param component The component that throw the exception
LibSdl::LibSdlException::LibSdlException(const std::string &message, const std::string &component)
{
    _message = "LibSdl: " + component + ": " + message;
}

/// @brief Return the exception message
/// @return The exception message
const char *LibSdl::LibSdlException::what() const noexcept
{
    return _message.c_str();
}

// Init and destroy

/*  @author Paul
    @brief LibSdl constructor
*/
LibSdl::LibSdl()
{
    _win = nullptr;
    _render = nullptr;
    if (Sdl::initSDL() < 0)
        throw LibSdlException("Failed to init SDL", "LibSdl");
    if (Sdl::initIMG() < 0)
        throw LibSdlException("Failed to init IMG", "LibSdl");
    if (Sdl::initTTF() < 0)
        throw LibSdlException("Failed to init TTF", "LibSdl");
}

/*  @author Paul
    @brief LibSdl destructor
*/
LibSdl::~LibSdl()
{
    if (_render != nullptr)
        destroyRender();
    if (_win != nullptr)
        _destroyScreen();
    Sdl::quitTTF();
    Sdl::quitIMG();
    Sdl::quitSDL();
}

// -- IDispModule

/*  @author Paul
    @brief initScreen function
    @param void
    @return bool
*/
bool LibSdl::initScreen()
{
    if (_win == nullptr)
        _win = Sdl::createWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if (_win == nullptr) {
        throw LibSdlException("Failed to create window", "initScreen");
        return false;
    }
    try {
        initRender();
    } catch (LibSdlException &e) {
        throw e.what();
        return false;
    }
    return true;
}

/*  @author Paul
    @brief display function
    @param void
    @return bool
*/
bool LibSdl::display()
{
    try {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                destroyScreen();
                return false;
            } else if (event.type == SDL_KEYDOWN) {
                setKey(event.key.keysym.sym);
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int left = 0;
                    int right = 120;
                    int up = 560;
                    int down = 600;

                    if (event.button.x >= left && event.button.x <= right && event.button.y >= up && event.button.y <= down)
                        setKey(SDLK_l);
                }
            }
        }

        renderClear();
        drawProp(_props);
        drawEntity(_entities);
        drawText(_texts);
        renderPresent();
    } catch (LibSdlException &e) {
        throw LibSdlException(e.what(), "display");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief setUserInput function
    @param Key key
    @return void
*/
void LibSdl::setUserInput(Key key)
{
    _key = key;
}

/*  @author Paul
    @brief setKey function
    @param SDL_KeyCode key
    @return void
*/
void LibSdl::setKey(SDL_Keycode key)
{
    switch (key) {
        case SDLK_UP:
            _key = Key::Z;
            break;
        case SDLK_DOWN:
            _key = Key::S;
            break;
        case SDLK_LEFT:
            _key = Key::Q;
            break;
        case SDLK_RIGHT:
            _key = Key::D;
            break;
        case SDLK_z:
            _key = Key::Z;
            break;
        case SDLK_s:
            _key = Key::S;
            break;
        case SDLK_q:
            _key = Key::Q;
            break;
        case SDLK_d:
            _key = Key::D;
            break;
        case SDLK_r:
            _key = Key::R;
            break;
        case SDLK_l:
            _key = Key::L;
            break;
        case SDLK_g:
            _key = Key::G;
            break;
        case SDLK_RETURN:
            _key = Key::Enter;
            break;
        case SDLK_RETURN2:
            _key = Key::Enter;
            break;
        case SDLK_ESCAPE:
            _key = Key::Escape;
            break;
        default:
            _key = Key::None;
            break;
    }
}

/*  @author Paul
    @brief getUserInput function
    @param void
    @return Key
*/
Key LibSdl::getUserInput()
{
    return _key;
}

/*  @author Paul
    @brief drawSprite function
    @param std::string *path
    @param float y
    @param float x
    @return bool
*/
bool LibSdl::drawTextures(std::string *path, float y, float x, float rotation)
{
    for (auto &texture : _textures) {
        if (*texture.first == *path) {
            texture.second.second.x = x;
            texture.second.second.y = y;
            SDL_Point center = {texture.second.second.w / 2, texture.second.second.h / 2};
            Sdl::renderCopyEx(_render, texture.second.first, nullptr, &texture.second.second, rotation, &center, SDL_FLIP_NONE);
            return true;
        }
    }
    return true;
}

/*  @author Paul
    @brief drawEntity function
    @param Entity *entity
    @return bool
*/
bool LibSdl::drawEntity(Entity *entity)
{
    std::string *path = entity->getSpritePath();

    if (path == nullptr) {
        throw LibSdlException("Failed to get sprite path", "drawEntity");
        return false;
    }
    float x = entity->getProperty(Position)[0];
    float y = entity->getProperty(Position)[1];

    drawTextures(path, y, x, entity->getProperty(Rotation)[0]);
    return true;
}

/*  @author Paul
    @brief drawEntity function
    @param std::vector<Entity *> entities
    @return bool
*/
bool LibSdl::drawEntity(std::vector<Entity *> entities)
{
    try {
        for (auto &entity : entities)
            drawEntity(entity);
    } catch (const std::exception &e) {
        throw LibSdlException(e.what());
        return false;
    }
    return true;
}

/*  @author Paul
    @brief drawProp function
    @param Prop *prop
    @return bool
*/
bool LibSdl::drawProp(Prop *prop)
{
    std::string *path = prop->getSpritePath();

    if (path == nullptr) {
        throw LibSdlException("Failed to get sprite path", "drawProp");
        return false;
    }
    float x = prop->getProperty(Position)[0];
    float y = prop->getProperty(Position)[1];
    drawTextures(path, y, x);
    return true;
}

/*  @author Paul
    @brief drawProp function
    @param std::vector<Prop *> props
    @return bool
*/
bool LibSdl::drawProp(std::vector<Prop *> props)
{
    try {
        for (auto &prop : props)
            drawProp(prop);
    } catch (const std::exception &e) {
        throw LibSdlException(e.what(), "drawProp");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief drawText function
    @param Text *text
    @return bool
*/
bool LibSdl::drawText(Text *text)
{
    try {
        for (auto &txt : _sdlTexts) {
            if (txt.first == text) {
                if (txt.second.first != text->getText()) {
                    txt.second.first = text->getText();
                    Sdl::destroyTexture(txt.second.second.first);

                    int size;

                    if (text->getType() == Score)
                        size = 35;
                    else
                        size = 20;

                    SDL_Surface *surface = createTextSurface(text->getText()->c_str(), createColor(255, 255, 255, 255), createFont(text->getFont()->c_str(), size));
                    txt.second.second.first = Sdl::createTextureFromSurface(_render, surface);
                }
                int x = text->getProperty(Position)[0];
                int y = text->getProperty(Position)[1];
                SDL_Rect rect = {x, y, txt.second.second.second.w, txt.second.second.second.h};
                Sdl::renderCopy(_render, txt.second.second.first, nullptr, &rect);
                return true;
            }
        }
    } catch (const std::exception &e) {
        throw LibSdlException(e.what(), "drawText");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief drawText function
    @param std::vector<Text *> texts
    @return bool
*/
bool LibSdl::drawText(std::vector<Text *> texts)
{
    try {
        for (auto &text : texts)
            drawText(text);
    } catch (const std::exception &e) {
        throw LibSdlException(e.what(), "drawText");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief addText function
    @param Text *text
    @return bool
*/
bool LibSdl::addText(Text *text)
{
    try {
        int size;

        if (text->getType() == Score)
            size = 35;
        else
            size = 20;
        TTF_Font *font = createFont(text->getFont()->c_str(), size);
        SDL_Surface *surface = createTextSurface(text->getText()->c_str(), createColor(255, 255, 255, 255), font);
        SDL_Texture *texture = Sdl::createTextureFromSurface(_render, surface);

        int x = text->getProperty(Position)[0];
        int y = text->getProperty(Position)[1];

        SDL_Rect rect = {x, y, surface->w, surface->h};
        _sdlTexts[text] = std::make_pair(text->getText(), std::make_pair(texture, rect));

        _texts.push_back(text);
    } catch (const std::exception &e) {
        throw LibSdlException(e.what(), "addText");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief addEntity function
    @param Entity *entity
    @return bool
*/
bool LibSdl::addEntity(Entity *entity)
{
    try {
        SDL_Texture *texture = createTexture(entity->getSpritePath());
        int x = entity->getProperty(Position)[0];
        int y = entity->getProperty(Position)[1];
        int w;
        int h;

        Sdl::queryTexture(texture, NULL, NULL, &w, &h);
        SDL_Rect rect = {x, y, w * 2, h * 2};

        _textures[entity->getSpritePath()] = std::make_pair(texture, rect);
        _entities.push_back(entity);
    } catch (const std::exception &e) {
        throw LibSdlException(e.what(), "addEntity");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief addProp function
    @param Prop *prop
    @return bool
*/
bool LibSdl::addProp(Prop *prop)
{
    try {
        SDL_Texture *texture = createTexture(prop->getSpritePath());
        int w;
        int h;

        Sdl::queryTexture(texture, NULL, NULL, &w, &h);
        SDL_Rect rect = {0, 0, w * 2, h * 2};

        _textures[prop->getSpritePath()] = std::make_pair(texture, rect);
        _props.push_back(prop);
    } catch (const std::exception &e) {
        throw LibSdlException(e.what(), "addProp");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief changeScore function
    @param int add
    @return bool
*/
bool LibSdl::changeScore(int add)
{
    _score += add;
    std::string *newText = new std::string("Score: " + std::to_string(_score));

    for (auto &it : _texts) {
        if (it->getType() == Score) {
            it->setText(newText);
            if (_score > _highScore) {
                _highScore = _score;
                writeScore();
            }
            return true;
        }
    }
    return false;
}

/*  @author Paul
    @brief getScore function
    @param void
    @return int
*/
int LibSdl::getScore()
{
    return _score;
}

/*  @author Paul
    @brief getHighScore function
    @param void
    @return int
*/
int LibSdl::getHighScore()
{
    return _highScore;
}

/*  @author Paul
    @brief setScore function
    @param int score
    @return bool
*/
bool LibSdl::setScore(int score)
{
    _score = score;
    if (_score > _highScore) {
        std::cout << "Score: " << _score << " Highscore: " << _highScore << std::endl;
        writeScore();
        _highScore = _score;
    }
    return true;
}

bool LibSdl::setHighScore(int score)
{
    _highScore = score;
    return true;
}

/*  @author Paul
    @brief writeScore function
    @param void
    @return bool
*/
bool LibSdl::writeScore()
{
    std::ofstream file;
    std::string *line = new std::string(std::to_string(_score));

    file.open("score.txt");
    if (!file.is_open()) {
        file.open("score.txt", std::ios::out);
        if (!file.is_open())
            return false;
    }
    file << *line;
    file.close();
    return true;
}

/*  @author Paul
    @brief clearAll function
    @param void
    @return bool
*/
bool LibSdl::clearAll()
{
    if (!(_entities.empty()))
        _entities.clear();
    if (!(_props.empty()))
        _props.clear();
    if (!(_texts.empty()))
        _texts.clear();
    return true;
}

/*  @author Paul
    @brief clearEntity function
    @param void
    @return bool
*/
bool LibSdl::clearEntity()
{
    if (!(_entities.empty())) {
        for (auto &it : _entities) {
            _textures.erase(it->getSpritePath());
        }
        _entities.clear();
    }
    return true;
}

/*  @author Paul
    @brief clearEntity function
    @param Id id
    @return bool
*/
bool LibSdl::clearEntity([[maybe_unused]] Id id)
{
    return true;
}

/*  @author Paul
    @brief clearEntity function
    @param std::vector<Id> ids
    @return bool
*/
bool LibSdl::clearEntity([[maybe_unused]] std::vector<Id> ids)
{
    return true;
}

/*  @author Paul
    @brief clearProp function
    @param Id id
    @return bool
**/
bool LibSdl::clearProp([[maybe_unused]] Id id)
{
    return true;
}

/*  @author Paul
    @brief clearProp function
    @param std::vector<Id> ids
    @return bool
*/
bool LibSdl::clearProp([[maybe_unused]] std::vector<Id> ids)
{
    return true;
}

/*  @author Paul
    @brief clearText function
    @param Id id
    @return bool
*/
bool LibSdl::clearText([[maybe_unused]] Id id)
{
    return true;
}

/*  @author Paul
    @brief clearText function
    @param std::vector<Id> ids
    @return bool
*/
bool LibSdl::clearText([[maybe_unused]] std::vector<Id> ids)
{
    return true;
}

/*  @author Paul
    @brief update function
    @param void
    @return bool
*/
bool LibSdl::update()
{
    return true;
}

/*  @author Paul
    @brief updateEntity function
    @param Id id
    @param Entity *entity
    @return bool
*/
bool LibSdl::updateEntity([[maybe_unused]] Id id, [[maybe_unused]] Entity *entity)
{
    return true;
}

/*  @author Paul
    @brief updateEntity function
    @param std::vector<std::pair<Id, Entity *>> entities
    @return bool
*/
bool LibSdl::updateEntity([[maybe_unused]] std::vector<std::pair<Id, Entity *>> entities)
{
    return true;
}

/*  @author Paul
    @brief updateProp function
    @param Id id
    @param Prop *prop
    @return bool
*/
bool LibSdl::updateProp([[maybe_unused]] Id id, [[maybe_unused]] Prop *prop)
{
    return true;
}

/*  @author Paul
    @brief getEntities function
    @param void
    @return std::vector<Entity *>
*/
std::vector<Entity *> LibSdl::getEntities()
{
    return _entities;
}

/*  @author Paul
    @brief updateProp function
    @param std::vector<std::pair<Id, Prop *>> props
    @return bool
*/
bool LibSdl::updateProp([[maybe_unused]] std::vector<std::pair<Id, Prop *>> props)
{
    return true;
}

/*  @author Paul
    @brief updateText function
    @param Id id
    @param Text *text
    @return bool
*/
bool LibSdl::updateText([[maybe_unused]] Id id, [[maybe_unused]] Text *text)
{
    return true;
}

/*  @author Paul
    @brief updateText function
    @param std::vector<std::pair<Id, Text *>> texts
    @return bool
*/
bool LibSdl::updateText([[maybe_unused]] std::vector<std::pair<Id, Text *>> texts)
{
    return true;
}

/*  @author Paul
    @brief displayError function
    @param void
    @return bool
*/
bool LibSdl::displayError()
{
    return true;
}

/*  @author Paul
    @brief sceneSwitch function
    @param void
    @return bool
*/
bool LibSdl::sceneSwitch()
{
    return true;
}

/*  @author Paul
    @brief getFPS function
    @param void
    @return int
*/
int LibSdl::getFPS()
{
    return 0;
}

/*  @author Paul
    @brief debug function
    @param void
    @return bool
*/
bool LibSdl::debug()
{
    return true;
}

/*  @author Paul
    @brief getRes function
    @param void
    @return std::vector<float>
*/
std::vector<float> LibSdl::getRes()
{
    return std::vector<float>();
}

/*  @author Paul
    @brief getSize function
    @param void
    @return std::vector<float>
*/
std::vector<float> LibSdl::getSize()
{
    return std::vector<float>();
}

// -- LibSdl

// Window (Screen)

/*  @author Paul
    @brief destroyScreen function
    @param void
    @return void
*/
void LibSdl::_destroyScreen()
{
    Sdl::destroyWindow(_win);
}

// Renderer
//  - Init and destroy

/*  @author Paul
    @brief initRender function
    @param void
    @return void
*/
void LibSdl::initRender()
{
    if (_render == nullptr)
        _render = Sdl::createRenderer(_win, -1, SDL_RENDERER_ACCELERATED);

    if (_render == nullptr)
        throw LibSdlException("Failed to create renderer", "initRender");
}

/*  @author Paul
    @brief destroyRender function
    @param void
    @return void
*/
void LibSdl::destroyRender()
{
    Sdl::destroyRenderer(_render);
}

// - Present and clear

/*  @author Paul
    @brief renderClear function
    @param void
    @return void
*/
void LibSdl::renderClear()
{
    Sdl::renderClear(_render);
}

// Rect

/*  @author Paul
    @brief createRect function
    @param int x
    @param int y
    @param int w
    @param int h
    @return SDL_Rect
*/
SDL_Rect LibSdl::createRect(int x, int y, int w, int h)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    return rect;
}

// Texture

/*  @author Paul
    @brief createTexture function
    @param SDL_Surface *surface
    @return SDL_Texture *
*/
SDL_Texture *LibSdl::createTexture(SDL_Surface *surface)
{
    SDL_Texture *texture = Sdl::createTextureFromSurface(_render, surface);

    if (texture == nullptr)
        throw LibSdlException("Failed to create texture from surface", "createTexture");
    return texture;
}

/*  @author Paul
    @brief createTexture function
    @param string *path
    @return SDL_Texture *
*/
SDL_Texture *LibSdl::createTexture(std::string *path)
{
    SDL_Texture *texture = Sdl::loadTexture(_render, path->c_str());

    if (texture == nullptr)
        throw LibSdlException("Failed to create texture from surface", "createTexture");
    return texture;
}

/*  @author Paul
    @brief drawTexture function
    @param SDL_Texture *texture
    @param SDL_Rect rect
    @return void
*/
void LibSdl::drawTexture(SDL_Texture *texture, SDL_Rect rect)
{
    Sdl::renderCopy(_render, texture, nullptr, &rect);
}

/*  @brief destroyTexture function
    @param SDL_Texture *texture
    @return void
*/
void LibSdl::destroyTexture(SDL_Texture *texture)
{
    Sdl::destroyTexture(texture);
}

// Surface

/*  @author Paul
    @brief createSurface function
    @param const char *path
    @return SDL_Surface *
*/
SDL_Surface *LibSdl::createSurface(std::string *path)
{
    SDL_Surface *surface = Sdl::loadIMG(path->c_str());

    if (surface == nullptr)
        throw LibSdlException("Failed to load surface", "createSurface");
    return surface;
}

/*  @brief destroySurface function
    @param SDL_Surface *surface
    @return void
*/
void LibSdl::destroySurface(SDL_Surface *surface)
{
    Sdl::freeSurface(surface);
}

// Display / Draw

/*  @author Paul
    @brief display function
    @param void
    @return void
*/
void LibSdl::renderPresent()
{
    Sdl::renderPresent(_render);
}

// Draw

/*  @author Paul
    @brief drawRect function
    @param SDL_Rect rect
    @param SDL_Color color
    @return void
*/
void LibSdl::drawPixel(int x, int y, Color color)
{
    int r = (color >> 16) & 0xFF;
    int g = (color >> 8) & 0xFF;
    int b = color & 0xFF;
    int a = 0xFF;
    SDL_Color sdlColor = createColor(r, g, b, a);

    drawPixel(x, y, sdlColor);
}

/*  @author Paul
    @brief drawRect function
    @param SDL_Rect rect
    @param SDL_Color color
    @return void
*/
void LibSdl::drawPixel(int x, int y, const SDL_Color &color)
{
    Sdl::setRenderDrawColor(_render, color.r, color.g, color.b, color.a);
    Sdl::renderDrawPoint(_render, x, y);
}

/*  @author Paul
    @brief createColor function
    @param int r
    @param int g
    @param int b
    @param int a
    @return SDL_Color
*/
SDL_Color LibSdl::createColor(int r, int g, int b, int a)
{
    SDL_Color color;

    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

/*  @author Paul
    @brief createFont function
    @param const char *path
    @param int size
    @return TTF_Font *
*/
TTF_Font *LibSdl::createFont(const char *path, int size)
{
    TTF_Font *font = Sdl::openFont(path, size);

    if (font == nullptr)
        throw LibSdlException("Failed to load font", "createFont");
    return font;
}

/*  @brief destroyFont function
    @param TTF_Font *font
    @return void
*/
void LibSdl::destroyFont(TTF_Font *font)
{
    Sdl::closeFont(font);
}

/*  @author Paul
    @brief createTextSurface function
    @param const char *text
    @param const SDL_Color &color
    @param TTF_Font *font
    @return SDL_Surface *
*/
SDL_Surface *LibSdl::createTextSurface(const char *text, const SDL_Color &color, TTF_Font *font)
{
    SDL_Surface *surface = Sdl::renderText_Solid(font, text, color);

    if (surface == nullptr)
        throw LibSdlException("Failed to create text surface", "createTextSurface");
    return surface;
}

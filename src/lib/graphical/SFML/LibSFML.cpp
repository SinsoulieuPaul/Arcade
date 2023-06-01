/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** LibSfml
*/

#include <iostream>
#include <fstream>
#include "LibSFML.hpp"

extern "C" std::shared_ptr<IDispModule> createLib()
{
    std::cout << "Creating LibSfml instance" << std::endl;
    return std::make_shared<LibSfml>();
}

/*==============/
/  Exceptions   /
/==============*/

/// @brief Constructor of the LibSfmlException class
/// @param message The exception message
/// @param component The component that throw the exception
LibSfml::LibSfmlException::LibSfmlException(const std::string &message, const std::string &component)
{
    _message = "LibSfml: " + component + ": " + message;
}

/// @brief Return the exception message
/// @return The exception message
const char *LibSfml::LibSfmlException::what() const noexcept
{
    return _message.c_str();
}

// Init and destroy

/*  @author Paul
    @brief LibSfml constructor
*/
LibSfml::LibSfml()
{
    _win = nullptr;
    _score = 0;
    _key = Key::None;
}

/*  @author Paul
    @brief LibSfml destructor
*/
LibSfml::~LibSfml()
{
}

// -- IDispModule

/*  @author Paul
    @brief initScreen function
    @param void
    @return bool
*/
bool LibSfml::initScreen()
{
    if (_win != nullptr) {
        return true;
    }
    _win = new sf::RenderWindow(sf::VideoMode(800, 600), "Arcade");
    if (_win == nullptr) {
        throw LibSfmlException("Failed to create window", "initScreen");
        return false;
    }
    _win->setFramerateLimit(60);

    _key = Key::None;
    _score = 0;
    return true;
}

/*  @author Paul
    @brief display function
    @param void
    @return bool
*/
bool LibSfml::display()
{
    try {
        sf::Event event;
        while (_win->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                destroyScreen();
                return false;
            } else if (event.type == sf::Event::KeyPressed) {
                setKey(event.key.code);
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int left = 0;
                    int right = 120;
                    int up = 560;
                    int down = 600;

                    if (event.mouseButton.x >= left and event.mouseButton.x <= right and
                        event.mouseButton.y >= up and event.mouseButton.y <= down) {
                        _key = L;
                    }
                }
            }
        }
        _win->clear();
        drawProp(_props);
        drawEntity(_entities);
        drawText(_texts);
        _win->display();
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what(), "display");
        return false;
    }
    return true;
}

void LibSfml::setUserInput(Key key)
{
    _key = key;
}

void LibSfml::setKey(sf::Keyboard::Key key)
{
    switch (key) {
        case sf::Keyboard::Up:
            _key = Key::Z;
            break;
        case sf::Keyboard::Down:
            _key = Key::S;
            break;
        case sf::Keyboard::Left:
            _key = Key::Q;
            break;
        case sf::Keyboard::Right:
            _key = Key::D;
            break;
        case sf::Keyboard::Z:
            _key = Key::Z;
            break;
        case sf::Keyboard::S:
            _key = Key::S;
            break;
        case sf::Keyboard::Q:
            _key = Key::Q;
            break;
        case sf::Keyboard::D:
            _key = Key::D;
            break;
        case sf::Keyboard::R:
            _key = Key::R;
            break;
        case sf::Keyboard::L:
            _key = Key::L;
            break;
        case sf::Keyboard::G:
            _key = Key::G;
            break;
        case sf::Keyboard::Enter:
            _key = Key::Enter;
            break;
        case sf::Keyboard::Escape:
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
Key LibSfml::getUserInput()
{
    return _key;
}

/*  @author Paul
    @brief drawSprite function
    @param std::string *path
    @param sf::Vector2f pos
    @return bool
*/
bool LibSfml::drawSprite(std::string *path, sf::Vector2f pos, float rotation)
{
    for (auto &sprite : _sprites) {
        if (*sprite.first == *path) {
            sprite.second->setPosition(pos);
            sprite.second->setRotation(rotation);
            _win->draw(*sprite.second);
            return true;
        }
    }
    return false;
}

/*  @author Paul
    @brief drawEntity function
    @param Entity *entity
    @return bool
*/
bool LibSfml::drawEntity(Entity *entity)
{
    std::string *path = entity->getSpritePath();

    if (path == nullptr) {
        throw LibSfmlException("Failed to get sprite path", "drawEntity");
        return false;
    }

    sf::Vector2f pos;

    pos.x = entity->getProperty(Position)[0];
    pos.y = entity->getProperty(Position)[1];

    drawSprite(path, pos, entity->getProperty(Rotation)[0]);
    return true;
}

/*  @author Paul
    @brief drawEntity function
    @param std::vector<Entity *> entities
    @return bool
*/
bool LibSfml::drawEntity(std::vector<Entity *> entities)
{
    try {
        for (auto &entity : entities)
            drawEntity(entity);
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what());
        return false;
    }
    return true;
}

/*  @author Paul
    @brief drawProp function
    @param Prop *prop
    @return bool
*/
bool LibSfml::drawProp(Prop *prop)
{
    std::string *path = prop->getSpritePath();


    if (path == nullptr) {
        throw LibSfmlException("Failed to get sprite path", "drawProp");
        return false;
    }
    sf::Vector2f pos;

    pos.x = prop->getProperty(Position)[0];
    pos.y = prop->getProperty(Position)[1];

    drawSprite(path, pos);
    return true;
}

/*  @author Paul
    @brief drawProp function
    @param std::vector<Prop *> props
    @return bool
*/
bool LibSfml::drawProp(std::vector<Prop *> props)
{
    try {
        for (auto &prop : props)
            drawProp(prop);
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what());
        return false;
    }
    return true;
}

/*  @author Paul
    @brief drawText function
    @param Text *text
    @return bool
*/
bool LibSfml::drawText(Text *text)
{
    sf::Vector2f pos;

    pos.x = text->getProperty(Position)[0];
    pos.y = text->getProperty(Position)[1];

    for (auto &textSfml : _sfTexts) {
        if (textSfml.first == text) {
            textSfml.second->setPosition(pos);
            if (textSfml.second->getString() != *text->getText())
                textSfml.second->setString(*text->getText());
            _win->draw(*textSfml.second);
            return true;
        }
    }
    return true;
}

/*  @author Paul
    @brief drawText function
    @param std::vector<Text *> texts
    @return bool
*/
bool LibSfml::drawText(std::vector<Text *> texts)
{
    try {
        for (auto &text : texts)
            drawText(text);
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what());
        return false;
    }
    return true;
}

/*  @author Louis
    @brief addText function
    @param Text *text
    @return bool
*/

bool LibSfml::addText(Text *text)
{
    try {
        int size;

        if (text->getType() == Score)
            size = 35;
        else
            size = 20;
        sf::Font *font = createFont(text->getFont()->c_str());
        sf::Text *textSfml = createText(text->getText()->c_str(), font, size, sf::Color::White);

        _texts.push_back(text);
        _sfTexts[text] = textSfml;
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what());
        return false;
    }
    return true;
}

/*  @author Paul
    @brief addEntity function
    @param Entity *entity
    @return bool
*/
bool LibSfml::addEntity(Entity *entity)
{
    try {
        sf::Texture *texture = createTexture(entity->getSpritePath());
        sf::Sprite *sprite = createSprite(texture);
        sprite->setScale(2, 2);

        _sprites[entity->getSpritePath()] = sprite;
        _entities.push_back(entity);
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what());
        return false;
    }
    return true;
}

/*  @author Paul
    @brief addProp function
    @param Prop *prop
    @return bool
*/
bool LibSfml::addProp(Prop *prop)
{
    if (prop->getSpritePath() == nullptr || prop->getSpritePath()->empty())
        return false;

    try {
        sf::Texture *texture = createTexture(prop->getSpritePath());
        sf::Sprite *sprite = createSprite(texture);

        sprite->setScale(2, 2);
        _sprites[prop->getSpritePath()] = sprite;
        _props.push_back(prop);
    } catch (const std::exception &e) {
        throw LibSfmlException(e.what());
        return false;
    }
    return true;
}

/*  @author Paul
    @brief ² function
    @param void
    @return bool
*/
bool LibSfml::clearAll()
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
bool LibSfml::clearEntity()
{
    if (!(_entities.empty())) {
        for (auto &it : _entities) {
            _sprites.erase(it->getSpritePath());
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
bool LibSfml::clearEntity([[maybe_unused]] Id id)
{
    return true;
}

/*  @author Paul
    @brief clearEntity function
    @param std::vector<Id> ids
    @return bool
*/
bool LibSfml::clearEntity([[maybe_unused]] std::vector<Id> ids)
{
    return true;
}

/*  @author Paul
    @brief clearProp function
    @param Id id
    @return bool
**/
bool LibSfml::clearProp([[maybe_unused]] Id id)
{
    return true;
}

/*  @author Paul
    @brief clearProp function
    @param std::vector<Id> ids
    @return bool
*/
bool LibSfml::clearProp([[maybe_unused]] std::vector<Id> ids)
{
    return true;
}

/*  @author Paul
    @brief clearText function
    @param Id id
    @return bool
*/
bool LibSfml::clearText([[maybe_unused]] Id id)
{
    return true;
}

/*  @author Paul
    @brief clearText function
    @param std::vector<Id> ids
    @return bool
*/
bool LibSfml::clearText([[maybe_unused]] std::vector<Id> ids)
{
    return true;
}

/*  @author Paul
    @brief update function
    @param void
    @return bool
*/
bool LibSfml::update()
{
    return true;
}

/*  @author Paul
    @brief updateEntity function
    @param Id id
    @param Entity *entity
    @return bool
*/
bool LibSfml::updateEntity([[maybe_unused]] Id id, [[maybe_unused]] Entity *entity)
{
    return true;
}

/*  @author Paul
    @brief updateEntity function
    @param std::vector<std::pair<Id, Entity *>> entities
    @return bool
*/
bool LibSfml::updateEntity([[maybe_unused]] std::vector<std::pair<Id, Entity *>> entities)
{
    return true;
}

/*  @author Paul
    @brief getEntities function
    @param void
    @return std::vector<Entity *>
*/
std::vector<Entity *> LibSfml::getEntities()
{
    return _entities;
}

/*  @author Paul
    @brief updateProp function
    @param Id id
    @param Prop *prop
    @return bool
*/
bool LibSfml::updateProp([[maybe_unused]] Id id, [[maybe_unused]] Prop *prop)
{
    return true;
}

/*  @author Paul
    @brief updateProp function
    @param std::vector<std::pair<Id, Prop *>> props
    @return bool
*/
bool LibSfml::updateProp([[maybe_unused]] std::vector<std::pair<Id, Prop *>> props)
{
    return true;
}

/*  @author Paul
    @brief updateText function
    @param Id id
    @param Text *text
    @return bool
*/
bool LibSfml::updateText([[maybe_unused]] Id id, [[maybe_unused]] Text *text)
{
    return true;
}

/*  @author Paul
    @brief updateText function
    @param std::vector<std::pair<Id, Text *>> texts
    @return bool
*/
bool LibSfml::updateText([[maybe_unused]] std::vector<std::pair<Id, Text *>> texts)
{
    return true;
}

/*  @author Paul
    @brief displayError function
    @param void
    @return bool
*/
bool LibSfml::displayError()
{
    return true;
}

/*  @author Paul
    @brief sceneSwitch function
    @param void
    @return bool
*/
bool LibSfml::sceneSwitch()
{
    return true;
}

/*  @author Paul
    @brief getFPS function
    @param void
    @return int
*/
int LibSfml::getFPS()
{
    return 0;
}

/*  @author Paul
    @brief debug function
    @param void
    @return bool
*/
bool LibSfml::debug()
{
    return true;
}

/*  @author Paul
    @brief getRes function
    @param void
    @return std::vector<float>
*/
std::vector<float> LibSfml::getRes()
{
    return std::vector<float>();
}

/*  @author Paul
    @brief getSize function
    @param void
    @return std::vector<float>
*/
std::vector<float> LibSfml::getSize()
{
    return std::vector<float>();
}

// -- LibSfml

// Window (Screen)

/*  @author Paul
    @brief destroyScreen function
    @param void
    @return void
*/
void LibSfml::_destroyScreen()
{
    _win->close();
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
sf::IntRect LibSfml::createRect(int x, int y, int w, int h)
{
    sf::IntRect rect;

    rect.left = x;
    rect.top = y;
    rect.width = w;
    rect.height = h;
    return rect;
}

// Texture

/*  @author Paul
    @brief createTexture function
    @param const char *file
    @return sf::Texture *
*/
sf::Texture *LibSfml::createTexture(std::string *file)
{
    sf::Texture *texture = new sf::Texture();

    if (!texture->loadFromFile(*file))
        throw LibSfmlException("Failed to load texture", "LibSfml::createTexture");
    return texture;
}

// Sprite

/*  @author Paul
    @brief createSprite function
    @param sf::Texture *texture
    @return sf::Sprite *
*/
sf::Sprite *LibSfml::createSprite(sf::Texture *texture)
{
    sf::Sprite *sprite = new sf::Sprite();

    sprite->setTexture(*texture);
    return sprite;
}

/*  @author Paul
    @brief createSprite function
    @param sf::Texture *texture
    @param sf::IntRect rect
    @return sf::Sprite *
*/
sf::Sprite *LibSfml::createSprite(sf::Texture *texture, sf::IntRect rect)
{
    sf::Sprite *sprite = new sf::Sprite();

    sprite->setTexture(*texture);
    sprite->setTextureRect(rect);
    return sprite;
}

// Font

/*  @author Paul
    @brief createFont function
    @param const char *file
    @return sf::Font *
*/
sf::Font *LibSfml::createFont(const char *file)
{
    sf::Font *font = new sf::Font();

    if (!font->loadFromFile(file))
        throw LibSfmlException("Failed to load font", "LibSfml::createFont");
    return font;
}

/*  @author Paul
    @brief createText function
    @param const char *str
    @param sf::Font *font
    @param int size
    @param sf::Color color
    @return sf::Text *
*/
sf::Text *LibSfml::createText(const char *str, sf::Font *font, int size, sf::Color color)
{
    sf::Text *text = new sf::Text();

    text->setFont(*font);
    text->setString(str);
    text->setCharacterSize(size);
    text->setFillColor(color);
    return text;
}

/*  @author Paul
    @brief changeScore function
    @param int add
    @return void
*/
bool LibSfml::changeScore(int add)
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
int LibSfml::getScore()
{
    return _score;
}

/*  @author Paul
    @brief getHighScore function
    @param void
    @return int
*/
int LibSfml::getHighScore()
{
    return _score;
}

/*  @author Paul
    @brief setScore function
    @param int add
    @return bool
*/
bool LibSfml::setScore(int score)
{
    _score = score;
    if (_score > _highScore) {
        writeScore();
        _highScore = _score;
    }
    return true;
}

/*  @author Paul
    @brief setHighScore function
    @param int add
    @return bool
*/
bool LibSfml::setHighScore(int score)
{
    _highScore = score;
    return true;
}

/*  @author Paul
    @brief writeScore function
    @param void
    @return bool
*/
bool LibSfml::writeScore()
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

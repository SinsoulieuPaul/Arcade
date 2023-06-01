/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"
#include <iostream>
#include <fstream>

/*==============/
/  Exceptions   /
/==============*/

/// @brief Constructor of the LibNcursesException class
/// @param message The exception message
/// @param component The component that throw the exception
LibNcurses::LibNcursesException::LibNcursesException(const std::string &message)
{
    _message = "LibNcurses: " + message;
}

/// @brief Return the exception message
/// @return The exception message
const char *LibNcurses::LibNcursesException::what() const noexcept
{
    return _message.c_str();
}

// Load Library

/*  @author Louis
    @Allows loading the library through the dlfcn
*/
extern "C" std::shared_ptr<IDispModule> createLib()
{
    std::cout << "Creating LibNcurses instance" << std::endl;
    return std::make_shared<LibNcurses>();
}

// Init and destroy

/*  @author Zélie
    @brief LibNcurse constructor, with initial size values
*/
LibNcurses::LibNcurses()
{
    _x = 36;
    _y = 28;
}

/*  @author Zélie
    @brief LibNcurse constructor, with size parameters
*/
LibNcurses::LibNcurses(int x, int y)
{
    _x = x;
    _y = y;
}

/*  @author Zélie
    @brief LibNcurse destructor
*/
LibNcurses::~LibNcurses()
{
    Ncurses::_clear();
    Ncurses::_refresh();
    Ncurses::_clear();
    Ncurses::_endwin();
}

// -- IDispModule

/*  @author Zélie
    @brief initScreen function
    @param void
    @return bool
*/
bool LibNcurses::initScreen()
{
    _win = Ncurses::_initscr();
    Ncurses::_keypad(_win, true);
    Ncurses::_timeout();
    return true;
}

// bool LibNcurses::update()
// {
//     Ncurses::_clear();
//     return true;
// }

/*  @author Zélie
    @brief getUserInput function
    @param void
    @return Key
*/
void LibNcurses::setKey()
{
    int input = Ncurses::_getch();

    switch (input) {
        case KEY_UP:
            _key = Key::Z;
            break;
        case KEY_DOWN:
            _key = Key::S;
            break;
        case KEY_LEFT:
            _key = Key::Q;
            break;
        case KEY_RIGHT:
            _key = Key::D;
            break;
        case 122:
            _key = Key::Z;
            break;
        case 113:
            _key = Key::Q;
            break;
        case 115:
            _key = Key::S;
            break;
        case 100:
            _key = Key::D;
            break;
        case 114:
            _key = Key::R;
            break;
        case 108:
            _key = Key::L;
            break;
        case 71:
            _key = Key::G;
            break;
        case KEY_ENTER:
            _key = Key::Enter;
            break;
        case '\n':
            _key = Key::Enter;
            break;
        default :
            _key = Key::None;
            break;
    }
}

Key LibNcurses::getUserInput()
{
    return _key;
}

void LibNcurses::setUserInput(Key key)
{
    _key = key;
}

bool LibNcurses::destroyScreen()
{
    Ncurses::_clear();
    Ncurses::_refresh();
    Ncurses::_endwin();
    return true;
}

/*  @author Zélie
    @brief display function
    @param void
    @return bool
*/
bool LibNcurses::display()
{
    Ncurses::_clear();
    drawProp(_props);
    drawEntity(_entities);
    drawText(_texts);
    Ncurses::_refresh();
    Ncurses::_curs_set(0);
    setKey();
    return true;
}

/*  @author Zélie
    @brief drawEntity function
    @param Entity *entity
    @return bool
*/

bool LibNcurses::drawEntity(Entity *entity)
{
    Ncurses::_mvaddch(entity->getProperty(Position)[1] / 16, entity->getProperty(Position)[0] / 16, entity->getSpriteChar());
    return true;
}

/*  @author Zélie
    @brief drawEntity function
    @param std::vector<Entity *> entities
    @return bool
*/
bool LibNcurses::drawEntity(std::vector<Entity *> entities)
{
    try {
        for (auto &entity : entities)
            drawEntity(entity);
    } catch (const std::exception &e) {
        throw LibNcursesException(e.what());
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief drawProp function
    @param Prop *prop
    @return bool
*/
bool LibNcurses::drawProp(Prop *prop)
{
    Ncurses::_mvaddch(prop->getProperty(Position)[1] / 16, prop->getProperty(Position)[0] / 16, prop->getSpriteChar());
    return true;
}

/*  @author Zélie
    @brief drawProp function
    @param std::vector<Prop *> props
    @return bool
*/
bool LibNcurses::drawProp(std::vector<Prop *> props)
{
    try {
        for (auto prop : props)
            drawProp(prop);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while drawing props");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief drawText function
    @param Text *text
    @return bool
*/
bool LibNcurses::drawText(Text *text)
{
    Ncurses::_mvaddstr(text->getProperty(Position)[1] / 16, text->getProperty(Position)[0] / 16, text->getText()->c_str());
    return true;
}

/*  @author Zélie
    @brief drawText function
    @param std::vector<Text *> texts
    @return bool
*/
bool LibNcurses::drawText(std::vector<Text *> texts)
{
    try {
        for (std::size_t i = 0; i < texts.size(); i++)
            drawText(texts[i]);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while drawing texts");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief drawText function
    @param Text *text
    @return bool
*/
bool LibNcurses::addText(Text *text)
{
    try {
        _texts.push_back(text);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while adding text");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief addEntity function
    @param Entity *entity
    @return bool
*/
bool LibNcurses::addEntity(Entity *entity)
{
    try {
        _entities.push_back(entity);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while adding entity");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief addProp
    @param Prop *prop
    @return bool
*/
bool LibNcurses::addProp(Prop *prop)
{
    try {
        _props.push_back(prop);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while adding prop");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief changeScore function
    @param int add
    @return bool
*/
bool LibNcurses::changeScore(int add)
{
    _score += add;
    if (_score > _highScore) {
        _highScore = _score;
        writeScore();
    }
    return true;
}

/*  @author Zélie
    @brief getScore function
    @param void
    @return int
*/
int LibNcurses::getScore()
{
    return _score;
}

/*  @author Paul
    @brief getHighScore function
    @param void
    @return int
*/
int LibNcurses::getHighScore()
{
    return _score;
}

/*  @author Zélie
    @brief setScore function
    @param int score
    @return void
*/
bool LibNcurses::setScore(int score)
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
    @param int score
    @return void
*/
bool LibNcurses::setHighScore(int score)
{
    _highScore = score;
    return true;
}

/*  @author Paul
    @brief writeScore function
    @param void
    @return bool
*/
bool LibNcurses::writeScore()
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

/*  @author Zélie
    @brief clearAll function
    @param void
    @return bool
*/
bool LibNcurses::clearAll()
{
    try {
        if (!(_entities.empty()))
            _entities.clear();
        if (!(_props.empty()))
            _props.clear();
        if (!(_texts.empty()))
            _texts.clear();
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing all");
        return false;
    }
    return true;
}

/*  @author Paul
    @brief clearEntity function
    @param void
    @return bool
*/
bool LibNcurses::clearEntity()
{
    try {
        if (!(_entities.empty()))
            _entities.clear();
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing entities");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief clearEntity function
    @param Id id
    @return bool
*/
bool LibNcurses::clearEntity(Id id)
{
    try {
        _entities.erase(_entities.begin() + id);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing entities");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief clearProp function
    @param Id id
    @return bool
*/
bool LibNcurses::clearProp(Id id)
{
    try {
        _props.erase(_props.begin() + id);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing props");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief clearText function
    @param Id id
    @return bool
*/
bool LibNcurses::clearText(Id id)
{
    try {
        _texts.erase(_texts.begin() + id);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing texts");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief clearEntity function
    @param std::vector<Id> ids
    @return bool
*/
bool LibNcurses::clearEntity(std::vector<Id> ids)
{
    try {
        for (auto id : ids)
            clearEntity(id);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing entities");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief clearProp function
    @param std::vector<Id> ids
    @return bool
*/
bool LibNcurses::clearProp(std::vector<Id> ids)
{
    try {
        for (auto id : ids)
            clearProp(id);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing props");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief clearText function
    @param std::vector<Id> ids
    @return bool
*/
bool LibNcurses::clearText(std::vector<Id> ids)
{
    try {
        for (auto id : ids)
            clearText(id);
    } catch (const std::exception &e) {
        throw LibNcursesException("Error while clearing texts");
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief updateEntity function
    @param Id pos
    @param Entity *entity
    @return bool
*/
bool LibNcurses::updateEntity(Id pos, Entity *entity)
{
    _entities.at(pos) = entity;
    return true;
}

/*  @author Paul
    @brief getEntities function
    @param void
    @return std::vector<Entity *>
*/
std::vector<Entity *> LibNcurses::getEntities()
{
    return _entities;
}

/*  @author Zélie
    @brief updateProp function
    @param Id pos
    @param Prop *prop
    @return bool
*/
bool LibNcurses::updateProp(Id pos, Prop *prop)
{
    _props.at(pos) = prop;
    return true;
}

/*  @author Zélie
    @brief updateText function
    @param Id pos
    @param Text *text
    @return bool
*/
bool LibNcurses::updateText(Id pos, Text *text)
{
    _texts.at(pos) = text;
    return true;
}

/*  @author Zélie
    @brief updateEntity function
    @param std::vector<std::pair<Id, Entity *>> entities
    @return bool
*/
bool LibNcurses::updateEntity(std::vector <std::pair<Id, Entity *>> Entities)
{
    try {
        for (auto entity : Entities)
            updateEntity(std::get<Id>(entity), std::get<Entity *>(entity)); 
    } catch (const std::exception &e) {
        throw  LibNcursesException("Error: " + std::string(e.what()));
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief updateProp function
    @param std::vector<std::pair<Id, Prop *>> props
    @return bool
*/
bool LibNcurses::updateProp(std::vector<std::pair<Id, Prop *>> Props)
{
    try {
        for (auto prop : Props)
            updateProp(std::get<Id>(prop), std::get<Prop *>(prop));
    } catch (const std::exception &e) {
        throw  LibNcursesException("Error: " + std::string(e.what()));
        return false;
    }
    return true;
}

/*  @author Zélie
    @brief updateText function
    @param std::vector<std::pair<Id, Text *>> texts
    @return bool
*/
bool LibNcurses::updateText(std::vector<std::pair<Id, Text *>> Texts)
{
    try {
        for (auto text : Texts)
            updateText(std::get<Id>(text), std::get<Text *>(text));
    } catch (const std::exception &e) {
        throw  LibNcursesException("Error: " + std::string(e.what()));
        return false;
    }
    return true;
}

bool LibNcurses::displayError()
{
    return true;
}

bool LibNcurses::sceneSwitch()
{
    return true;
}

/*  @author Zélie
    @brief getFPS function
    @param void
    @return int 69420
*/
int LibNcurses::getFPS()
{
    return 69420;
}

bool LibNcurses::debug()
{
    return true;
}

std::vector<float> LibNcurses::getRes()
{
    return {0, 0};
}

std::vector<float> LibNcurses::getSize()
{
    return {0, 0};
}

bool LibNcurses::update()
{
    return true;
}

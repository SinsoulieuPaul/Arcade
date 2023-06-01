/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Pacman
*/

#include "Pacman.hpp"
#include "../../../core/Core.hpp"

extern Core *g_core;
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

Pacman::Pacman()
{
}

Pacman::~Pacman()
{
}

/* @author Louis
    @brief systemInit function
    @param void
    @return State
*/

State Pacman::systemInit()
{
    std::cout << "Pacman init" << std::endl;
    this->_state = Init;
    this->_initBackground();
    Entity *player = new Entity(Player, std::vector<float>{2 * 16 , 2 * 16});
    player->setSpritePath(new std::string("assets/pacman/pacman_full.png"));
    player->setSpriteChar('P');
    player->setProperty(Velocity, std::vector<float>{0, 0});
    _entities.push_back(player);
    return _state;
}

/* @author Louis
    @brief systemStart function
    @param void
    @return State
*/

State Pacman::systemStart()
{
    this->_state = Started;
    return _state;
}

/* @author Louis
    @brief systemStop function
    @param void
    @return State
*/

State Pacman::systemStop()
{
    this->_state = Stopped;
    return _state;
}

/* @author Louis
    @brief systemClear function
    @param void
    @return State
*/

State Pacman::systemClear()
{
    this->_state = Cleared;
    return _state;
}

/* @author Louis
    @param void
    @return State
*/

State Pacman::systemGetState() const
{
    return _state;
}

/* @author Louis
    @brief systemSetState function
    @param State
    @return void
*/

void Pacman::systemSetState(State state)
{
    this->_state = state;
}

/* @author Louis
    @brief systemOnUserInput function
    @param int
    @return void
*/


bool Pacman::_playerCollision()
{
    Entity *player = this->_entities[0];
    std::vector<float> playerPos = player->getProperty(Position);
    std::vector<float> playerVel = player->getProperty(Velocity);

    for (auto prop : this->_props) {
        std::vector<float> propPos = prop->getProperty(Position);
        if (prop->getType() == Wall) {
            if (playerPos[0] + playerVel[0] == propPos[0] && playerPos[1] + playerVel[1] == propPos[1]) {
                return true;
            }
        }
    }
    return false;
}

void Pacman::systemOnUserInput([[maybe_unused]]int input )
{

    std::vector<Entity *> entities = entityGetAll();
    if (input == Key::Z && !_playerCollision()) {
        for (auto entity : entities) {
            std::map<Property, std::vector<float>> properties = entity->getProperties();
            entity->setProperty(Velocity, std::vector<float> {0, -4});
        }
    } else if (input == Key::S && !_playerCollision()) {
        for (auto entity : entities) {
            std::map<Property, std::vector<float>> properties = entity->getProperties();
            entity->setProperty(Velocity, std::vector<float> {0, 4});
        }
    } else if (input == Key::Q && !_playerCollision()) {
        for (auto entity : entities) {
            std::map<Property, std::vector<float>> properties = entity->getProperties();
            entity->setProperty(Velocity, std::vector<float> {-4, 0});
        }
    } else if (input == Key::D && !_playerCollision()) {
        for (auto entity : entities) {
            std::map<Property, std::vector<float>> properties = entity->getProperties();
            entity->setProperty(Velocity, std::vector<float> {4, 0});
        }
    }
}

/* @author Louis
    @brief systemDebug function
    @param void
    @return void
*/

void Pacman::systemDebug()
{
    std::cout << "Pacman debug" << std::endl;
}

/* @author Louis
    @brief systemUpdate function
    @param void
    @return State
*/
State Pacman::systemUpdate()
{
    this->_state = Updated;

    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _clock);
    if (timeElapsed.count() >= 30) {
        _clock = currentTime;
        _entities[0]->setProperty(Position, std::vector<float>{_entities[0]->getProperties()[Position][0] + _entities[0]->getProperties()[Velocity][0], _entities[0]->getProperties()[Position][1] + _entities[0]->getProperties()[Velocity][1]});
    }

    return _state;
}

bool Pacman::propRemove([[maybe_unused]]Id id) {
    if (id < this->_props.size()) {
        this->_props.erase(this->_props.begin() + id);
        return true;
    }
    return false;
}
// Entity


std::vector<Entity *> Pacman::entityGetAll()
{
    return this->_entities;
}


Entity * Pacman::entityGet(Id index)
{
    return this->_entities[index];
}

Entity * Pacman::entityGet(Name name)
{
    for (auto &entity : this->_entities) {
        if (entity->getName() == name)
            return entity;
    }
    return new Entity();
}

Id Pacman::entityGetId(Name name)
{
    for (std::size_t i = 0; i < this->_entities.size(); i++) {
        if (this->_entities[i]->getName() == name)
            return i;
    }
    return 0;
}

Name Pacman::entityGetName(Id index)
{
    return this->_entities[index]->getName();
}


std::vector<Entity *> Pacman::entityGetAllOfType(EntityType type)
{
    std::vector<Entity *> entities;
    for (auto &entity : this->_entities) {
        if ((int)entity->getProperty(Type)[0] == type)
            entities.push_back(entity);
    }
    return entities;
}

void Pacman::_initLabyrinth()
{
    std::vector<std::vector<float>> coords;

    // Coordonnées pour les murs horizontaux
    std::vector<std::vector<int>> horizontal_walls = {
        {6, 6, 44},
        {6, 34, 44},
        {12, 16, 20},
        {36, 16, 44},
        {20, 22, 28},
        {36, 22, 44}
    };

    for (const auto &wall : horizontal_walls) {
        for (int x = wall[0]; x <= wall[2]; x += 2) {
            if (!((x == 16 && (wall[1] == 6 || wall[1] == 34)) || (x == 34 && (wall[1] == 6 || wall[1] == 34)))) {
                coords.push_back({(float)x, (float)wall[1]});
            }
        }
    }

    // Coordonnées pour les murs verticaux
    std::vector<std::vector<int>> vertical_walls = {
        {6, 6, 34},
        {44, 6, 34},
        {20, 6, 16},
        {20, 22, 34},
        {36, 6, 16},
        {36, 22, 34}
    };

    for (const auto &wall : vertical_walls) {
        for (int y = wall[1]; y <= wall[2]; y += 2) {
            if (!((y == 20 && (wall[0] == 6 || wall[0] == 44)) || (y == 12 && (wall[0] == 20 || wall[0] == 36)))) {
                coords.push_back({(float)wall[0], (float)y});
            }
        }
    }

    // Coordonnées pour la cache au milieu
    std::vector<std::vector<float>> middle_cache_coords = {
        {28, 20}, {28, 22}, {28, 24}, {28, 26},
        {30, 20},
        {32, 20}, {32, 22}, {32, 24}, {32, 26}
    };

    coords.insert(coords.end(), middle_cache_coords.begin(), middle_cache_coords.end());

    // Création des objets murs
    for (auto &coord : coords) {
        Prop *prop = new Prop(Wall, std::vector<float>{coord[0] * 16, coord[1] * 16});
        prop->setSpritePath(new std::string("assets/pacman/pacman_wall.png"));
        prop->setSpriteChar('X');
        prop->setName(new std::string("Wall"));
        this->_props.push_back(prop);
    }

    Prop *prop = new Prop(Button);
    prop->setProperty(Position, std::vector<float>{(0), (35*16)});
    prop->setSpritePath(new std::string("assets/buttons/load_button.png"));
    prop->setSpriteChar('L');
    this->_props.push_back(prop);
}

// Prop

void Pacman::_initBackground()
{
    int height = 600 - 16;
    int width = 800 - 16;
    int size = 16;
    for (int i = 0; i < height / size; i++) {
        for (int j = 0; j < width / size; j++) {
            if ( i == 0 || i == height / size - 1 || j == 0 || j == width / size - 1) {
                Prop *prop = new Prop(Wall, std::vector<float>{(float)j * size, (float)i * size});
                prop->setSpritePath(new std::string("assets/pacman/pacman_wall.png"));
                prop->setSpriteChar('X');
                prop->setName(new std::string("Wall"));
                this->_props.push_back(prop);
            }
        }
    }
    _initLabyrinth();
}

void Pacman::_initPacman()
{
}

extern "C" std::shared_ptr<IGameModule> createLib()
{
    return std::make_shared<Pacman>();
}

std::vector<float> Pacman::entityGetProperty(Id index, Property property)
{
    return this->_entities[index]->getProperty(property);
}

bool Pacman::entityUpdate(Id index, Property property, int value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Pacman::entityUpdate(Id index, Property property, std::vector<float> value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Pacman::entityUpdate(Id index, Property property, float value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Pacman::entityUpdate(Id index, Property property, std::vector<int> value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Pacman::entityUpdate(Id index, Property property, Name value)
{
    (void)index;
    (void)property;
    (void)value;
    return true;
}

bool Pacman::entityPush(Entity entity)
{
    this->_entities.push_back(new Entity(entity));
    return true;
}

bool Pacman::entityPush_front(Entity entity)
{
    this->_entities.insert(this->_entities.begin(), new Entity(entity));
    return true;
}

bool Pacman::entityRemove(Id index)
{
    this->_entities.erase(this->_entities.begin() + index);
    return true;
}

bool Pacman::entityPop()
{
    this->_entities.pop_back();
    return true;
}

bool Pacman::entityPop_front()
{
    this->_entities.erase(this->_entities.begin());
    return true;
}

bool Pacman::entityClearAll()
{
    this->_entities.clear();
    return true;
}

/*  @author Paul
    @brief getScore function
    @param void
    @return int
*/
int Pacman::getScore() const
{
    return this->_score;
}

/*  @author
    @brief setScore function
    @param int
    @return void
*/
void Pacman::setScore(int score)
{
    this->_score = score;
}

/*  @author Paul
    @brief getHighScore function
    @param void
    @return int
*/
int Pacman::getHighScore() const
{
    return this->_highScore;
}

/*  @author
    @brief setHighScore function
    @param int
    @return void
*/
void Pacman::setHighScore(int score)
{
    this->_highScore = score;
}

/*  @author
    @brief textGetAll function
    @param void
    @return std::vector<Text *>
*/
std::vector<Text *> Pacman::textGetAll()
{
    return this->_texts;
}

std::vector<Prop *> Pacman::propGetAll()
{
    return this->_props;
}

std::vector<Prop *> Pacman::propGetAllOfType(PropType type)
{
    std::vector<Prop *> props;

    for (auto &prop : this->_props) {
        if (prop->getType() == type)
            props.push_back(prop);
    }
    return props;
}

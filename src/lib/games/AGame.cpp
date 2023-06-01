/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** AGame
*/

#include "AGame.hpp"

AGame::AGame()
{
}

AGame::~AGame()
{
}


State AGame::systemInit()
{
    this->_state = Init;
    return _state;
}

State AGame::systemStart()
{
    this->_state = Started;
    return _state;
}

State AGame::systemStop()
{
    this->_state = Stopped;
    return _state;
}

State AGame::systemClear()
{
    this->_state = Cleared;
    return _state;
}

State AGame::systemUpdate()
{
    this->_state = Updated;
    return _state;
}

State AGame::systemGetState() const
{
    return _state;
}

void AGame::systemSetState([[maybe_unused]] State state)
{
    this->_state = state;
}

void AGame::systemOnUserInput([[maybe_unused]] int input)
{
}

void AGame::systemDebug()
{
    std::cout << "Debug" << std::endl;
}

// Entity functions

std::vector<Entity *> AGame::entityGetAll()
{
    return this->_entities;
}

Entity * AGame::entityGet([[maybe_unused]] Id id)
{
    for (std::size_t i = 0; i < this->_entities.size(); i++) {
        if (i == id)
            return this->_entities[i];
    }
    return new Entity();
}

Entity * AGame::entityGet([[maybe_unused]] Name name)
{
    for (auto &entity : this->_entities) {
        if (entity->getName() == name)
            return entity;
    }
    return new Entity();
}

std::vector<Entity *> AGame::entityGetAllOfType([[maybe_unused]] EntityType type)
{
    std::vector<Entity *> entities;
    for (auto &entity : this->_entities) {
        if (entity->getType() == type)
            entities.push_back(entity);
    }
    return entities;
}

Id AGame::entityGetId([[maybe_unused]] Name name)
{
    Id id = 0;
    for (auto &entity : this->_entities) {
        if (entity->getName() == name)
            return id;
        id++;
    }
    return id;
}

Name AGame::entityGetName([[maybe_unused]] Id id)
{
    for (Id i = 0; i < this->_entities.size(); i++) {
        if (i == id)
            return this->_entities[i]->getName();
    }
    return new std::string("No name");
}

std::vector<float> AGame::entityGetProperty([[maybe_unused]]Id id, [[maybe_unused]] Property property)
{
    for (Id i = 0; i < this->_entities.size(); i++) {
        if (i == id)
            return this->_entities[i]->getProperty(property);
    }
    return std::vector<float>();
}

bool AGame::entityUpdate([[maybe_unused]] Id id, [[maybe_unused]] Property property, [[maybe_unused]] int value)
{
    for (Id i = 0; i < this->_entities.size(); i++) {
        if (i == id) {
            this->_entities[i]->setProperty(property, value);
            return true;
        }
    }
    return false;
}

bool AGame::entityUpdate([[maybe_unused]] Id id, [[maybe_unused]] Property property, [[maybe_unused]]float value)
{
    // for (auto &entity : this->_entities) {
    //     // if (entity->getId() == id)
    //     //     return entity->update(property, value);
    // }
    return false;
}

bool AGame::entityUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]std::vector<float> value)
{
    // for (auto &entity : this->_entities) {
    //     // if (entity->getId() == id)
    //     //     return entity->update(property, value);
    // }
    return false;
}

bool AGame::entityUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]std::vector<int> value)
{
    // for (auto &entity : this->_entities) {
    //     // if (entity->getId() == id)
    //     //     return entity->update(property, value);
    // }
    return false;
}

bool AGame::entityUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]Name value)
{
    // for (auto &entity : this->_entities) {
    //     // if (entity->getId() == id)
    //     //     return entity->update(property, value);
    // }
    return false;
}

bool AGame::entityPush(Entity entity)
{
    this->_entities.push_back(&entity);
    return true;
}

bool AGame::entityPush_front(Entity entity)
{
    this->_entities.at(0) = &entity;
    return true;
}

bool AGame::entityRemove([[maybe_unused]] Id id)
{
    // for (auto &entity : this->_entities) {
    //     // if (entity->getId() == id) {
    //     //     this->_entities.erase(entity);
    //     //     return true;
    //     // }
    // }
    return false;
}

bool AGame::entityPop()
{
    this->_entities.pop_back();
    return true;
}

bool AGame::entityPop_front()
{
    this->_entities.erase(this->_entities.begin());
    return true;
}

bool AGame::entityClearAll()
{
    this->_entities.clear();
    return true;
}

// Prop functions

std::vector<Prop *> AGame::propGetAll()
{
    return this->_props;
}

Prop AGame::propGet([[maybe_unused]] Id id)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return *prop;
    // }
    return Prop();
}

std::vector<Prop *> AGame::propGetAllOfType([[maybe_unused]] PropType type)
{
    // std::vector<Prop> props;
    // for (auto &prop : this->_props) {
    //     // if (prop->getType() == type)
    //     //     props.push_back(*prop);
    // }
    return std::vector<Prop *>();
}

std::vector<float> AGame::propGetProperty([[maybe_unused]] Id id, [[maybe_unused]] Property property)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return prop->getProperty(property);
    // }
    return std::vector<float>();
}

bool AGame::propUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]int value)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return prop->update(property, value);
    // }
    return false;
}

bool AGame::propUpdate([[maybe_unused]]Id id,[[maybe_unused]] Property property, [[maybe_unused]]float value)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return prop->update(property, value);
    // }
    return false;
}

bool AGame::propUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]std::vector<float> value)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return prop->update(property, value);
    // }
    return false;
}

bool AGame::propUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]std::vector<int> value)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return prop->update(property, value);
    // }
    return false;
}

bool AGame::propUpdate([[maybe_unused]]Id id, [[maybe_unused]]Property property, [[maybe_unused]]Name value)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id)
    //     //     return prop->update(property, value);
    // }
    return false;
}

bool AGame::propPush([[maybe_unused]]Prop prop)
{
    this->_props.push_back(&prop);
    return true;
}

bool AGame::propPush_front([[maybe_unused]]Prop prop)
{
    this->_props.at(0) = &prop;
    return true;
}

bool AGame::propRemove([[maybe_unused]]Id id)
{
    // for (auto &prop : this->_props) {
    //     // if (prop->getId() == id) {
    //     //     this->_props.erase(prop);
    //     //     return true;
    //     // }
    // }
    return false;
}

bool AGame::propPop()
{
    this->_props.pop_back();
    return true;
}

bool AGame::propPop_front()
{
    this->_props.erase(this->_props.begin());
    return true;
}

bool AGame::propClearAll()
{
    this->_props.clear();
    return true;
}

/*  @author Paul
    @brief textGetAll function
    @param void
    @return std::vector<Text *>
*/
std::vector<Text *> AGame::textGetAll()
{
    return this->_texts;
}

/*  @author Paul
    @brief getScore function
    @param void
    @return int
*/
int AGame::getScore() const
{
    return this->_score;
}

/*  @author Paul
    @brief setScore function
    @param int
    @return void
*/
void AGame::setScore(int score)
{
    this->_score = score;
}

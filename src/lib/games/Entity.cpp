/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Entity
*/

#include "Entity.hpp"

/* @author Louis
    @brief Entity constructor
*/
Entity::Entity()
{
    this->_type = EntityType::Mob;
    this->_name = new std::string("test");
    _properties[Property::Position] = {0, 0};
    _properties[Property::Velocity] = {0};
    _properties[Property::Health] = {100};
    _properties[Property::Type] = {static_cast<float>(EntityType::Mob)};
}

/* @author Louis
    @brief Entity constructor
    @param EntityType
*/
Entity::Entity(EntityType type)
{
    this->_type = type;
    this->_name = new std::string("test");
    _properties[Property::Position] = {0, 0};
    _properties[Property::Velocity] = {0};
    _properties[Property::Health] = {100};
    _properties[Property::Type] = {static_cast<float>(type)};

}

/* @author Louis
    @brief Entity constructor
    @param EntityType
    @param std::vector<float>
*/
Entity::Entity(EntityType type, std::vector<float> position)
{
    this->_type = type;
    this->_name = new std::string("test");
    _properties[Property::Position] = position;
    _properties[Property::Velocity] = {0};
    _properties[Property::Health] = {100};
    _properties[Property::Type] = {static_cast<float>(type)};
    _properties[Property::Rotation] = {0};
}

Entity::~Entity()
{
}

/*  @author Louis
    @brief set Property function
    @param Property
    @param int
*/
void Entity::setProperty(Property property, int value)
{
    _properties[property] = {static_cast<float>(value)};
}

/*  @author Louis
    @brief set Property function
    @param Property
    @param float
*/
void Entity::setProperty(Property property, float value)
{
    _properties[property] = {value};
}

/*  @author Louis
    @brief set Property function
    @param Property
    @param std::vector<float>
*/
void Entity::setProperty(Property property, std::vector<float> value)
{
    _properties[property] = value;
}

/*  @author Louis
    @brief set Property function
    @param Property
    @param std::vector<int>
*/
void Entity::setProperty(Property property, std::vector<int> value)
{
    std::vector<float> tmp;
    for (auto &i : value)
        tmp.push_back(static_cast<float>(i));
    _properties[property] = tmp;
}

/*  @author Louis
    @brief get Property function
    @param Property
    @return std::vector<float>
*/
std::vector<float> Entity::getProperty(Property property)
{
    if (_properties.find(property) == _properties.end())
        return {0};
    return _properties[property];
}

/*  @author Louisd::cout << "Entity::getProperty" << std::endl;
    @brief get Properties function
    @return std::map<Property, std::vector<float>>
*/
std::map<Property, std::vector<float>> Entity::getProperties()
{
    return _properties;
}

/*  @author Louis
    @brief get Type function
    @return EntityType
*/
EntityType Entity::getType()
{
    return _type;
}

/*  @author Louis
    @brief get Name function
    @return Name
*/
Name Entity::getName()
{
    return _name;
}

/*  @author Louis
    @brief set Name function
    @param Name
    @return void
*/
void Entity::setName(Name name)
{
    _name = name;
}

/*  @author Louis
    @brief get SpritePath function
    @param void
    @return std::string *
*/
std::string *Entity::getSpritePath() const
{
    return _spritePath;
}

/*  @author Louis
    @brief set SpritePath function
    @param std::string *
    @return void
*/
void Entity::setSpritePath(std::string *spritePath)
{
    _spritePath = spritePath;
}

/*  @author Louis
    @brief get SpriteChar function
    @param void
    @return Sprite
*/
char Entity::getSpriteChar() const
{
    return _spriteChar;
}

/*  @author Louis
    @brief set SpriteChar function
    @param char spriteChar
    @return void
*/
void Entity::setSpriteChar(char spriteChar)
{
    _spriteChar = spriteChar;
}

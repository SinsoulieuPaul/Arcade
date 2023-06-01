/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Prop
*/

#include "Prop.hpp"

Prop::Prop()
{
    Prop(PropType::Wall);
}

Prop::~Prop()
{
}

Prop::Prop(PropType type)
{
    Prop(type, {0, 0});
}

Prop::Prop(PropType type, std::vector<float> position)
{
    _properties[Property::Position] = position;
    _properties[Property::Velocity] = {0};
    _properties[Property::Health] = {100};
    _properties[Property::Type] = {static_cast<float>(type)};
    _type = type;
    _name = new std::string("default");
}

void Prop::setProperty(Property property, int value)
{
    _properties[property] = {static_cast<float>(value)};
}

void Prop::setProperty(Property property, float value)
{
    _properties[property] = {value};
}

void Prop::setProperty(Property property, std::vector<float> value)
{
    _properties[property] = value;
}

void Prop::setProperty(Property property, std::vector<int> value)
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
std::vector<float> Prop::getProperty(Property property)
{
    return _properties[property];
}


/*  @author Louis
    @brief get Type function
    @param void
    @return PropType
*/

PropType Prop::getType()
{
    return _type;
}

/*  @author Louis
    @brief set Name function
    @return void
*/
void Prop::setName(Name name)
{
    _name = name;
}

/*  @author Louis
    @brief get Name function
    @param void
    @return Name
*/
Name Prop::getName()
{
    return _name;
}

/*  @author Louis
    @brief get SpritePath function
    @param void
    @return std::string *
*/
std::string *Prop::getSpritePath() const
{
    return _spritePath;
}

/*  @author Louis
    @brief set SpritePath function
    @param std::string *spritePath
    @return void
*/
void Prop::setSpritePath(std::string *spritePath)
{
    _spritePath = spritePath;
}

/*  @author Louis
    @brief get SpriteChar function
    @param void
    @return char
*/
char Prop::getSpriteChar() const
{
    return _spriteChar;
}

/*  @author Louis
    @brief set SpriteChar function
    @param char spriteChar
    @return void
*/
void Prop::setSpriteChar(char spriteChar)
{
    _spriteChar = spriteChar;
}

/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Text
*/

#include "Text.hpp"
#include <iostream>

Text::~Text()
{
}

Text::Text(std::string *text)
{
    this->_text = text;
    this->_type = TextType::Other;
}

Text::Text(std::string *text, TextType type)
{
    this->_text = text;
    this->_type = type;
}

Text::Text(std::string *text, std::string *font)
{
    this->_text = text;
    this->_font = font;
    this->_type = TextType::Other;
}

Text::Text(std::string *text, std::string *font, TextType type)
{
    this->_text = text;
    this->_font = font;
    this->_type = type;
}

Text::Text(std::string *text, std::string *font, std::vector<float> position)
{
    this->_text = text;
    this->_font = font;
    this->_properties[Property::Position] = position;
    this->_type = TextType::Other;
}

Text::Text(std::string *text, std::string *font, std::vector<float> position, TextType type)
{
    this->_text = text;
    this->_font = font;
    this->_properties[Property::Position] = position;
    this->_type = type;
}

// Setters

void Text::setText(std::string *text)
{
    this->_text = text;
}

void Text::setFont(std::string *font)
{
    this->_font = font;
}

void Text::setProperty(Property property, std::vector<float> value)
{
    this->_properties[property] = value;
}

void Text::setType(TextType type)
{
    this->_type = type;
}

// Getters

std::string *Text::getText()
{
    return this->_text;
}

std::string *Text::getFont()
{
    return this->_font;
}

TextType Text::getType()
{
    return this->_type;
}

std::vector<float> Text::getProperty(Property property)
{
    if (this->_properties.find(property) == this->_properties.end())
        return {0, 0};
    return this->_properties[property];
}
/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Entity
*/


#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "IGameModule.hpp"

class Entity {
    public:

        /// @author Louis
        /// @brief Entity constructor
        /// @param void
        Entity();

        /// @author Louis
        /// @brief Entity constructor
        /// @param EntityType
        Entity(EntityType);

        /// @author Louis
        /// @brief Entity constructor
        /// @param EntityType
        /// @param std::vector<float> value
        Entity(EntityType, std::vector<float>);

        /// @author Louis
        /// @brief Entity destructor
        /// @param void
        ~Entity();

        // Setters

        /// @author Louis
        /// @brief setProperty function
        /// @param Property property
        /// @param int value
        /// @return void
        void setProperty(Property, int);

        /// @author Louis
        /// @brief setProperty function
        /// @param Property property
        /// @param float value
        /// @return void
        void setProperty(Property, float);

        /// @brief setProperty function
        /// @param Property property
        /// @param std::vector<float> value
        /// @return void
        void setProperty(Property, std::vector<float>);

        /// @brief setProperty function
        /// @param Property property
        /// @param std::vector<int> value
        /// @return void
        void setProperty(Property, std::vector<int>);

        // Getters

        /// @author Louis
        /// @brief getProperty function
        /// @param Property property
        /// @return std::vector<float>
        std::vector<float> getProperty(Property);

        /// @author Louis
        /// @brief getProperties function
        /// @param void
        /// @return std::map<Property, std::vector<float>>
        std::map<Property, std::vector<float>> getProperties();

        /// @author Louis
        /// @brief getType function
        /// @param void
        /// @return EntityType
        EntityType getType();

        /// @author Louis
        /// @brief getName function
        /// @param void
        /// @return Name
        Name getName();

        /// @author Louis
        /// @brief setName function
        /// @param Name name
        /// @return void
        void setName(Name);

        /// @author Louis
        /// @brief getSpritePath function
        /// @param void
        /// @return std::string *
        std::string *getSpritePath() const;

        /// @author Louis
        /// @brief setSpritePath function
        /// @param std::string *spritePath
        /// @return void
        void setSpritePath(std::string *spritePath);

        /// @author Louis
        /// @brief getSpriteChar function
        /// @param void
        /// @return char
        char getSpriteChar() const;

        /// @author Louis
        /// @brief setSpriteChar function
        /// @param char spriteChar
        /// @return void
        void setSpriteChar(char spriteChar);
    protected:
        std::map<Property, std::vector<float>> _properties;
        EntityType _type;
        Name _name;
        void *_clickAction;
        std::string *_spritePath;
        char _spriteChar;
};

#endif /* !ENTITY_HPP_ */

/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Prop
*/

#ifndef PROP_HPP_
#define PROP_HPP_
#include "IGameModule.hpp"

class Prop {
    public:
        /// @author Louis
        /// @brief Prop destructor
        /// @param void
        ~Prop();

        /// @author Louis
        /// @brief Prop constructor
        /// @param void
        Prop();

        /// @author Louis
        /// @brief Prop constructor
        /// @param PropType type
        Prop(PropType);

        /// @author Louis
        /// @brief Prop constructor
        /// @param PropType type
        /// @param std::vector<float> properties
        Prop(PropType, std::vector<float>);

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

        /// @author Louis
        /// @brief setProperty function
        /// @param Property property
        /// @param std::vector<float> value
        /// @return void
        void setProperty(Property, std::vector<float>);

        /// @author Louis
        /// @brief setProperty function
        /// @param Property property
        /// @param std::vector<int> value
        /// @return void
        void setProperty(Property, std::vector<int>);

        /// @author Louis
        /// @brief setName function
        /// @param Name name
        /// @return void
        void setName(Name);
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
        /// @return PropType
        PropType getType();

        /// @author Louis
        /// @brief getName function
        /// @param void
        /// @return Name
        Name getName();

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
        PropType _type;
        Name _name;
        void *_clickAction;
        std::string *_spritePath;
        char _spriteChar;
    private:
};

#endif /* !PROP_HPP_ */

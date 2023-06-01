/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Text
*/

#include "IGameModule.hpp"

#ifndef TEXT_HPP_
#define TEXT_HPP_

class Text {
    public:
        /// @author Louis
        /// @brief Text destructor
        /// @param void
        ~Text();

        /// @author Louis
        /// @brief Text constructor
        /// @param std::string *text
        Text(std::string *);

        /// @author Paul
        /// @brief Text constructor
        /// @param std::string *text
        /// @param TextType type
        Text(std::string *, TextType type);

        /// @author Paul
        /// @brief Text constructor
        /// @param std::string *text
        /// @param std::string *font
        Text(std::string *, std::string *);

        /// @author Paul
        /// @brief Text constructor
        /// @param std::string *text
        /// @param std::string *font
        /// @param TextType type
        Text(std::string *, std::string *, TextType);

        /// @author Paul
        /// @brief Text constructor
        /// @param std::string *text
        /// @param std::string *font
        /// @param std::vector<float> position
        Text(std::string *, std::string *, std::vector<float>);

        /// @author Paul
        /// @brief Text constructor
        /// @param std::string *text
        /// @param std::string *font
        /// @param std::vector<float> position
        /// @param TextType type
        Text(std::string *, std::string *, std::vector<float>, TextType);

        // Setters

        /// @author Louis
        /// @brief setText function
        /// @param std::string *text
        /// @return void
        void setText(std::string *);

        /// @author Paul
        /// @brief setFont function
        /// @param std::string *font
        /// @return void
        void setFont(std::string *);

        /// @author Paul
        /// @brief setType function
        /// @param TextType type
        /// @return void
        void setType(TextType);

        /// @author Paul
        /// @brief setProperty function
        /// @param Property property
        /// @param std::vector<float> value
        /// @return void
        void setProperty(Property, std::vector<float>);

        // Getters

        /// @author Louis
        /// @brief getText function
        /// @param void
        /// @return std::string *
        std::string *getText();

        /// @author Paul
        /// @brief getFont function
        /// @param void
        /// @return std::string *
        std::string *getFont();

        /// @author Paul
        /// @brief getType function
        /// @param void
        /// @return TextType
        TextType getType();

        /// @author Paul
        /// @brief getProperty function
        /// @param Property property
        /// @return std::vector<float>
        std::vector<float> getProperty(Property);

    protected:
    private:
        std::string *_text;
        std::string *_font;
        TextType _type;
        std::map<Property, std::vector<float>> _properties;
        void *_clickAction;
};

#endif /* !TEXT_HPP_ */

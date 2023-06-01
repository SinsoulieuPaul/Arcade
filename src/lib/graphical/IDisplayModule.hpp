/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** IDisplayModule
*/

#pragma once
#include <cstddef>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include "../games/IGameModule.hpp"
#include "../games/Entity.hpp"
#include "../games/Prop.hpp"
#include "../games/Text.hpp"

class IDispModule {
    public:
        /// @author Louis
        /// @brief initScreen function
        /// @param void
        /// @return bool
        virtual bool initScreen() = 0;

        /// @author Louis
        /// @brief destroyScreen function
        /// @param void
        /// @return bool
        virtual bool destroyScreen() = 0;

        /// @author Louis
        /// @brief display function
        /// @param void
        /// @return bool
        virtual bool display() = 0;

        /// @author Louis
        /// @brief getUserInput function
        /// @param void
        /// @return Key
        virtual Key getUserInput() = 0;

        /// @author Louis
        /// @brief setUserInput function
        /// @param Key
        /// @return void
        virtual void setUserInput(Key) = 0;

        /// @author Louis
        /// @brief drawEntity function
        /// @param Entity *entity
        /// @return bool
        virtual bool drawEntity(Entity *) = 0;

        /// @author Louis
        /// @brief drawEntity function
        /// @param std::vector<Entity *> entities
        /// @return bool
        virtual bool drawEntity(std::vector<Entity *>) = 0;

        /// @author Louis
        /// @brief drawProp function
        /// @param Prop *prop
        /// @return bool
        virtual bool drawProp(Prop *) = 0;

        /// @author Louis
        /// @brief drawProp function
        /// @param std::vector<Prop *> props
        /// @return bool
        virtual bool drawProp(std::vector<Prop *>) = 0;

        /// @author Louis
        /// @brief drawText function
        /// @param Text *text
        /// @return bool
        virtual bool drawText(Text *) = 0;

        /// @author Louis
        /// @brief drawText function
        /// @param std::vector<Text *> texts
        /// @return bool
        virtual bool drawText(std::vector<Text *>) = 0;

        /// @author Louis
        /// @brief clearAll function
        /// @param void
        /// @return bool
        virtual bool clearAll() = 0;

        /// @author Paul
        /// @brief clearEntity function
        /// @param void
        /// @return bool
        virtual bool clearEntity() = 0;

        /// @author Louis
        /// @brief clearEntity function
        /// @param Id id
        /// @return bool
        virtual bool clearEntity(Id) = 0;

        /// @author Louis
        /// @brief clearEntity function
        /// @param std::vector<Id> ids
        /// @return bool
        virtual bool clearEntity(std::vector<Id>) = 0;

        /// @author Louis
        /// @brief clearProp function
        /// @param Id id
        /// @return bool
        virtual bool clearProp(Id) = 0;

        /// @author Louis
        /// @brief clearProp function
        /// @param std::vector<Id> ids
        /// @return bool
        virtual bool clearProp(std::vector<Id>) = 0;

        /// @author Louis
        /// @brief clearText function
        /// @param Id id
        /// @return bool
        virtual bool clearText(Id) = 0;

        /// @author Louis
        /// @brief clearText function
        /// @param std::vector<Id> ids
        /// @return bool
        virtual bool clearText(std::vector<Id>) = 0;

        /// @author Louis
        /// @brief addText function
        /// @param Text *text
        /// @return bool
        virtual bool addText(Text *) = 0;

        /// @author Louis
        /// @brief addEntity function
        /// @param Entity *entity
        /// @return bool
        virtual bool addEntity(Entity *) = 0;

        /// @author Louis
        /// @brief addProp function
        /// @param Prop *prop
        /// @return bool
        virtual bool addProp(Prop *) = 0;

        // Clear & draw

        /// @author Louis
        /// @brief update function
        /// @param void
        /// @return bool
        virtual bool update() = 0;

        /// @author Louis
        /// @brief updateEntity function
        /// @param Id id
        /// @param Entity *entity
        /// @return bool
        virtual bool updateEntity(Id, Entity *) = 0;

        /// @author Louis
        /// @brief updateEntity function
        /// @param std::vector<std::pair<Id, Entity *>> entities
        /// @return bool
        virtual bool updateEntity(std::vector<std::pair<Id, Entity *>>) = 0;

        /// @author Paul
        /// @brief getEntities function
        /// @param void
        /// @return std::vector<Entity *>
        virtual std::vector<Entity *> getEntities() = 0;

        /// @author Louis
        /// @brief updateProp function
        /// @param Id id
        /// @param Prop *prop
        /// @return bool
        virtual bool updateProp(Id, Prop *) = 0;

        /// @author Louis
        /// @brief updateProp function
        /// @param std::vector<std::pair<Id, Prop *>> props
        /// @return bool
        virtual bool updateProp(std::vector<std::pair<Id, Prop *>>) = 0;

        /// @author Louis
        /// @brief updateText function
        /// @param Id id
        /// @param Text *text
        /// @return bool
        virtual bool updateText(Id, Text *) = 0;

        /// @author Louis
        /// @brief updateText function
        /// @param std::vector<std::pair<Id, Text *>> texts
        /// @return bool
        virtual bool updateText(std::vector<std::pair<Id, Text *>>) = 0;

        // Puterror

        /// @author Louis
        /// @brief displayError function
        /// @param void
        /// @return bool
        virtual bool displayError() = 0;

        /// @author Louis
        /// @brief sceneSwitch function
        /// @param void
        /// @return bool
        virtual bool sceneSwitch() = 0;

        // Useless

        /// @author Louis
        /// @brief getFPS function
        /// @param void
        /// @return int
        virtual int getFPS() = 0;

        // check if lib works
        // Useless

        /// @author Louis
        /// @brief debug function
        /// @param void
        /// @return bool
        virtual bool debug() = 0;

        /// @author Louis
        /// @brief getRes function
        /// @param void
        /// @return std::vector<float>
        virtual std::vector<float> getRes() = 0;

        /// @author Louis
        /// @brief getSize function
        /// @param void
        /// @return std::vector<float>
        virtual std::vector<float> getSize() = 0;

        /// @author Louis
        /// @brief changeScore function
        /// @param int add
        /// @return bool
        virtual bool changeScore(int add) = 0;

        /// @author Louis
        /// @brief getScore function
        /// @param void
        /// @return int
        virtual int getScore() = 0;

        /// @author Paul
        /// @brief getHighScore function
        /// @param void
        /// @return int
        virtual int getHighScore() = 0;

        /// @author Louis
        /// @brief setScore function
        /// @param int score
        /// @return bool
        virtual bool setScore(int score) = 0;

        /// @author Paul
        /// @brief setHighScore function
        /// @param int score
        /// @return bool
        virtual bool setHighScore(int score) = 0;

        /// @author Paul
        /// @brief writeScore function
        /// @param void
        /// @return bool
        virtual bool writeScore() = 0;
};

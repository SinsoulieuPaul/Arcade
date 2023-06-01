/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** AGame
*/


#ifndef AGAME_HPP_
#define AGAME_HPP_
#include "IGameModule.hpp"
#include "Prop.hpp"
#include "Entity.hpp"
#include "Text.hpp"
#include <iostream>

/// @brief AGame class
/// @author Louis
/// @date 2023-15-03
/// @details
/// This class is the base class for all games
/// It contains all the functions that are needed for a game
/// It is an abstract class
class AGame : public IGameModule {
    public:

        /// @author Louis
        /// @brief AGame constructor
        /// @param void
        AGame();

        /// @author Louis
        /// @brief AGame destructor
        /// @param void
        ~AGame();

        State systemInit() override;
        State systemStart() override;
        State systemStop() override;
        State systemClear() override;
        State systemUpdate() override;
        State systemGetState() const override;
        void systemSetState(State) override;
        void systemOnUserInput(int) override;
        void systemDebug() override;

        // Entity functions
        std::vector<Entity *> entityGetAll() override;
        Entity* entityGet(Id) override;
        Entity* entityGet(Name) override;
        std::vector<Entity *> entityGetAllOfType(EntityType) override;
        Id entityGetId(Name) override;
        Name entityGetName(Id) override;
        std::vector<float> entityGetProperty(Id, Property) override;
        bool entityUpdate(Id, Property, int) override;
        bool entityUpdate(Id, Property, float) override;
        bool entityUpdate(Id, Property, std::vector<float>) override;
        bool entityUpdate(Id, Property, std::vector<int>) override;
        bool entityUpdate(Id, Property, Name) override;
        bool entityPush(Entity) override;
        bool entityPush_front(Entity) override;
        bool entityRemove(Id) override;
        bool entityPop() override;
        bool entityPop_front() override;
        bool entityClearAll() override;

        // Text functions
        std::vector<Text *> textGetAll() override;

        // Prop functions
        std::vector<Prop *> propGetAll() override;
        Prop propGet(Id) override;
        std::vector<Prop *> propGetAllOfType(PropType) override;
        std::vector<float> propGetProperty(Id, Property) override;
        bool propUpdate(Id, Property, int) override;
        bool propUpdate(Id, Property, float) override;
        bool propUpdate(Id, Property, std::vector<float>) override;
        bool propUpdate(Id, Property, std::vector<int>) override;
        bool propUpdate(Id, Property, Name) override;
        bool propPush(Prop) override;
        bool propPush_front(Prop) override;
        bool propRemove(Id) override;
        bool propPop() override;
        bool propPop_front() override;
        bool propClearAll() override;

        // Score functions
        int getScore() const override;
        void setScore(int score) override;

    private:
        std::vector<Prop *> _props;
        std::vector<Entity *> _entities;
        std::vector<Text *> _texts;
        State _state;
        int _score;

};

#endif /* !AGAME_HPP_ */

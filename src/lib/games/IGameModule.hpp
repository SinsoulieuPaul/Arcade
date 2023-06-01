/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** IGameModule
*/

#include <cstddef>
#include <string>
#include <map>
#include <vector>
#include <memory>

#pragma once

enum Key {
    Z,
    Q,
    S,
    D,
    R,
    L,
    G,
    Enter,
    Escape,
    None
};

enum EntityType {
    Player,
    Enemy,
    Mob,
};

enum PropType {
    Wall,
    Door,
    Invisible,
    Object,
    Button
};

enum TextType {
    Score,
    Other
};

enum Property {
    Velocity,
    Position,
    Health,
    Rotation,
    Type,
};

enum State {
    Paused,
    Init,
    Started,
    Stopped,
    Loading,
    Over,
    Won,
    Failed,
    Error,
    Cleared,
    Updated,
};

typedef std::size_t Id;
typedef std::string *Name;

class Entity;
class Prop;
class Text;

class IGameModule {
    public:
        // System functions

        /// @author Louis
        /// @brief systemInit function
        /// @param void
        /// @return State
        virtual State systemInit() = 0;

        /// @author Louis
        /// @brief systemStart function
        /// @param void
        /// @return State
        virtual State systemStart() = 0;

        /// @author Louis
        /// @brief systemStop function
        /// @param void
        /// @return State
        virtual State systemStop() = 0;

        /// @author Louis
        /// @brief systemClear function
        /// @param void
        /// @return State
        virtual State systemClear() = 0;

        /// @author Louis
        /// @brief systemUpdate function
        /// @param void
        /// @return State
        virtual State systemUpdate() = 0;

        /// @author Louis
        /// @brief systemGetState function
        /// @param void
        /// @return State
        virtual State systemGetState() const = 0;

        /// @author Louis
        /// @brief systemSetState function
        /// @param State state
        /// @return void
        virtual void systemSetState(State) = 0;

        /// @author Louis
        /// @brief systemOnUserInput function
        /// @param int input
        /// @return void
        virtual void systemOnUserInput(int) = 0;

        /// @author Louis
        /// @brief systemDebug function
        /// @param void
        /// @return void
        virtual void systemDebug() = 0;

        // Entity functions

        /// @author Louis
        /// @brief entityGetAll function
        /// @param void
        /// @return std::vector<Entity *>
        virtual std::vector<Entity *> entityGetAll() = 0;

        /// @author Louis
        /// @brief entityGet function
        /// @param Id id
        /// @return Entity *
        virtual ::Entity* entityGet(Id) = 0;

        /// @author Louis
        /// @brief entityGet function
        /// @param Name name
        /// @return Entity *
        virtual ::Entity* entityGet(Name) = 0;

        /// @author Louis
        /// @brief entityGetAllOfType function
        /// @param EntityType type
        /// @return std::vector<Entity *>
        virtual std::vector<::Entity*> entityGetAllOfType(EntityType) = 0;

        /// @author Louis
        /// @brief entitygetId function
        /// @param Name name
        /// @return Id id
        virtual Id entityGetId(Name) = 0;

        /// @author Louis
        /// @brief entityGetName function
        /// @param Id id
        /// @return Name name
        virtual Name entityGetName(Id) = 0;

        /// @author Louis
        /// @brief entityGetProperty function
        /// @param Id id
        /// @param Property property
        /// @return int
        virtual std::vector<float> entityGetProperty(Id, Property) = 0;

        /// @author Louis
        /// @brief entityUpdate function
        /// @param Id id
        /// @param Property property
        /// @param int value
        /// @return bool
        virtual bool entityUpdate(Id, Property, int) = 0;

        /// @author Louis
        /// @brief entityUpdate function
        /// @param Id id
        /// @param Property property
        /// @param float value
        /// @return bool
        virtual bool entityUpdate(Id, Property, float) = 0;

        /// @author Louis
        /// @brief entityUpdate function
        /// @param Id id
        /// @param Property property
        /// @param std::vector<float> value
        /// @return bool
        virtual bool entityUpdate(Id, Property, std::vector<float>) = 0;

        /// @author Louis
        /// @brief entityUpdate function
        /// @param Id id
        /// @param Property property
        /// @param std::vector<int> value
        /// @return bool
        virtual bool entityUpdate(Id, Property, std::vector<int>) = 0;

        /// @author Louis
        /// @brief entityUpdate function
        /// @param Id id
        /// @param Property property
        /// @param Name name
        /// @return bool
        virtual bool entityUpdate(Id, Property, Name) = 0;

        /// @author Louis
        /// @brief entityPush function
        /// @param Entity entity
        /// @return bool
        virtual bool entityPush(::Entity) = 0;

        /// @author Louis
        /// @brief entityPush_front function
        /// @param Entity entity
        /// @return bool
        virtual bool entityPush_front(::Entity) = 0;

        /// @author Louis
        /// @brief entityRemove function
        /// @param Id id
        /// @return bool
        virtual bool entityRemove(Id) = 0;

        /// @author Louis
        /// @brief entityRemove function
        /// @param Name name
        /// @return bool
        virtual bool entityPop() = 0;

        /// @author Louis
        /// @brief entityPop_front function
        /// @param void
        /// @return bool
        virtual bool entityPop_front() = 0;

        /// @author Louis
        /// @brief entityClearAll function
        /// @param void
        /// @return bool
        virtual bool entityClearAll() = 0;

        // Text functions

        /// @author Louis
        /// @brief textGetAll function
        /// @param void
        /// @return std::vector<Text *>
        virtual std::vector<::Text *> textGetAll() = 0;

        // Prop functions

        /// @author Louis
        /// @brief propGetAll function
        /// @param void
        /// @return std::vector<Prop *>
        virtual std::vector<::Prop *> propGetAll() = 0;

        /// @author Louis
        /// @brief propGet function
        /// @param Id id
        /// @return Prop *
        virtual ::Prop propGet(Id) = 0;

        /// @author Louis
        /// @brief propGetAllOfType function
        /// @param PropType type
        /// @return std::vector<Prop *>
        virtual std::vector<::Prop *> propGetAllOfType(PropType) = 0;

        /// @author Louis
        /// @brief propGetProperty function
        /// @param Id id
        /// @param Property property
        /// @return std::vector<float>
        virtual std::vector<float> propGetProperty(Id, Property) = 0;

        /// @author Louis
        /// @brief propUpdate function
        /// @param Id id
        /// @param Property property
        /// @param int value
        /// @return bool
        virtual bool propUpdate(Id, Property, int) = 0;

        /// @author Louis
        /// @brief propUpdate function
        /// @param Id id
        /// @param Property property
        /// @param float value
        virtual bool propUpdate(Id, Property, float) = 0;

        /// @author Louis
        /// @brief propUpdate function
        /// @param Id id
        /// @param Property property
        /// @param std::vector<float> value
        /// @return bool
        virtual bool propUpdate(Id, Property, std::vector<float>) = 0;

        /// @author Louis
        /// @brief propUpdate function
        /// @param Id id
        /// @param Property property
        /// @param std::vector<int> value
        /// @return bool
        virtual bool propUpdate(Id, Property, std::vector<int>) = 0;

        /// @author Louis
        /// @brief propUpdate function
        /// @param Id id
        /// @param Property property
        /// @param Name name
        /// @return bool
        virtual bool propUpdate(Id, Property, Name) = 0;

        /// @author Louis
        /// @brief propPush function
        /// @param Prop prop
        /// @return bool
        virtual bool propPush(::Prop) = 0;

        /// @author Louis
        /// @brief propPush_front function
        /// @param Prop prop
        /// @return bool
        virtual bool propPush_front(::Prop) = 0;

        /// @author Louis
        /// @brief propRemove function
        /// @param Id id
        /// @return bool
        virtual bool propRemove(Id) = 0;

        /// @author Louis
        /// @brief propPop function
        /// @param void
        /// @return bool
        virtual bool propPop() = 0;

        /// @author Louis
        /// @brief propPop_front function
        /// @param void
        /// @return bool
        virtual bool propPop_front() = 0;

        /// @author Louis
        /// @brief propClearAll function
        /// @param void
        /// @return bool
        virtual bool propClearAll() = 0;

        /// @author Paul
        /// @brief getScore function
        /// @param void
        /// @return int
        virtual int getScore() const = 0;

        /// @author Paul
        /// @brief setScore function
        /// @param int score
        /// @return void
        virtual void setScore(int score) = 0;

        /// @author Paul
        /// @brief getHighScore function
        /// @param void
        /// @return int
        virtual int getHighScore() const = 0;

        /// @author Paul
        /// @brief setHighScore function
        /// @param int HighScore
        /// @return void
        virtual void setHighScore(int score) = 0;
};
/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Pacman
*/

#ifndef PACMAN_HPP_
    #define PACMAN_HPP_

#include "../AGame.hpp"
#include <chrono>

class Pacman : public AGame {
    public:
        /// @author Paul
        /// @brief Pacman constructor
        /// @param void
        Pacman();

        /// @author Paul
        /// @brief Pacman destructor
        /// @param void
        ~Pacman();

        State systemInit() override;
        State systemStart() override;
        State systemStop() override;
        State systemClear() override;
        State systemUpdate() override;
        State systemGetState() const override;
        void systemSetState(State) override;
        void systemOnUserInput(int) override;
        void systemDebug() override;
        std::vector<Prop *> propGetAll() override;

        // Entity
                // Entity functions
        std::vector<Entity *> entityGetAll() override;
        Entity * entityGet(Id) override;
        Entity * entityGet(Name) override;
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

        // Text
        std::vector<Text *> textGetAll() override;

        int getScore() const override;
        void setScore(int score) override;
        int getHighScore() const override;
        void setHighScore(int score) override;

        std::vector<Prop *> propGetAllOfType(PropType) override;
        bool propRemove([[maybe_unused]]Id id) override;

    protected:
        State _state;
    private:
        /// @author Louis
        /// @brief _initBackground function
        /// @param void
        /// @return void
        void _initBackground();

        /// @author Louis
        /// @brief _initSnake function
        /// @param void
        /// @return void
        void _initPacman();

        /// @author Louis
        /// @brief _initLabyrinth function
        /// @param void
        /// @return void

        void _initLabyrinth();
        bool _playerCollision();

        int _score;
        int _highScore;
        int _rand = 0;
        std::vector<Entity *> _entities;
        std::vector<Entity *> _player;
        std::vector<Prop *> _props;
        std::vector<Text *> _texts;
        std::chrono::_V2::system_clock::time_point _clock = std::chrono::high_resolution_clock::now();
};

#endif /* !PACMAN_HPP_ */

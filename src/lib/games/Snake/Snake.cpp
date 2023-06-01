/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Snake
*/

#include "Snake.hpp"
#include "../../../core/Core.hpp"

extern Core *g_core;
#include <cmath>
#include <random>
#include <vector>
#include <algorithm>

Snake::Snake()
{
    this->direction = "right";
}

Snake::~Snake()
{
}

/* @author Louis
    @brief systemInit function
    @param void
    @return State
*/

State Snake::systemInit()
{
    std::cout << "Snake init" << std::endl;
    this->_state = Init;
    this->_initBackground();
    this->_initSnake();
    this->_initFood();
    return _state;
}

/* @author Louis
    @brief systemStart function
    @param void
    @return State
*/

State Snake::systemStart()
{
    this->_state = Started;
    return _state;
}

/* @author Louis
    @brief systemStop function
    @param void
    @return State
*/

State Snake::systemStop()
{
    this->_state = Stopped;
    return _state;
}

/* @author Louis
    @brief systemClear function
    @param void
    @return State
*/

State Snake::systemClear()
{
    this->_state = Cleared;
    return _state;
}

/* @author Louis
    @param void
    @return State
*/

State Snake::systemGetState() const
{
    return _state;
}

/* @author Louis
    @brief systemSetState function
    @param State
    @return void
*/

void Snake::systemSetState(State state)
{
    this->_state = state;
}

/* @author Louis
    @brief systemOnUserInput function
    @param int
    @return void
*/


void Snake::systemOnUserInput([[maybe_unused]]int input )
{
    std::vector<Entity *> entities = entityGetAll();
    std::map<Property, std::vector<float>> properties = entities[0]->getProperties();
    if (input == Key::D && this->direction == "right") {
        entities[0]->setProperty(Velocity, std::vector<float>{0, 4});
        this->direction = "down";
    } else if (input == Key::D && this->direction == "left") {
        entities[0]->setProperty(Velocity, std::vector<float>{0, -4});
        this->direction = "up";
    } else if (input == Key::D && this->direction == "up") {
        entities[0]->setProperty(Velocity, std::vector<float>{4, 0});
        this->direction = "right";
    } else if (input == Key::D && this->direction == "down") {
        entities[0]->setProperty(Velocity, std::vector<float>{-4, 0});
        this->direction = "left";
    } else if (input == Key::Q && this->direction == "right") {
        entities[0]->setProperty(Velocity, std::vector<float>{0, -4});
        this->direction = "up";
    } else if (input == Key::Q && this->direction == "left") {
        entities[0]->setProperty(Velocity, std::vector<float>{0, 4});
        this->direction = "down";
    } else if (input == Key::Q && this->direction == "up") {
        entities[0]->setProperty(Velocity, std::vector<float>{-4, 0});
        this->direction = "left";
    } else if (input == Key::Q && this->direction == "down") {
        entities[0]->setProperty(Velocity, std::vector<float>{4, 0});
        this->direction = "right";
    }
    _rotateSnake();
}

void Snake::_stockPos() {
    float gridSizeX = 50.0f;
    float gridSizeY = 37.5f;
    for (std::size_t i = 0; i < this->_entities.size(); i++) {
        std::vector<float> pos = this->_entities[i]->getProperty(Position);
        // Align the position with the grid
        pos[0] = std::round(pos[0] / gridSizeX) * gridSizeX;
        pos[1] = std::round(pos[1] / gridSizeY) * gridSizeY;
        _snakePos[i] = pos;
    }
}

void Snake::_rotateSnake() {
    // Move head
    const float gridWidth = 800.0f - (16 * 2);
    const float gridHeight = 600.0f - (16 * 2) - 32;
    Entity* head = this->_entities[0];
    std::vector<float> headPosition = head->getProperty(Position);
    std::vector<float> headVelocity = head->getProperty(Velocity);
    headPosition[0] += headVelocity[0];
    headPosition[1] += headVelocity[1];
    // Wrap the head position around the grid
    headPosition[0] = std::fmod(headPosition[0] + gridWidth, gridWidth);
    headPosition[1] = std::fmod(headPosition[1] + gridHeight, gridHeight);
    head->setProperty(Position, headPosition);

    // Set the rotation of the head
    float angle = std::atan2(headVelocity[1], headVelocity[0]) * 180.0f / 3.14159265358979323846f;
    head->setProperty(Rotation, std::vector<float> {angle});

    // Move body
    for (std::size_t i = 1; i < this->_entities.size(); i++) {
        Entity* body = this->_entities[i];
        Entity* previousBody = this->_entities[i - 1];
        std::vector<float> bodyPosition = body->getProperty(Position);
        std::vector<float> bodyVelocity = body->getProperty(Velocity);
        std::vector<float> previousBodyPosition = previousBody->getProperty(Position);
        std::vector<float> previousBodyVelocity = previousBody->getProperty(Velocity);
        float dx = previousBodyPosition[0] - bodyPosition[0];
        float dy = previousBodyPosition[1] - bodyPosition[1];
        float distanceToPreviousBody = std::sqrt(dx * dx + dy * dy);
        float speedFactor = distanceToPreviousBody / 8.0f;
        bodyVelocity[0] = dx / distanceToPreviousBody * speedFactor;
        bodyVelocity[1] = dy / distanceToPreviousBody * speedFactor;
        bodyPosition[0] += bodyVelocity[0];
        bodyPosition[1] += bodyVelocity[1];
        // Wrap the body position around the grid
        bodyPosition[0] = std::fmod(bodyPosition[0] + gridWidth, gridWidth);
        bodyPosition[1] = std::fmod(bodyPosition[1] + gridHeight, gridHeight);
        body->setProperty(Velocity, bodyVelocity);
        body->setProperty(Position, bodyPosition);

        // Set the rotation of the body
        float angle = std::atan2(previousBodyVelocity[1], previousBodyVelocity[0]) * 180.0f / 3.14159265358979323846f;
        body->setProperty(Rotation, std::vector<float> {angle});
    }

    // Check for collisions

    // Check if the head is colliding with the body
    for (std::size_t i = 1; i < this->_entities.size(); i++) {
        Entity* body = this->_entities[i];
        std::vector<float> bodyPosition = body->getProperty(Position);
        std::vector<float> headPosition = head->getProperty(Position);
        float dx = headPosition[0] - bodyPosition[0];
        float dy = headPosition[1] - bodyPosition[1];
        float distanceToBody = std::sqrt(dx * dx + dy * dy);
        if (distanceToBody < 8.0f) {
            systemStop();
        }
    }

    // Check if the head is colliding with the walls

    float headSize = 16.0f;
    float headLeft = headPosition[0] - headSize;
    float headRight = headPosition[0] + headSize;
    float headTop = headPosition[1] - headSize;
    float headBottom = headPosition[1] + headSize;

    // Check for collisions with each wall
    for (auto wall : propGetAllOfType(Wall)) {
        std::vector<float> wallPosition = wall->getProperty(Position);
        float wallWidth = 16.0f;
        float wallHeight = 16.0f;

        // Calculate the positions of the corners of the collision boxes
        float wallLeft = wallPosition[0] - wallWidth/2;
        float wallRight = wallPosition[0] + wallWidth/2;
        float wallTop = wallPosition[1] - wallHeight/2;
        float wallBottom = wallPosition[1] + wallHeight/2;

        // Check for a collision with this wall
        if ((headRight > wallLeft && headLeft < wallRight &&
            headBottom > wallTop && headTop < wallBottom) || headLeft < 2 * 16 || headRight > 800 || headTop < 2 * 16 || headBottom > 600) {
            systemStop();
        }
    }


}







float Snake::_getRandomFloat(float min, float max, std::vector<float> forbidden)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);

    float random = dis(gen);
    for (auto value : forbidden) {
        if (random == value) {
            random = _getRandomFloat(min, max, forbidden);
        }
    }
    return random;
}

/* @author Louis
    @brief systemDebug function
    @param void
    @return void
*/

void Snake::systemDebug()
{
    std::cout << "Snake debug" << std::endl;
}

/* @author Louis
    @brief systemUpdate function
    @param void
    @return State
*/
State Snake::systemUpdate()
{
    this->_state = Updated;

    Entity *head = this->_entities[0];
    // float tolerance = 32; // Valeur de tolérance pour l'erreur de position

    const int box_size = 16; // taille de la boîte de collision
    for (auto prop : propGetAllOfType(Object)) {
        if (*prop->getName() == "food") {
            std::vector<float> foodPosition = prop->getProperty(Position);
            std::vector<float> headPosition = head->getProperty(Position);

            // calcul des coordonnées de la boîte de collision pour la nourriture et la tête
            float foodLeft = foodPosition[0] - box_size;
            float foodRight = foodPosition[0] + box_size;
            float foodTop = foodPosition[1] - box_size;
            float foodBottom = foodPosition[1] + box_size;

            float headLeft = headPosition[0] - box_size;
            float headRight = headPosition[0] + box_size;
            float headTop = headPosition[1] - box_size;
            float headBottom = headPosition[1] + box_size;

            // test de collision
            if (foodLeft <= headRight && foodRight >= headLeft && foodTop <= headBottom && foodBottom >= headTop) {
                setScore(getScore() + 100);
                std::vector<float> bodyPosition = this->_entities[this->_entities.size() - 1]->getProperty(Position);
                std::vector<float > bodyVelocity = this->_entities[this->_entities.size() - 1]->getProperty(Velocity);
                Entity *lastbody = new Entity(Player, bodyPosition);
                lastbody->setProperty(Velocity, bodyVelocity);
                lastbody->setSpriteChar('=');
                lastbody->setSpritePath(new std::string("assets/snake/snake_middle_tail.png"));
                this->_entities.insert(this->_entities.end() - 1, lastbody);
                if (_rand % 2 == 0) {
                    std::vector<float> lstA;
                    for (auto entity : entityGetAll()) {
                        std::map<Property, std::vector<float>> properties = entity->getProperties();
                        lstA.push_back(properties[Position][0]);
                    }
                    for (auto prop : propGetAllOfType(Wall)) {
                        std::vector<float> propPosition = prop->getProperty(Position);
                        lstA.push_back(propPosition[0]);
                    }

                    float x = _getRandomFloat(48, 752, lstA);
                    float y = _getRandomFloat(48, 470, std::vector<float>{0});
                    prop->setProperty(Position, std::vector<float>{x, y});
                } else {
                    std::vector<float> lstB;
                    for (auto entity : entityGetAll()) {
                        std::map<Property, std::vector<float>> properties = entity->getProperties();
                        lstB.push_back(properties[Position][1]);
                    }

                    float x = _getRandomFloat(48, 752, std::vector<float>{0});
                    float y = _getRandomFloat(48, 470, lstB);
                    prop->setProperty(Position, std::vector<float>{x, y});
                }

                _rand += 1;
                // std::vector<Prop *> props = propGetAll();
                // for (std::size_t i = 0; i < props.size(); i++) {
                //     if(props[i] == prop) {
                //         propRemove(i);
                //     }
                // }
            }
        }
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - _clock);
    if (timeElapsed.count() >= 30) {
        _clock = currentTime;
        _rotateSnake();
    }
    return _state;
}

bool Snake::propRemove([[maybe_unused]]Id id) {
    if (id < this->_props.size()) {
        this->_props.erase(this->_props.begin() + id);
        return true;
    }
    return false;
}
// Entity


std::vector<Entity *> Snake::entityGetAll()
{
    return this->_entities;
}


Entity * Snake::entityGet(Id index)
{
    return this->_entities[index];
}

Entity * Snake::entityGet(Name name)
{
    for (auto &entity : this->_entities) {
        if (entity->getName() == name)
            return entity;
    }
    return new Entity();
}

Id Snake::entityGetId(Name name)
{
    for (std::size_t i = 0; i < this->_entities.size(); i++) {
        if (this->_entities[i]->getName() == name)
            return i;
    }
    return 0;
}

Name Snake::entityGetName(Id index)
{
    return this->_entities[index]->getName();
}


std::vector<Entity *> Snake::entityGetAllOfType(EntityType type)
{
    std::vector<Entity *> entities;
    for (auto &entity : this->_entities) {
        if ((int)entity->getProperty(Type)[0] == type)
            entities.push_back(entity);
    }
    return entities;
}


// Prop

void Snake::_initBackground()
{
    int nb_cases = 25 * 17;
    int x = 0;
    int y = 0;
    for (int i = 0; i < nb_cases; i++) {
        if (x == 25) {
            x = 0;
            y++;
        }
        if (x == 0 || x == 24 || y == 0 || y == 16) {
            Prop *prop = new Prop(Wall, std::vector<float>{(float)x, (float)y});
            prop->setSpritePath(new std::string("assets/snake/snake_wall.png"));
            prop->setSpriteChar('X');
            prop->setProperty(Position, std::vector<float>{(float)(x * 32), (float)(y * 32)});
            this->_props.push_back(prop);
        } else {
            if (y % 2 == 0) {
                if (x % 2 == 0) {
                    Prop *prop = new Prop(Invisible, std::vector<float>{(float)x, (float)y});
                    prop->setSpritePath(new std::string("assets/snake/snake_bg_1.png"));
                    prop->setSpriteChar(' ');
                    prop->setProperty(Position, std::vector<float>{(float)(x * 32), (float)(y * 32)});
                    this->_props.push_back(prop);
                } else {
                    Prop *prop = new Prop(Invisible, std::vector<float>{(float)x, (float)y});
                    prop->setSpritePath(new std::string("assets/snake/snake_bg_2.png"));
                    prop->setSpriteChar(' ');
                    prop->setProperty(Position, std::vector<float>{(float)(x * 32), (float)(y * 32)});
                    this->_props.push_back(prop);
                }
            } else {
                if (x % 2 == 0) {
                    Prop *prop = new Prop(Invisible, std::vector<float>{(float)x, (float)y});
                    prop->setSpritePath(new std::string("assets/snake/snake_bg_2.png"));
                    prop->setSpriteChar(' ');
                    prop->setProperty(Position, std::vector<float>{(float)(x * 32), (float)(y * 32)});
                    this->_props.push_back(prop);
                } else {
                    Prop *prop = new Prop(Invisible, std::vector<float>{(float)x, (float)y});
                    prop->setSpritePath(new std::string("assets/snake/snake_bg_1.png"));
                    prop->setSpriteChar(' ');
                    prop->setProperty(Position, std::vector<float>{(float)(x * 32), (float)(y * 32)});
                    this->_props.push_back(prop);
                }
            }
        }
        x++;
    };

}


void Snake::_initFood()
{
    srand(time(NULL));
    const float generationWidth = 700.f;

    Prop *prop = new Prop(Object, std::vector<float>{50, 40});
    prop->setSpritePath(new std::string("assets/snake/snake_apple.png"));
    prop->setSpriteChar('O');
    prop->setName(new std::string("food"));
    float x = (float)(rand() % (int)generationWidth);
    float y = 161;
    prop->setProperty(Position, std::vector<float>{x, y});
    this->_props.push_back(prop);
}

void Snake::_initSnake()
{
    Entity *head = new Entity(Player, std::vector<float>{16.0f * 27, 16.0f * 16});
    head->setSpritePath(new std::string("assets/snake/snake_head.png"));
    head->setProperty(Velocity, std::vector<float>{4.0f, 0});
    head->setSpriteChar('D');
    head->setProperty(Type, std::vector<float>{(float)Player});
    head->setProperty(Health, std::vector<float>{100});
    head->setName(new std::string("Snake"));
    // _snakePos.push_back(head->getProperties()[Position]);

    Entity *body = new Entity(Player, std::vector<float>{16.0f * 25, 16.0f * 16});
    body->setSpritePath(new std::string("assets/snake/snake_middle_tail.png"));
    body->setProperty(Velocity, std::vector<float>{4.0f, 0});
    body->setSpriteChar('=');
    body->setProperty(Type, std::vector<float>{(float)Player});
    body->setProperty(Health, std::vector<float>{100});
    body->setName(new std::string("Snake"));

    Entity *body2 = new Entity(Player, std::vector<float>{16.0f * 23, 16.0f * 16});
    body2->setSpritePath(new std::string("assets/snake/snake_middle_tail.png"));
    body2->setProperty(Velocity, std::vector<float>{4.0f, 0});
    body2->setSpriteChar('=');
    body2->setProperty(Type, std::vector<float>{(float)Player});
    body2->setProperty(Health, std::vector<float>{100});
    body2->setName(new std::string("Snake"));

    Entity *tail = new Entity(Player, std::vector<float>{16.0f * 21, 16.0f * 16});
    tail->setSpritePath(new std::string("assets/snake/snake_end_tail.png"));
    tail->setProperty(Velocity, std::vector<float>{4.0f, 0});
    tail->setSpriteChar('C');
    tail->setProperty(Type, std::vector<float>{(float)Player});
    tail->setProperty(Health, std::vector<float>{100});
    tail->setName(new std::string("Snake"));

    std::string *score_text = new std::string("Score: 0");
    std::string *score_font = new std::string("assets/fonts/Roboto-Regular.ttf");
    Text *score = new Text(score_text, score_font, std::vector<float>{320, 560}, Score);

    this->_entities.push_back(head);
    this->_entities.push_back(body);
    this->_entities.push_back(body2);
    this->_entities.push_back(tail);

    this->_player.push_back(head);
    this->_player.push_back(body);
    this->_player.push_back(body2);
    this->_player.push_back(tail);

    Prop *prop = new Prop(Button);
    prop->setProperty(Position, std::vector<float>{(0), (35*16)});
    prop->setSpritePath(new std::string("assets/buttons/load_button.png"));
    prop->setSpriteChar('L');
    this->_props.push_back(prop);

    this->_texts.push_back(score);
}

extern "C" std::shared_ptr<IGameModule> createLib()
{
    return std::make_shared<Snake>();
}

std::vector<float> Snake::entityGetProperty(Id index, Property property)
{
    return this->_entities[index]->getProperty(property);
}

bool Snake::entityUpdate(Id index, Property property, int value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Snake::entityUpdate(Id index, Property property, std::vector<float> value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Snake::entityUpdate(Id index, Property property, float value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Snake::entityUpdate(Id index, Property property, std::vector<int> value)
{
    this->_entities[index]->setProperty(property, value);
    return true;
}

bool Snake::entityUpdate(Id index, Property property, Name value)
{
    (void)index;
    (void)property;
    (void)value;
    return true;
}

bool Snake::entityPush(Entity entity)
{
    this->_entities.push_back(new Entity(entity));
    return true;
}

bool Snake::entityPush_front(Entity entity)
{
    this->_entities.insert(this->_entities.begin(), new Entity(entity));
    return true;
}

bool Snake::entityRemove(Id index)
{
    this->_entities.erase(this->_entities.begin() + index);
    return true;
}

bool Snake::entityPop()
{
    this->_entities.pop_back();
    return true;
}

bool Snake::entityPop_front()
{
    this->_entities.erase(this->_entities.begin());
    return true;
}

bool Snake::entityClearAll()
{
    this->_entities.clear();
    return true;
}

/*  @author Paul
    @brief getScore function
    @param void
    @return int
*/
int Snake::getScore() const
{
    return this->_score;
}

/*  @author
    @brief setScore function
    @param int
    @return void
*/
void Snake::setScore(int score)
{
    this->_score = score;
}

/*  @author Paul
    @brief getHighScore function
    @param void
    @return int
*/
int Snake::getHighScore() const
{
    return this->_highScore;
}

/*  @author
    @brief setHighScore function
    @param int
    @return void
*/
void Snake::setHighScore(int score)
{
    this->_highScore = score;
}

/*  @author
    @brief textGetAll function
    @param void
    @return std::vector<Text *>
*/
std::vector<Text *> Snake::textGetAll()
{
    return this->_texts;
}

std::vector<Prop *> Snake::propGetAll()
{
    return this->_props;
}

std::vector<Prop *> Snake::propGetAllOfType(PropType type)
{
    std::vector<Prop *> props;

    for (auto &prop : this->_props) {
        if (prop->getType() == type)
            props.push_back(prop);
    }
    return props;
}
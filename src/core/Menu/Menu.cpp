/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{

}

Menu::~Menu()
{
}

extern "C" std::shared_ptr<IGameModule> createLib()
{
    std::cout << "Creating Menu" << std::endl;
    return std::make_shared<Menu>();
}

State Menu::systemInit()
{
    _state = Init;
    _gameLibs =
    {
        "arcade_snake.so",
        "arcade_nibbler.so",
        "arcade_pacman.so",
        "arcade_solarfox.so",
        "arcade_centipede.so",
        "arcade_qix.so"
    };

    _graphLibs =
    {
        "arcade_sfml.so",
        "arcade_ncurses.so",
        "arcade_sdl2.so",
        "arcade_ndk++.so",
        "arcade_opengl.so",
        "arcade_vulkan.so",
        "arcade_qt5.so",
        "arcade_gtk+.so",
        "arcade_irrlicht.so",
        "arcade_xlib.so",
        "arcade_allegro5.so",
        "arcade_libcaca.so",
        "arcade_aalib.so",
        "arcade_ndk++.so"
    };

    for (const auto &entry : std::filesystem::directory_iterator(libPath)) {
        std::string path = entry.path();
        for (auto &game : _gameLibs) {
            if (path.substr(path.find_last_of("/") + 1) == game) {
                _gameFounds.push_back(path);
            }
        }
    }
    for (const auto &entry : std::filesystem::directory_iterator(libPath)) {
        std::string path = entry.path();
        for (auto &graphic : _graphLibs) {
            if (path.substr(path.find_last_of("/") + 1) == graphic) {
                _graphFounds.push_back(path);
            }
        }
    }
    _initMenu();
    return _state;
}

void Menu::_initMenu()
{
    float i = 1;
    std::string *font = new std::string("assets/fonts/Roboto-Regular.ttf");
    Text *arrow = _gameFounds.empty() == false ? new Text(new std::string (">"), font, std::vector<float>{16, (9*16)}, Other)
       : new Text (new std::string ("No game found"), font, std::vector<float>{16, (9*16)}, Other);

    Text *ascii = new Text(new std::string ("Arcade"), font, std::vector<float>{0, 0}, Other);
    Text *glibs = new Text(new std::string ("List of Available graphical libraries:"), font, std::vector<float>{(16*29), (8*16)}, Other);
    Text *games = new Text(new std::string ("List of Available Games:"), font, std::vector<float>{0, (8*16)}, Other);
    this->_texts.push_back(ascii);
    this->_texts.push_back(games);
    this->_texts.push_back(glibs);
    this->_texts.push_back(arrow);

    Prop *prop = new Prop(Button);
    prop->setProperty(Position, std::vector<float>{(0), (35*16)});
    prop->setSpritePath(new std::string("assets/buttons/load_button.png"));
    prop->setSpriteChar('L');
    this->_props.push_back(prop);

    for (auto graphlibs : _graphFounds) {
        std::string *test = new std::string(graphlibs);
        Text *text = new Text(test, font, std::vector<float>{(16*29), ((i*16) + 8*16)}, Other);
        this->_texts.push_back(text);
        i++;
    }

    i = 1;
    for (auto game : _gameFounds) {
        std::string *test = new std::string(game);
        Text *text = new Text(test, font, std::vector<float>{32, ((i*16) + 8*16)}, Other);
        this->_texts.push_back(text);
        i++;
    }

    std::string *scoreText = new std::string("HighScore:");

    std::ifstream file("score.txt");
    float j = 0;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            scoreText->append(" ");
            scoreText->append(line);
            j++;
        }
        file.close();
    } else {
        scoreText->append(" 0");
    }

    Text *score = new Text(scoreText, font, std::vector<float>{0, (16*16)}, Other);
    this->_texts.push_back(score);

    _i = i - _gameFounds.size();
    _state = Started;
}

void Menu::systemOnUserInput(int input)
{
    if (input == Key::Z && _i > 1) {
        _i--;
        _texts[3]->setProperty(Position, {16, ((_i*16) + 8*16)});
    } else if (input == Key::S && _i < _gameFounds.size()) {
        _i++;
        _texts[3]->setProperty(Position, {16, ((_i*16) + 8*16)});
   }
}

int Menu::getScore() const {
    return _i - 1;
}

int Menu::getHighScore() const {
    return 0;
}

void Menu::setScore([[maybe_unused]] int score) {
    return;
}

void Menu::setHighScore([[maybe_unused]] int score) {
    return;
}

State Menu::systemStop() {
    _state = Stopped;
    return _state;
}

std::vector<Text *> Menu::textGetAll()
{
    return this->_texts;
}

std::vector<Prop *> Menu::propGetAll()
{
    return this->_props;
}

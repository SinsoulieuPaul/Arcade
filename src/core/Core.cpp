/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** Core
*/

#include "Core.hpp"
#include <chrono>
#include <thread>


Core::Core(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: ./arcade [lib.so]" << std::endl;
        throw CoreException("Wrong number of arguments");
    }
    _gameIndex = 0;
    _graphicalIndex = -1;
    _reloaded = false;
    _loadLibs();
    _chooseLibs(new std::string(av[1]));
    _createMenu();
    _runGame();
}

Core::~Core()
{
}

void Core::_loadLibs()
{
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
}

void Core::_createMenu()
{
    std::cout << "Loading game lib: " << "./lib/menu.so" << std::endl;
    void *handle = dlopen("./lib/menu.so", RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen error: " << dlerror() << std::endl;
        throw CoreException("Cannot open lib / Missing Permission");
    }
    _gameLib = (std::shared_ptr<IGameModule> (*)())dlsym(handle, "createLib");
    if (!_gameLib) {
        std::cerr << "dlsym error: " << dlerror() << std::endl;
        throw CoreException("Cannot load createLib function, please add it to your lib");
    }
    _game.operator=(_gameLib());
    _game.get()->systemInit();
    try {
        _module.get()->initScreen();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw CoreException("Cannot init screen");
    }
    std::vector<Text *> texts = _game.get()->textGetAll();
    for (auto text : texts) {
        _module.get()->addText(text);
    }

    std::vector<Prop *> props = _game.get()->propGetAll();
    for (auto prop : props) {
        _module.get()->addProp(prop);
    }

    _runMenu();
    // dlclose(handle);
}

void Core::_runMenu()
{
    while (_module.get()->display()) {
        Key userInput = _module.get()->getUserInput();
        if (userInput != Key::None) {
            if (userInput == Key::L) {
                _module.get()->destroyScreen();
                setGraphicalIndex(_graphicalIndex + 1);
                _changeGraphLib();
            } else if (userInput == Key::Enter) {
                setGameIndex(_game.get()->getScore());
                _module.get()->display();
                _module.get()->clearAll();
                _game.get()->systemStop();
                _createGame();
                break;
            } else {
                _game.get()->systemOnUserInput(userInput);
                _module.get()->setUserInput(Key::None);
            }
        }
        // if (_game.get()->getScore() != _module.get()->getScore()) {
        //     _module.get()->changeScore(100);
        // }
    }
    exit(0);
}

void Core::_createGame()
{
    std::cout << "Loading game lib: " << _gameFounds[_gameIndex] << std::endl;
    void *handle = dlopen(_gameFounds[_gameIndex].c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen error: " << dlerror() << std::endl;
        throw CoreException("Cannot open lib / Missing Permission");
    }
    _gameLib = (std::shared_ptr<IGameModule> (*)())dlsym(handle, "createLib");
    if (!_gameLib) {
        std::cerr << "dlsym error: " << dlerror() << std::endl;
        throw CoreException("Cannot load createLib function, please add it to your lib");
    }

    std::ifstream file("score.txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::string *test = new std::string(line);
            try {
                _game.get()->setHighScore(std::stoi(*test));
                _module.get()->setHighScore(std::stoi(*test));
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
        }
        file.close();
    }
    _game.operator=(_gameLib());
    _game.get()->systemInit();
    _game.get()->setScore(0);
    _module.get()->setScore(0);
    std::vector<Text *> texts = _game.get()->textGetAll();
    for (auto text : texts) {
        _module.get()->addText(text);
    }

    std::vector<Prop *> props = _game.get()->propGetAll();
    for (auto prop : props) {
        _module.get()->addProp(prop);
    }
    std::vector<Entity *> entities = _game.get()->entityGetAll();
    for (auto entity : entities) {
        _module.get()->addEntity(entity);
    }
    _runGame();
    dlclose(handle);
}


void Core::_chooseLibs(std::string *lib)
{
    int i = 0;
    for (auto &graphic : _graphLibs) {
        if (lib->substr(lib->find_last_of("/") + 1) == graphic) {
            for (auto gfound : _graphFounds) {
                if (gfound.find(*lib) != std::string::npos)
                    _graphicalIndex = i;
                i++;
            }
            if (_graphicalIndex == -1)
                throw CoreException("No such lib / Wrong lib type");
             _loadGraphLib(lib);
            return;
        }
    }
    throw CoreException("No such lib / Wrong lib type");
}

void Core::_loadGraphLib(std::string *lib)
{
    std::cout << "Loading graphic lib: " << *lib << std::endl;
    void *handle = dlopen(lib->c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "dlopen error: " << dlerror() << std::endl;
        throw CoreException("Cannot open lib / Missing Permission");
    }
    _createLib = (std::shared_ptr<IDispModule> (*)())dlsym(handle, "createLib");
    if (!_createLib) {
        std::cerr << "dlsym error: " << dlerror() << std::endl;
        throw CoreException("Cannot load createLib function, please add it to your lib");
    }

    _module.operator=(_createLib());
}

void Core::_runGame()
{
    while (_module.get()->display()) {
        _game.get()->systemUpdate();
        if (_module.get()->getEntities().size() != _game.get()->entityGetAll().size()) {
            _module.get()->clearEntity();
            for (auto entity : _game.get()->entityGetAll()) {
                _module.get()->addEntity(entity);
            }
        }
        if (_game.get()->systemGetState() == State::Stopped) {
            _module.get()->clearAll();
            _game.get()->systemStop();
            _createMenu();
            break;
        }
        Key userInput = _module.get()->getUserInput();
        if (userInput != Key::None) {
            if (userInput == Key::L && _reloaded == false) {
                _reloaded = true;
                _module.get()->destroyScreen();
                setGraphicalIndex(_graphicalIndex + 1);
                _changeGraphLib();
            // R: reload / Escape: Menu / G: Next game
            } else if (userInput == Key::Escape) {
                _game.get()->systemStop();
                _module.get()->clearAll();
                _createMenu();
                break;
            } else if (userInput == Key::R && _reloaded == false) {
                _reloaded = true;
                _module.get()->clearAll();
                _game.get()->systemStop();
                _createGame();
            } else if (userInput == Key::G && _reloaded == false) {
                _reloaded = true;
                _module.get()->clearAll();
                _game.get()->systemStop();
                std::cout << "Next game" << std::endl;
                setGameIndex(_gameIndex + 1);
                _createGame();
            } else {
                _reloaded = false;
                _game.get()->systemOnUserInput(userInput);
                _module.get()->setUserInput(Key::None);
            }
        }
        if (_game.get()->getScore() != _module.get()->getScore()) {
            _module.get()->changeScore(100);
        }
    }
    _game.get()->systemStop();
    exit(0);
}

void Core::_changeGraphLib()
{
    std::string *lib = &_graphFounds[_graphicalIndex];
    _game.get()->setScore(_module.get()->getScore());
    _game.get()->setHighScore(_module.get()->getHighScore());
    _loadGraphLib(lib);
    try {
        _module.get()->initScreen();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(84);
    }

    std::vector<Text *> texts = _game.get()->textGetAll();
    for (auto text : texts) {
        _module.get()->addText(text);
    }

    std::vector<Prop *> props = _game.get()->propGetAll();
    for (auto prop : props) {
        _module.get()->addProp(prop);
    }
    std::vector<Entity *> entities = _game.get()->entityGetAll();
    for (auto entity : entities) {
        _module.get()->addEntity(entity);
    }
}

void Core::setGameIndex(int index)
{
    int max = {static_cast<int>(_gameFounds.size())};
    if (index < 0 || index > max - 1) {
        _gameIndex = 0;
        return;
    }
    _gameIndex = index;
}

void Core::setGraphicalIndex(int Index)
{
    int max = {static_cast<int>(_graphFounds.size())};
    if (Index < 0 || Index > max - 1) {
        _graphicalIndex = 0;
        return;
    }
    _graphicalIndex = Index;
}

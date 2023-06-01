/*
** EPITECH PROJECT, 2023
** B-OOP-400-LIL-4-1-arcade-bauchart.loic
** File description:
** main
*/

#include "Core.hpp"

int main (int ac, char **av) {
    try
    {
        Core *g_core = new Core(ac, av);
        (void)g_core;
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
        return 84;
    }
}
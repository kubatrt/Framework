#include <iostream>
#include "CatchGame.hpp"

using namespace example;

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl;
    sf::RenderWindow window({1280, 720}, "Catch game");
    CatchGame game(window);
    return game.run();
}

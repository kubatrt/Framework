#include <iostream>
#include "CatchGame.hpp"

// Example "Catch Game"
// TODO: move game logic to state
// TODO: implement catch game logic: player, falling boxes, scoring...
// TODO: use resource manager
// TODO: add animations
// TODO: add sound, consider SoundPlayer from some book

using namespace example;

int main(int argc, char** argv)
{
    std::cout << argv[0] << std::endl;

    CatchGame game;
    return game.run();
}

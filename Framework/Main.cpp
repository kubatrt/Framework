#include <iostream>
#include "Game.hpp"

int main(int argc, char** argv)
{
	std::cout << argv[0] << std::endl;
	framework::Game game;
	return game.run();
}
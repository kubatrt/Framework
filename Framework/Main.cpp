#include <iostream>
#include "CatchGame.hpp"

int main(int argc, char** argv)
{
	std::cout << argv[0] << std::endl;
	CatchGame game;
	return game.run();
}
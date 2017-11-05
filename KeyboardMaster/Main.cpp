#include "KeyboardMaster.hpp"

/* 
	Let's begin from...
	* Game class interface - start from scratch
	* create simple menu scene - this will take much more time that i though
	* run the games from menu and back to it - hah what a whishful thinkind
	* simple "log to file" system - I really encourage you to do this now!
*/

using namespace km;

// int wmain_t(int argc, wchar_t* awgv) // on windows
int main(int argc, char* argv)
{
	KeyboardMaster game;
	return game.run();    // consider passing args
}

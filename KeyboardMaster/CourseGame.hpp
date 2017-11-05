#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <locale>
#include <codecvt>
#include <random>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
//#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>

#include "SimpleApplication.hpp"
#include "VirtualKeyboard.hpp"
#include "CourseText.hpp"
#include "KeyboardTyper.hpp"
#include "Dictionary.hpp"
#include "Misc.hpp"
#include "WordBlock.hpp"

namespace KM
{

class CourseGame : public SimpleApplication
{
    public:
        int run(int argc, char* argv) override;
};

}

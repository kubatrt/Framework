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
#include "Utilities.hpp"
#include "Miscellaneous.hpp"
#include "WordBlock.hpp"

namespace KM
{

class CourseGame : public SimpleApplication
{
    public:
		explicit CourseGame() {}

        CourseGame(const CourseGame&) = delete;
        const CourseGame& operator=(const CourseGame&) = delete;

        virtual int run(int argc, char* argv);
};

}

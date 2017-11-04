#pragma once

#include <SFML/Graphics.hpp>

namespace framework
{

struct IApplication
{
    virtual int run() = 0;
};

}
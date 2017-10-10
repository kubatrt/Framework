#pragma once

namespace framework
{

struct IApplication
{
virtual void onStartup() = 0;
virtual void onDestroy() = 0;
virtual void onEvent() = 0;
virtual void update() = 0;
virtual void draw() = 0;
virtual int run() = 0;
};

}
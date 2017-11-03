#pragma once

namespace framework
{

struct IApplication
{
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual int run() = 0;
};

}
#pragma once

namespace KM
{

class SimpleApplication
{
public:
	SimpleApplication() {};
	virtual ~SimpleApplication() {};

	virtual int run(int argc, char* argv) = 0;
};

}

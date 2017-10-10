#pragma once

#include "gmock/gmock.h"
#include "../FrameworkLib/IApplication.hpp"

class ApplicationMock : public framework::IApplication
{
public:
	MOCK_METHOD0(onStartup, void());
	MOCK_METHOD0(onDestroy, void());
	MOCK_METHOD0(onEvent, void());

	MOCK_METHOD0(update, void());
	MOCK_METHOD0(draw, void());
	MOCK_METHOD0(run, int());
};
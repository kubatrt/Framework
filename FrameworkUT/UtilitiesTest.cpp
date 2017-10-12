#include <iostream>
#include <cmath>
#include <vector>

#include "gtest\gtest.h"

#include "..\FrameworkLib\Utilities.hpp"
#include "..\FrameworkLib\Util\Maths.hpp"

using namespace testing;
using namespace framework;


TEST(VariadicPrint, test)
{
	doPrint(std::cout, "a", "b", "c", "d");
	doPrint(std::cerr, "This", "is", "a", "test");
}

TEST(MathTest, Collision2d)
{
	Point p(1,1);
	Rect rect(0, 0, 2, 2);
	EXPECT_TRUE(collision2d(p, rect));
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	auto ret = RUN_ALL_TESTS();
	std::cin.get();
	return ret;
}
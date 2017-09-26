#include <iostream>
#include "gtest\gtest.h"
#include "..\FrameworkLib\Arithmetic.hpp"

using namespace testing;
using namespace arithmetic;


TEST(Arithmetic, Square)
{
	EXPECT_EQ(square<int>(2,2), 2*2);
}


int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	auto ret = RUN_ALL_TESTS();
	std::cin.get();
	return ret;
}
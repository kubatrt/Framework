#include <memory>
#include "gtest/gtest.h"

#include "ApplicationMock.hpp"


using namespace ::testing;
using namespace framework;

class ApplicationTest : public Test
{
public:
	ApplicationTest()
		: sut_(new ApplicationMock())
	{
		sut_.reset(new ApplicationMock());
	}

	void SetUp()
	{

	}

	void TearDown()
	{

	}

protected:
	std::unique_ptr<IApplication>	sut_;
	ApplicationMock sut2_;
	std::shared_ptr<IApplication> sut3_;
};


TEST_F(ApplicationTest, instanceCreation)
{
	
	//EXPECT_CALL(sut_, onStartup()).Times(AtLeast(1));
	//EXPECT_CALL(sut_, onDestroy()).Times(AtLeast(1));
	
	EXPECT_CALL(sut2_, onStartup()).Times(AtLeast(1));
	EXPECT_CALL(sut2_, onDestroy()).Times(AtLeast(1));

	sut_->onStartup();
	sut_->onDestroy();

	sut2_.onStartup();
	sut2_.onDestroy();


	EXPECT_NO_THROW();
}
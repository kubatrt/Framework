#pragma once

#include <iostream>

namespace framework
{
// todo with std::copy to ostream_iterator
struct Printer
{
	std::ostream& os_;
	Printer(std::ostream& os) : os_(os) {}
	
	template<typename T>
	void operator()(const T& obj) { os_ << obj << " "; }
};

} // framework
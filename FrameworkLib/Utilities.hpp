#pragma once

#include <iostream>

namespace framework
{

struct Printer
{
	std::ostream& os;
	Printer(std::ostream& os) : os(os) {}
	template<typename T>
	void operator()(const T& obj) { os << obj << " "; }
};

} // framework
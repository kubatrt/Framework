#pragma once

#include <iostream>
#include "Util\NonCopyable.hpp"
#include "Util\NonMoveable.hpp"

#define log_inf(text) std::cout << text << std::endl;
#define log_dbg(text) std::cout << text << std::endl;
#define log_err(text) std::cerr << text << std::endl;

typedef unsigned int uint;

namespace framework
{

// print Vector2f

template <typename... Args>
void printVA(std::ostream& out, Args&&... args)
{
	using expander = int[];
	(void)expander { (void(out << ',' << std::forward<Args>(args)),0)... };
	out << std::endl;
}

} // framework
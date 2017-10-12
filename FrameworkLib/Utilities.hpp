#pragma once

#include <iostream>

namespace framework
{

template <typename Arg, typename... Args>
void doPrint(std::ostream& out, Arg&& arg, Args&&... args)
{
	out << std::forward<Arg>(arg);
	using expander = int[];
	(void) expander { 0, (void(out << ',' << std::forward<Args>(args)), 0)... };
}

} // framework
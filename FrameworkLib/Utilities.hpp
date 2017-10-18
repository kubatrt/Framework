#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <cwctype>
#include <random>

#include "Util\NonCopyable.hpp"
#include "Util\NonMoveable.hpp"

// old
#define LOG(msg)    std::wcout << msg << " ::" << __FILE__ << ":" << __LINE__ << std::endl;
#define DEBUG(msg)  std::wcout << "DEBUG: " << msg << std::endl;
#define ERROR(msg)  std::wcerr << "ERROR: " << msg << std::endl;

#define log_inf(text) std::cout << text << std::endl;
#define log_dbg(text) std::cout << text << std::endl;
#define log_err(text) std::cerr << text << std::endl;

typedef unsigned int uint;

namespace framework
{

// old
struct RandomMachine
{
	template<class T>
	static T GetRange(T min, T max)
	{
		std::random_device rd;
		std::default_random_engine re(rd());	//std::mt19937

												// use epoch time as seed for random generator
		long int seed = static_cast<long int>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now().time_since_epoch()).count());
		re.seed(seed);
		std::uniform_int_distribution<T> unif_dist_wordlength(min, max);

		return unif_dist_wordlength(re);
	}
};


namespace charutils	// unused
{

struct Capitalize
{
	void operator()(std::string &str)
	{
		str[0] = toupper(str[0]);
	}
	void operator()(std::wstring &str)
	{
		str[0] = towupper(str[0]);
	}
};

struct Upper
{
	void operator()(std::string &str)
	{
		for (auto& s : str)
		{
			s = toupper(s);
		}
	}
	void operator()(std::wstring &str)
	{
		for (auto& s : str)
		{
			s = towupper(s);
		}
	}
};

struct Lower
{
	void operator()(std::string &str)
	{
		for (auto& s : str)
		{
			s = tolower(s);
		}
	}
	void operator()(std::wstring &str)
	{
		for (auto& s : str)
		{
			s = towlower(s);
		}
	}
};


struct RemoveSpaces
{
	void operator()(std::string& str)
	{
		std::string buffer;
		//str.erase(std::remove_if(str.begin(), str.end(), ' '), str.end());
	}
};

}

// Check intersection with two shapes
template<class T1, class T2>
bool isIntersecting(T1& a, T2& b)
{
	return  a.right() >= b.left() && a.left() <= b.right()
		&& a.top() <= b.bottom() && a.bottom() >= b.top();
}


// print Vector2f
template <typename T>
void printVec(T vec)
{
	std::cout << "("<< vec.x << ", " << vec.y << ")"
}

template <typename... Args>
void printVA(std::ostream& out, Args&&... args)
{
	using expander = int[];
	(void)expander { (void(out << ',' << std::forward<Args>(args)),0)... };
	out << std::endl;
}

} // framework
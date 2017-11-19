#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <cwctype>
#include <random>
//#include <sstream>

#include "Util\NonCopyable.hpp"
#include "Util\NonMoveable.hpp"
#include "Util\Maths.hpp"
#include "Util\Random.hpp"

// !depracted
#define log_info(msg)   std::wcout << msg << std::endl;
#define log_debug(msg)  std::wcout << "(DEBUG): " << msg " ::" << __FILE__ << ":" << __LINE__ << std::endl;
#define log_error(msg)  std::wcerr << "(ERROR): " << msg << std::endl;

typedef unsigned int uint;
using WChar = wchar_t;
using WStr = std::wstring;
using FilePath = std::string;

namespace framework
{

std::vector<std::string> getLinesFromText(const std::string& text);

// !old
struct RandomMachine
{
    template<class T>
    static T getRange(T min, T max)
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

// unused
namespace charutils
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

struct ToUpper
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

struct ToLower
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

}   // charutils



// print Vector2f
template <typename T>
void printVec(T vec)
{
	std::cout << "("<< vec.x << ", " << vec.y << ")";
}

// print variadic argument pack
template <typename... Args>
void printVA(std::ostream& out, Args&&... args)
{
	using expander = int[];
	(void)expander { (void(out << ',' << std::forward<Args>(args)),0)... };
	out << std::endl;
}
} // framework
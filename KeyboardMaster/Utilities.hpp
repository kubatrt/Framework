#pragma once

#include <chrono>
#include <string>
#include <cwctype>
#include <random>

#define LOG(msg)    std::wcout << msg << " ::" << __FILE__ << ":" << __LINE__ << std::endl;
#define DEBUG(msg)  std::wcout << "DEBUG: " << msg << std::endl;
#define ERROR(msg)  std::wcerr << "ERROR: " << msg << std::endl;

// UTF-8 unicode
enum KeyCode : int
{
	EOL = 0,		// special end of line
	Backspace = 8,
	Enter = 13,
	Space = 32,
	q = 113,
	w = 119,
	e = 101,
	r = 114,
	t = 116,
	y = 121,
	u = 117,
	i = 105,
	o = 111,
	p = 112,
	bracketL = 91,
	bracketR = 93,
	backslash = 92,
	a = 97,
	s = 115, 
	d = 100,
	f = 102,
	g = 103,
	h = 104,
	j = 106,
	k = 107,
	l = 108,
	semicolon = 59,
	apostrophe = 39,
	z = 122,
	x = 120,
	c = 99,
	v = 118,
	b = 98,
	n = 110,
	m = 109,
	comma = 44,
	dot = 46,
	slash = 47
};

namespace Characters
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

}

struct RemoveSpace
{
	void operator()(std::string& str)
	{
		std::string buffer;
		//str.erase(std::remove_if(str.begin(), str.end(), ' '), str.end());
	}
};

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

// Check intersection with two shapes
template<class T1, class T2> 
bool IsIntersecting(T1& a, T2& b)
{
	return  a.right() >= b.left() && a.left() <= b.right()
		&& a.top() <= b.bottom() && a.bottom() >= b.top();
}

#ifdef WINDOWS_PLATFORM

/*
// Windows stat prcedure call
size_t GetSizeOfFile(const std::wstring& path)
{
	struct _stat fileinfo;
	_wstat(path.c_str(), &fileinfo);
	return fileinfo.st_size;
}


// Use Windows specific funtion to read wchar_t characters from file
std::wstring LoadUtf8FileToString(const std::wstring& filename)
{
	std::wstring buffer;            // stores file contents
	FILE* f = _wfopen(filename.c_str(), L"rtS, ccs=UTF-8");

	if (f == NULL)
	{
		ERROR("Failed to open file.")
			return buffer;
	}

	size_t filesize = 1;// GetSizeOfFile(filename);

	// Read entire file contents in to memory
	if (filesize > 0)
	{
		buffer.resize(filesize);
		size_t wchars_read = fread(&(buffer.front()), sizeof(wchar_t), filesize, f);
		buffer.resize(wchars_read);
		buffer.shrink_to_fit();
	}

	fclose(f);

	return buffer;
}
*/

#endif

#pragma once

#include <SFML\Graphics.hpp>

namespace km
{

struct IGameComponent
{
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderTarget& renderer) = 0;
};

enum KeyCode : int
{
    // UTF-8 unicode
    EOL = 0,
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


namespace experimental
{

// Check intersection with two shapes
template<class T1, class T2>
bool isIntersecting(T1& a, T2& b)
{
    return  a.right() >= b.left() && a.left() <= b.right()
        && a.top() <= b.bottom() && a.bottom() >= b.top();
}


struct User
{
    std::string name;
    unsigned int courseLevel;   // 0 - 20 deterimnes players skill level
};


struct Session
{
    User user;
    sf::Time timeStarted;
    std::string saveFilePath;

    void save();
    void load();
};


struct GameSession
{
    int score;
    int lives;
    float time;
};


// player game representative object
struct PlayerSpaceShip
{
    sf::Sprite  sprite;
    // animation
    // moving
    // tween position
};




class ILetterTyped
{
public:
    virtual void typedLetter(const wchar_t letter) = 0;
};

class IWordTyped
{
public:
    virtual void typedWord(const std::wstring word) = 0;
};

} // experimental

} // namespace km
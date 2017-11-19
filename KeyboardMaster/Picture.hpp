#pragma	once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "PictureElement.hpp"

namespace km
{

class Picture
{
public:
    Picture();
    Picture(FilePath fileName);
    ~Picture() = default;

    void initialize();
    void loadFromFile(FilePath fileName);

    void show();

private:
    bool visible_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::vector<PictureElement> elements_;
};

}
#pragma	once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Misc.hpp"
#include "PictureElement.hpp"
#include "Dictionary.hpp"
#include <memory>

namespace km
{

class Picture
{
public:
    Picture(sf::Texture texture, uint width, uint height, uint rows, uint cols);
    ~Picture() = default;

    void init();

    bool getVisible() const { return visible_; }
    void setVisible(bool visible) { visible_ = visible; }

    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& renderer);

    void typedWord(std::wstring word);
    bool isComplete();

    // TODO:
    // corectness
    // totalTime

private:
    bool visible_;
    sf::Texture texture_;
    sf::Sprite sprite_;

    uint elementsInRow_;
    uint elementsInCol_;
    uint elementsTotal_;
    uint elementsCorrect_;

    bool complete_;
    int activeIndex_;
    std::set<int> indexesLeft;
    
    std::vector<PictureElement> elements_;
    std::vector<std::shared_ptr<PictureElement>> elementsSPtr_;
    std::vector<sf::Sprite> elementsSprites_;
    Dictionary dictionary_;
};

}